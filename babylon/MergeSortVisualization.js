var createScene = function () {
    var scene = new BABYLON.Scene(engine);
    var camera = new BABYLON.ArcRotateCamera("camera", Math.PI / 2, Math.PI / 3, 100, new BABYLON.Vector3(0, 0, 0), scene);
    camera.attachControl(canvas, true);

    var light = new BABYLON.HemisphericLight("light", new BABYLON.Vector3(1, 1, 0), scene);

    var barCount = 300; // Увеличиваем количество столбиков
    var barWidth = 0.2; // Уменьшаем ширину столбиков
    var bars = [];
    var maxHeight = 10;
    var animationSpeed = 10; // Скорость анимации
    var delayTime = 5; // Задержка между шагами

    function createGradientTexture(height) {
        var dynamicTexture = new BABYLON.DynamicTexture("dynamicTexture", {width: 2, height: 256}, scene);
        var ctx = dynamicTexture.getContext();

        var gradient = ctx.createLinearGradient(0, 0, 0, 256);
        gradient.addColorStop(0, "blue");
        gradient.addColorStop(1, "red");

        ctx.fillStyle = gradient;
        ctx.fillRect(0, 0, 2, 256);

        dynamicTexture.update();

        var material = new BABYLON.StandardMaterial("barMat", scene);
        material.diffuseTexture = dynamicTexture;

        return material;
    }

    for (let i = 0; i < barCount; i++) {
        var height = Math.random() * maxHeight;
        var bar = BABYLON.MeshBuilder.CreateBox("bar" + i, { height: height, width: barWidth, depth: barWidth }, scene);
        bar.position.x = i * barWidth - (barCount * barWidth) / 2;
        bar.position.y = height / 2;
        bar.material = createGradientTexture(height);
        bars.push(bar);
    }

    async function mergeSort(bars, offset) {
        if (bars.length <= 1) {
            return bars;
        }

        var mid = Math.floor(bars.length / 2);
        var left = bars.slice(0, mid);
        var right = bars.slice(mid);

        left = await mergeSort(left, offset);
        right = await mergeSort(right, offset + left.length);

        return await merge(left, right, offset);
    }

    async function merge(left, right, offset) {
        var result = [];
        while (left.length && right.length) {
            if (left[0].position.y < right[0].position.y) {
                result.push(left.shift());
            } else {
                result.push(right.shift());
            }
        }

        result = result.concat(left, right);

        await updateBars(result, offset);

        return result;
    }

    async function updateBars(sortedBars, offset) {
        for (let i = 0; i < sortedBars.length; i++) {
            let bar = sortedBars[i];
            let targetX = (offset + i) * barWidth - (barCount * barWidth) / 2;

            // Создаем анимацию для перемещения столбиков
            var animation = new BABYLON.Animation("animation", "position.x", 60, 
                BABYLON.Animation.ANIMATIONTYPE_FLOAT, 
                BABYLON.Animation.ANIMATIONLOOPMODE_CONSTANT);

            var keys = [];
            keys.push({ frame: 0, value: bar.position.x });
            keys.push({ frame: animationSpeed, value: targetX });
            animation.setKeys(keys);

            bar.animations = [];
            bar.animations.push(animation);

            scene.beginAnimation(bar, 0, animationSpeed, false);

            // Задержка перед следующей итерацией
            await new Promise(resolve => setTimeout(resolve, delayTime));
        }
    }

    mergeSort(bars, 0).then(sortedBars => {
        console.log("Sorting Complete!");
    });

    return scene;
};

// Don't forget to call createScene to run the scene setup

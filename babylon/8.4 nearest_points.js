var createScene = function () {
    var scene = new BABYLON.Scene(engine);
    var camera = new BABYLON.ArcRotateCamera("camera", Math.PI / 2, Math.PI / 2.5, 15, new BABYLON.Vector3(0, 0, 0), scene);
    camera.attachControl(canvas, true);

    var light = new BABYLON.HemisphericLight("light", new BABYLON.Vector3(1, 1, 0), scene);

    var points = [];
    var closestPair = { distance: Infinity, pair: null };

    var animTime = 10;
    var pointCount = 100;

    for (let i = 0; i < pointCount; i++) {
        var point = BABYLON.MeshBuilder.CreateSphere('point' + i, { diameter: 0.2 }, scene);
        point.position.x = Math.random() * 10 - 5;
        point.position.y = Math.random() * 10 - 5;
        point.position.z = Math.random() * 10 - 5;
        point.material = new BABYLON.StandardMaterial("pointMat" + i, scene);
        point.material.emissiveColor = new BABYLON.Color3(0.5, 0.5, 0.5);
        points.push(point);
    }

    function sortPointsByX(points) {
        return points.sort((a, b) => a.position.x - b.position.x);
    }

async function findClosestPair(recPoints) {
    if (recPoints.length <= 3) {
        return bruteForceClosestPair(recPoints);
    }

    let mid = Math.floor(recPoints.length / 2);
    let midPoint = recPoints[mid].position.x;
    let left = recPoints.slice(0, mid);
    let right = recPoints.slice(mid);

    // Создаем и показываем плоскость разделения
    var plane = BABYLON.MeshBuilder.CreatePlane("plane", { height: 20, width: 20 }, scene);
    plane.position.x = midPoint; // Позиционируем плоскость на середине
    plane.rotation.y = Math.PI / 2; // Поворачиваем её вдоль оси Y
    plane.material = new BABYLON.StandardMaterial("planeMat", scene);
    plane.material.alpha = 0.3; // Устанавливаем большую прозрачность
    plane.material.diffuseColor = new BABYLON.Color3(0.1, 0.5, 0.5);
    plane.material.backFaceCulling = false; // Плоскость видна с обеих сторон

    let d1 = await findClosestPair(left);
    let d2 = await findClosestPair(right);

    // После обработки поддеревьев удаляем плоскость
    plane.dispose();

    let d = Math.min(d1, d2);


        let bandWidth = d;
        let inBand = recPoints.filter(p => Math.abs(p.position.x - recPoints[mid].position.x) < bandWidth);


        inBand.sort((a, b) => a.position.y - b.position.y);
        for (let i = 0; i < inBand.length - 1; i++) {
            for (let j = i + 1; j < inBand.length && (inBand[j].position.y - inBand[i].position.y) < bandWidth; j++) {
                await checkPair(inBand[i], inBand[j]);
            }
        }

        return closestPair.distance;
    }

    async function checkPair(p1, p2) {
        p1.material.emissiveColor = new BABYLON.Color3(1, 0, 0);
        p2.material.emissiveColor = new BABYLON.Color3(0, 0, 1);
        
        var line = BABYLON.MeshBuilder.CreateLines("line", { points: [p1.position.clone(), p2.position.clone()], updatable: true }, scene);
        
        await new Promise(resolve => setTimeout(resolve, animTime));

        let distance = BABYLON.Vector3.Distance(p1.position, p2.position);
        if (distance < closestPair.distance) {
            closestPair = { distance, pair: [p1, p2] };
        }
    
        line.dispose();
        p1.material.emissiveColor = new BABYLON.Color3(0.5, 0.5, 0.5);
        p2.material.emissiveColor = new BABYLON.Color3(0.5, 0.5, 0.5);

        return distance;
    }

    function bruteForceClosestPair(pointsArray) {
        let minDist = Infinity;
        for (let i = 0; i < pointsArray.length; i++) {
            for (let j = i + 1; j < pointsArray.length; j++) {
                let dist = BABYLON.Vector3.Distance(pointsArray[i].position, pointsArray[j].position);
                if (dist < minDist) {
                    minDist = dist;
                    closestPair = { distance: dist, pair: [pointsArray[i], pointsArray[j]] };
                }
            }
        }
        return minDist;
    }


    let sortedPoints = sortPointsByX(points);
    findClosestPair(sortedPoints).then(() => {
        if (closestPair.pair) {
            closestPair.pair[0].material.emissiveColor = new BABYLON.Color3(0, 1, 0);
            closestPair.pair[1].material.emissiveColor = new BABYLON.Color3(0, 1, 0);
            BABYLON.MeshBuilder.CreateLines("finalLine", { points: [closestPair.pair[0].position, closestPair.pair[1].position] }, scene);
        }
    });

    return scene;
};

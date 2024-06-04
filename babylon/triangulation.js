var createScene = function() {
    var scene = new BABYLON.Scene(engine);

    var camera = new BABYLON.ArcRotateCamera("Camera", -Math.PI / 2, Math.PI / 4, 10, BABYLON.Vector3.Zero(), scene);
    camera.attachControl(canvas, true);

    var light1 = new BABYLON.DirectionalLight("DirectionalLight", new BABYLON.Vector3(0, -1, 1), scene);
    var light2 = new BABYLON.HemisphericLight("HemiLight", new BABYLON.Vector3(0, 1, 0), scene);   
    light1.intensity = 0.75;
    light2.intensity = 0.5;

// Определим точки сложного десятиугольника
var points = [
    new BABYLON.Vector3(2, 0, 0),         // Вершина 1
    new BABYLON.Vector3(1.5, 0, 1.5),     // Вершина 2
    new BABYLON.Vector3(0, 0, 2),         // Вершина 3
    new BABYLON.Vector3(-1.5, 0, 1.5),    // Вершина 4
    new BABYLON.Vector3(-2, 0, 0.5),      // Вершина 5
    new BABYLON.Vector3(-1.8, 0, -1.5),   // Вершина 6
    new BABYLON.Vector3(-0.5, 0, -2),     // Вершина 7
    new BABYLON.Vector3(0.7, 0, -1.8),    // Вершина 8
    new BABYLON.Vector3(1.8, 0, -1),      // Вершина 9
    new BABYLON.Vector3(2, 0, -0.5),      // Вершина 10
    // Повторяем первую вершину, чтобы замкнуть полигон
    new BABYLON.Vector3(2, 0, 0)          // Вершина 1 (повтор)
];


    // Создаём линии полигона
    var polygonLines = BABYLON.MeshBuilder.CreateLines("polygonLines", {
        points: [...points, points[0]],
    }, scene);

    // Применим цвет для оригинального полигона
    polygonLines.color = new BABYLON.Color3(1, 0, 0);  // Красный цвет

    // GUI для отображения текста
    var advancedTexture = BABYLON.GUI.AdvancedDynamicTexture.CreateFullscreenUI("UI");

    var textBlock = new BABYLON.GUI.TextBlock();
    textBlock.text = "Количество треугольников: 0";
    textBlock.color = "white";
    textBlock.fontSize = 24;
    textBlock.textHorizontalAlignment = BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
    textBlock.textVerticalAlignment = BABYLON.GUI.Control.VERTICAL_ALIGNMENT_TOP;

    // Устанавливаем отступы от края
    textBlock.paddingTop = "10px";
    textBlock.paddingLeft = "10px";

    advancedTexture.addControl(textBlock);

    // Функция для выполнения триангуляции и анимации
    function animateTriangulation(vertices) {
        var triangles = [];
        if (vertices.length < 3) return triangles;

        // Разбиваем полигон на треугольники
        for (let i = 2; i < vertices.length; i++) {
            triangles.push([vertices[0], vertices[i - 1], vertices[i]]);
        }

        let triangleIndex = 0;

        function drawNextTriangle() {
            if (triangleIndex < triangles.length) {
                var triangle = triangles[triangleIndex];

                var triangleMesh = BABYLON.MeshBuilder.CreateLines("triangle" + triangleIndex, {
                    points: [...triangle, triangle[0]],
                }, scene);
                triangleMesh.color = new BABYLON.Color3(1, 0, 0);  // Красный цвет

                triangleIndex++;
                setTimeout(drawNextTriangle, 1000); // Рисуем следующий треугольник через 1 секунду
            } else {
                updateText(triangles.length);  // Обновляем текст с количеством треугольников
            }
        }

        drawNextTriangle();
    }

    // Функция для обновления текста с количеством треугольников
    function updateText(numTriangles) {
        textBlock.text = "Количество треугольников: " + numTriangles;
    }

    // Запускаем анимацию триангуляции после небольшой задержки
    setTimeout(() => {
        animateTriangulation(points);
    }, 1000);

    return scene;
};

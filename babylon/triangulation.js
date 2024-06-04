var createScene = function() {
    var scene = new BABYLON.Scene(engine);

    var camera = new BABYLON.ArcRotateCamera("Camera", -Math.PI / 2, Math.PI / 4, 10, BABYLON.Vector3.Zero(), scene);
    camera.attachControl(canvas, true);

    var light1 = new BABYLON.DirectionalLight("DirectionalLight", new BABYLON.Vector3(0, -1, 1), scene);
    var light2 = new BABYLON.HemisphericLight("HemiLight", new BABYLON.Vector3(0, 1, 0), scene);   
    light1.intensity = 0.75;
    light2.intensity = 0.5;

    // Определим точки многоугольника с вогнутой частью (шестигранник)
    var points = [
        new BABYLON.Vector3(2, 0, 0),         // Вершина 1
        new BABYLON.Vector3(1, 0, 1.5),       // Вершина 2
        new BABYLON.Vector3(0, 0, 1),         // Вершина 3
        new BABYLON.Vector3(-5, 0, 1.5),      // Вершина 4
        new BABYLON.Vector3(-2, 0, 0),        // Вершина 5
        new BABYLON.Vector3(-1, 0, -1.5),     // Вершина 6
        new BABYLON.Vector3(0, 0, -1),        // Вершина 7
        new BABYLON.Vector3(1, 0, -1.5),      // Вершина 8
        // Повторяем первую вершину, чтобы замкнуть полигон
        new BABYLON.Vector3(2, 0, 0)          // Вершина 1 (повтор)
    ];

    // Создаём линии полигона
    var polygonLines = BABYLON.MeshBuilder.CreateLines("polygonLines", {
        points: points,
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

    // Функция для обновления текста с количеством треугольников
    function updateText(numTriangles) {
        textBlock.text = "Количество треугольников: " + numTriangles;
    }

    // Функция для проверки, является ли вершина выпуклой или вогнутой
    function isConvex(A, B, C) {
        var crossProduct = (B.x - A.x) * (C.z - A.z) - (B.z - A.z) * (C.x - A.x);
        return crossProduct >= 0;
    }

    // Функция для проверки, содержит ли треугольник какую-либо другую вершину
    function isEar(polygon, i) {
        const n = polygon.length;
        const prev = (i - 1 + n) % n;
        const next = (i + 1) % n;

        if (!isConvex(polygon[prev], polygon[i], polygon[next])) return false;

        const A = polygon[prev];
        const B = polygon[i];
        const C = polygon[next];

        for (let j = 0; j < n; j++) {
            if (j === prev || j === i || j === next) continue;
            const P = polygon[j];
            if (pointInTriangle(P, A, B, C)) return false;
        }

        return true;
    }

    // Функция для проверки, находится ли точка внутри треугольника
    function pointInTriangle(P, A, B, C) {
        const areaOrig = triangleArea(A, B, C);
        const area1 = triangleArea(P, B, C);
        const area2 = triangleArea(P, A, C);
        const area3 = triangleArea(P, A, B);

        return Math.abs(areaOrig - (area1 + area2 + area3)) < 1e-6;
    }

    // Функция для вычисления площади треугольника
    function triangleArea(A, B, C) {
        return Math.abs((A.x * (B.z - C.z) + B.x * (C.z - A.z) + C.x * (A.z - B.z)) / 2);
    }

    // Алгоритм триангуляции удалением ушей
    function triangulatePolygon(polygon) {
        const triangles = [];

        while (polygon.length > 3) {
            for (let i = 0; i < polygon.length; i++) {
                if (isEar(polygon, i)) {
                    const prev = (i - 1 + polygon.length) % polygon.length;
                    const next = (i + 1) % polygon.length;
                    triangles.push([polygon[prev], polygon[i], polygon[next]]);
                    polygon.splice(i, 1);
                    break;
                }
            }
        }

        triangles.push([polygon[0], polygon[1], polygon[2]]);
        return triangles;
    }

    // Функция для выполнения анимации триангуляции
    function animateTriangulation(vertices) {
        var triangles = triangulatePolygon(vertices.slice(0, vertices.length - 1));

        let triangleIndex = 0;

        function drawNextTriangle() {
            if (triangleIndex < triangles.length) {
                var triangle = triangles[triangleIndex];

                // Отрисуем только внутренние линии треугольников
                for (let edgeIndex = 0; edgeIndex < triangle.length; edgeIndex++) {
                    var start = triangle[edgeIndex];
                    var end = triangle[(edgeIndex + 1) % triangle.length];

                    // Проверим, является ли линия внутренней или составляет границы многоугольника
                    var isBoundaryLine = points.some((point, i) => {
                        var nextPoint = points[(i + 1) % points.length];
                        return (point.equals(start) && nextPoint.equals(end)) || (point.equals(end) && nextPoint.equals(start));
                    });

                    if (!isBoundaryLine) {
                        var lineMesh = BABYLON.MeshBuilder.CreateLines("triangleEdge" + triangleIndex + "_" + edgeIndex, {
                            points: [start, end],
                        }, scene);
                        lineMesh.color = new BABYLON.Color3(0, 1, 0);  // Зелёный цвет
                    }
                }

                triangleIndex++;
                setTimeout(drawNextTriangle, 1000); // Рисуем следующий треугольник через 1 секунду
            } else {
                updateText(triangles.length);  // Обновляем текст с количеством треугольников
            }
        }

        drawNextTriangle();
    }

    // Запускаем анимацию триангуляции после небольшой задержки
    setTimeout(() => {
        animateTriangulation(points);
    }, 1000);

    return scene;
};

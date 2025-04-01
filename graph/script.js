// Функция для визуализации графа
function visualizeGraph(nodes, edges) {
    const container = document.getElementById('graph');

    const options = {
        nodes: {
            shape: 'dot', // Узлы будут круглыми
            size: 20,
        },
        edges: {
            arrows: { to: { enabled: true, scaleFactor: 0.5 } }, // Стрелки на рёбрах
            smooth: { type: 'continuous' }, // Гладкие рёбра
        },
        physics: {
            enabled: true, // Включаем физику для возможности перемещения узлов
            solver: 'forceAtlas2Based', // Используем solver для физического моделирования
            stabilization: { iterations: 1000 }, // Стабилизация графа
        },
    };

    const network = new vis.Network(container, { nodes, edges }, options);
    console.log("Загруженные данные:", nodes, edges);
}

// Обработчик загрузки файла
document.getElementById('file-input').addEventListener('change', function(event) {
    const reader = new FileReader();
    reader.onload = function (e) {
        const data = processFileData(e.target.result);
        visualizeGraph(data.nodes, data.edges);
    };
    reader.readAsText(event.target.files[0]);
});

// Функция для обработки данных из файла
function processFileData(fileContent) {
    const lines = fileContent.trim().split("\n");
    const nodes = new Set();
    const edges = [];

    // Преобразуем строки в данные
    lines.forEach(line => {
        const [from, to, weight] = line.split(" ");
        nodes.add(from);
        nodes.add(to);
        edges.push({ from, to, label: weight });
    });

    const nodesArray = Array.from(nodes).map((node, index) => ({
        id: index + 1, label: node
    }));

    return {
        nodes: nodesArray,
        edges: edges
    };
}

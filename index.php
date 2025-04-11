<!DOCTYPE html>
<html lang="hu">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Kollégiumi Beléptető</title>
    <link rel="stylesheet" href="styles.css">
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
</head>
<body>

<!-- Navbar -->
<div class="navbar">
    <img src="img/dormlogo.png" alt="Logo">
    <ul>
        <li><a href="index.html"><b>Főoldal</b></a></li>
        <li><a href="ujhallgato.html">Új hallgató</a></li>
        <li><a href="vendegkartya.html">Vendégkártya felvétele</a></li>
    </ul>
</div>

<!-- Statisztikák -->
<div class="stats-container">
    <h2>Jelenlegi létszám a kollégiumban</h2>
    <div class="charts">
        <div class="chart-container">
            <h3>Aktív vs. Inaktív kollégisták</h3>
            <canvas id="chartInaktiv"></canvas>
        </div>
        <div class="chart-container">
            <h3>Kiadható vendégszobák</h3>
            <canvas id="chartSzobak"></canvas>
        </div>
        <div class="chart-container">
            <h3>Kollégium megteltsége</h3>
            <canvas id="chartMegteltseg"></canvas>
        </div>
    </div>
</div>

<footer>
    <p>&copy; 2025 Kollégiumi Beléptető Rendszer | Kapcsolat: info@kollegium.hu</p>
</footer>

<script src="script.js"></script>

</body>
</html>

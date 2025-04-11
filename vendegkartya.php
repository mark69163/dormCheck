<!DOCTYPE html>
<html lang="hu">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Vendégkártya felvétele</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>

<!-- Navbar -->
<div class="navbar">
    <img src="img/dormlogo.png" alt="Logo">
    <ul>
        <li><a href="index.html">Főoldal</a></li>
        <li><a href="ujhallgato.html">Új hallgató</a></li>
        <li><a href="vendegkartya.html" class="active">Vendégkártya felvétele</a></li>
    </ul>
</div>

<!-- Vendégkártya form -->
<div class="form-container card">
    <h2>Vendégkártya felvétele</h2>
    <form>
        <label for="hallgato">🎓 Hallgató neve:</label>
        <input type="text" id="hallgato" placeholder="Pl. Kovács Péter" required>

        <label for="kartya">💳 Kártyaszám:</label>
        <input type="text" id="kartya" placeholder="Pl. 1234-5678-9012" required>

        <label for="ervenyesseg">📅 Érvényességi idő:</label>
        <input type="date" id="ervenyesseg" required>

        <button type="submit">✅ Mentés</button>
    </form>
</div>

<footer>
    <p>&copy; 2025 Kollégiumi Beléptető Rendszer</p>
</footer>

</body>
</html>
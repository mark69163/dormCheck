<!DOCTYPE html>
<html lang="hu">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Új hallgató felvétele</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>

<!-- Navbar -->
<div class="navbar">
    <img src="img/dormlogo.png" alt="Logo">
    <ul>
        <li><a href="index.php">📊 Főoldal</a></li>
        <li><a href="ujhallgato.php"><b>➕ Új hallgató</b></a></li>
        <li><a href="vendegkartya.php">🪪 Vendégkártya felvétele</a></li>
    </ul>
</div>

<!-- Form -->
<div class="form-container">
    <h2>Új hallgató felvétele</h2>
    <form>
        <label for="nev">Név:</label>
        <input type="text" id="nev" required>

        <label for="neptun">Neptun kód:</label>
        <input type="text" id="neptun" required>

        <label for="szoba">Szobaszám:</label>
        <input type="text" id="szoba" required>

        <button type="submit">Mentés</button>
    </form>
</div>

<br><br><br><br><br>
<footer class="footer">
    <div class="footer-left">
        <img src="img/logo--inverse.png" alt="NJE logó"> <!-- Itt cseréld le a megfelelő logóra -->
        <h2>Kollégium Beléptető Rendszer</h2>
        <a href="#">Tagok</a>
        <div class="footer-links">
            <a href="#">Koltai Armand</a> |
            <a href="#">Hoki Attila</a> |
            <a href="#">Kovács Márk</a>
        </div>
    </div>
    <div class="footer-right">
        <img src="img/dormlogo.png" alt="Széchenyi 2020"> <!-- Itt cseréld le a megfelelő logóra -->
    </div>
</footer>

</body>
</html>

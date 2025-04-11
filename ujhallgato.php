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
        <li><a href="index.html">Főoldal</a></li>
        <li><a href="ujhallgato.html"><b>Új hallgató</b></a></li>
        <li><a href="vendegkartya.html">Vendégkártya felvétele</a></li>
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

<footer>
    <p>&copy; 2025 Kollégiumi Beléptető Rendszer</p>
</footer>

</body>
</html>

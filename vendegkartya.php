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
        <li><a href="index.php">📊 Főoldal</a></li>
        <li><a href="ujhallgato.php">➕ Új hallgató</a></li>
        <li><a href="vendegkartya.php" class="active">🪪 Vendégkártya felvétele</a></li>
    </ul>
</div>

<!-- Vendégkártya form -->
<div class="form-container card">
    <h2>Guest Card Registration</h2>
    <form>
        <label for="student">🎓 Resident's Name:</label>
        <input type="text" id="student" placeholder="E.g. John Doe" required>

        <label for="student-card">💳 Resident's Card Number:</label>
        <input type="text" id="student-card" placeholder="E.g. 1234-5678-9012" required>

        <label for="guest">👤 Guest's Name:</label>
        <input type="text" id="guest" placeholder="E.g. Peter Smith" required>

        <label for="guest-card">💳 Guest's Card Number:</label>
        <input type="text" id="guest-card" placeholder="E.g. 3333-4444" required>

        <button type="submit">✅ Save</button>
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

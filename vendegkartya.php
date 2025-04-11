<!DOCTYPE html>
<html lang="hu">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Vendégkártya felvétele</title>
    <link rel="stylesheet" href="styles.css">
    <script src="https://unpkg.com/lucide@latest"></script>
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
</head>
<style>
    body {
        font-family: 'Inter', sans-serif;
        margin: 0;
        padding: 0;
        background: #f4f4f9;
        color: #333;
    }

    .container {
        display: flex;
        height: 100vh;
        overflow: hidden;
    }

    .sidebar {
        background: #212529;
        color: white;
        width: 250px;
        min-width: 60px;
        transition: width 0.3s ease;
        display: flex;
        flex-direction: column;
        padding-top: 20px;
    }

    .sidebar.collapsed {
        width: 60px;
    }

    .sidebar img {
        width: 70%;
        margin-bottom: 30px;
        transition: 0.3s;
        align-self: flex-start;
        padding-left: 20px;
    }

    .sidebar ul {
        list-style: none;
        padding: 0;
        width: 100%;
    }

    .sidebar ul li {
        padding: 15px 20px;
        display: flex;
        align-items: center;
        gap: 15px;
        transition: background 0.3s ease, padding 0.2s;
    }

    .sidebar ul li:hover {
        background: #495057;
        cursor: pointer;
    }

    .sidebar ul li span {
        white-space: nowrap;
    }

    .sidebar.collapsed ul li span {
        display: none;
    }

    .main-content {
        flex: 1;
        padding: 20px;
        overflow-y: auto;
        background: #f9f9f9;
    }

    h2 {
        text-align: center;
        color: #495057;
    }

    hr {
        width: 50%;
        margin: 20px auto;
        border: none;
        height: 2px;
        background: linear-gradient(to right, transparent, #f39c12, transparent);
    }

    .cards {
        display: flex;
        justify-content: space-between;
        gap: 20px;
        flex-wrap: wrap;
        margin-top: 30px;
    }

    .card {
        width: 27%;
        background-color: #ffffff;
        border-radius: 12px;
        padding: 15px;
        box-shadow: 0px 4px 15px rgba(0, 0, 0, 0.1);
        transition: all 0.3s ease;
    }

    .card:hover {
        transform: scale(1.05);
        box-shadow: 0px 4px 20px rgba(0, 0, 0, 0.2);
    }

    .card h4 {
        font-size: 20px;
        color: #2d2d2d;
        margin-bottom: 15px;
    }

    .card .value {
        font-size: 36px;
        font-weight: bold;
        color: #007bff;
    }

    .card .progress {
        margin-top: 15px;
        height: 8px;
        border-radius: 4px;
        background-color: #e0e0e0;
    }

    .card .progress-bar {
        height: 100%;
        border-radius: 4px;
    }

    .csippantas-gomb {
        position: absolute;
        top: 20px;
        right: 300px;
        padding: 12px 20px;
        font-size: 16px;
        background: #007bff;
        color: white;
        border: none;
        border-radius: 8px;
        cursor: pointer;
        transition: all 0.3s ease;
    }

    .csippantas-gomb:hover {
        background: #0056b311;
        transform: scale(1.1);
    }

    .notifications {
        width: 300px;
        background: #fff;
        box-shadow: 0 0 15px rgba(0, 0, 0, 0.1);
        border-left: 1px solid #ddd;
        transition: width 0.3s ease;
        display: flex;
        flex-direction: column;
    }

    .notifications.collapsed {
        width: 80px;
    }

    .notifications.collapsed .notifications-header h3 {
        display: none;
    }

    .notifications.collapsed #notifToggleIcon {
        display: block;
    }

    .notifications-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        cursor: pointer;
        padding: 12px;
        border-bottom: 1px solid #ddd;
        background: #f8f9fa;
    }

    .notifications-header h3 {
        margin: 0;
        font-size: 18px;
        color: #333;
    }

    .notifications-body {
        padding: 10px;
        flex: 1;
        overflow-y: auto;
    }

    .notification {
        background: #f9f9f9;
        padding: 12px;
        margin-bottom: 15px;
        border-left: 5px solid #007bff;
        border-radius: 6px;
        display: flex;
        align-items: center;
        gap: 15px;
        animation: showNotif 0.5s ease-out forwards;
    }

    .footer {
        background-color: #212529;
        color: white;
        padding: 20px;
        display: flex;
        justify-content: space-between;
        align-items: center;
        font-size: 14px;
    }

    .footer a {
        color: #f39c12;
        text-decoration: none;
    }

    .footer img {
        max-width: 100px;
    }

    @keyframes showNotif {
        0% {
            opacity: 0;
            transform: translateX(100%);
        }
        100% {
            opacity: 1;
            transform: translateX(0);
        }
    }

    /* Gomb pozicionálása a sidebar mellett */
    .btn-div {
        position: absolute;
        top: 5px;
        left: 250px;
        z-index: 1000;
        transition: left 0.3s ease;
    }

    .toggle-btn {
        background-color: transparent;
        color: darkgray;
        border: none;
        padding: 12px;
        cursor: pointer;
        font-size: 20px;
        height: 50px;
        width: 50px;
        border-radius: 8px;
    }
    .toggle-btn:hover {
        background-color: transparent;
    }

    @media screen and (max-width: 768px) {
        .cards {
            flex-direction: column;
            align-items: center;
            gap: 20px;
        }

        .sidebar {
            position: fixed;
            left: -250px;
            transition: left 0.3s ease;
        }

        .sidebar.collapsed {
            left: 0;
        }

        .main-content {
            margin-left: 20px;
            margin-top: 80px;
        }
    }
</style>
<body>
<div class="btn-div" id="toggleBtnDiv">
    <button class="toggle-btn" onclick="toggleSidebar()"><i data-lucide='menu'></i></button>
</div>
<div class="container">
<!-- Sidebar -->
<div class="sidebar" id="sidebar">
    <br>
    <img src="img/logo--inverse.png" alt="Logo">

    <ul>
        <li onclick="location.href='index.php'">
            <i data-lucide="bar-chart-3"></i> <span>Home</span>
        </li>
        <li onclick="location.href='ujhallgato.php'">
            <i data-lucide="user-plus"></i> <span>New Student</span>
        </li>
        <li onclick="location.href='vendegkartya.php'">
            <i data-lucide="badge-check"></i> <span>Register Guest Card</span>
        </li>
    </ul>
    <ul>
        <li onclick="location.href='logout.php'">
            <i data-lucide="log-out"></i> <span>Logout</span>
        </li>
    </ul>
</div>
    <div class="main-content">
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
    </div></div>
</body>
<!-- Scripts -->
<script>
    document.addEventListener("DOMContentLoaded", function () {
        const sidebar = document.getElementById("sidebar");
        const btnDiv = document.getElementById("toggleBtnDiv");

        // Read sidebar state from localStorage
        const isCollapsed = localStorage.getItem("sidebarCollapsed") === "true";

        if (isCollapsed) {
            sidebar.classList.add("collapsed");
            btnDiv.style.left = "60px";
        } else {
            sidebar.classList.remove("collapsed");
            btnDiv.style.left = "250px";
        }
    });

    function toggleSidebar() {
        const sidebar = document.getElementById("sidebar");
        const btnDiv = document.getElementById("toggleBtnDiv");

        sidebar.classList.toggle("collapsed");

        // Adjust the toggle button position dynamically
        btnDiv.style.left = sidebar.classList.contains("collapsed") ? "60px" : "250px";

        // Save state to localStorage
        localStorage.setItem("sidebarCollapsed", sidebar.classList.contains("collapsed"));
    }

    function toggleNotifications() {
        const notif = document.getElementById("notifications");
        const icon = document.getElementById("notifToggleIcon");

        notif.classList.toggle("collapsed");

        icon.innerHTML = notif.classList.contains("collapsed")
            ? "<i data-lucide='arrow-left'></i>"
            : "<i data-lucide='arrow-right'></i>";

        lucide.createIcons();
    }

    function showNotification() {
        const body = document.getElementById("notifBody");

        const notification = document.createElement("div");
        notification.classList.add("notification");

        notification.innerHTML = `
            <img src="img/hallgato.png" alt="Student Picture" style="width:40px; height:40px; border-radius:50%;">
            <div>
                <strong>Peter Kovacs</strong><br>
                Neptun Code: ABC123
            </div>
        `;

        body.appendChild(notification);

        setTimeout(() => {
            notification.style.animation = "hideNotif 0.5s ease-in forwards";
            setTimeout(() => {
                notification.remove();
            }, 500);
        }, 10000);
    }

    function generateRandomData() {
        let data = [];
        for (let i = 0; i < 7; i++) {
            data.push(Math.floor(Math.random() * (500 - 200 + 1)) + 200);
        }
        return data;
    }



    lucide.createIcons();
</script>
</html>

const express = require("express");
const http = require("http");
const WebSocket = require("ws");
const path = require("path");
const bodyParser = require("body-parser");
const db = require("./config/db");

const HomeController = require("./controllers/homeController"); // Új: HomeController import

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

// EJS config
app.set("view engine", "ejs");
app.set("views", path.join(__dirname, "views"));

app.use(bodyParser.json());
app.use("/public", express.static(path.join(__dirname, "public")));

// WebSocket kapcsolat naplózása
wss.on("connection", (ws) => {
    console.log("New WebSocket client connected");
});

const homeController = new HomeController(wss);
const homeRoutes = require("./routes/index")(homeController); // ⬅ átadod

// Route-ok
const apiRoutes = require("./routes/api");

app.use("/", homeRoutes);
app.use("/api", apiRoutes);

// Szerver indítás
const PORT = process.env.PORT || 3333;
server.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});

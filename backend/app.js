const express = require("express");
const http = require("http");
const WebSocket = require("ws");
const path = require("path");
const bodyParser = require("body-parser");
const db = require("./config/db");

const EntryController = require("./controllers/entryController");

const app = express();
const server = http.createServer(app);
const wss = new WebSocket.Server({ server });

// EJS config
app.set("view engine", "ejs");
app.set("views", path.join(__dirname, "views"));

app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, "public")));

// Route-ok
const homeRoutes = require("./routes/index");
const apiRoutes = require("./routes/api");
const entryRoutes = require("./routes/entry");

app.use("/", homeRoutes);
app.use("/api", apiRoutes);
app.use("/", entryRoutes); // /entry route itt

// WebSocket kapcsolat
wss.on('connection', (ws) => {
    console.log("New WebSocket client connected");
});

// EntryController indítása
const entryController = new EntryController(wss);
entryController.startChecking();

const PORT = process.env.PORT || 3333;
server.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});

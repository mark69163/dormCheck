const express = require("express");
const http = require("http");
const path = require("path");
const bodyParser = require("body-parser");
const db = require("./config/db");

const app = express();
const server = http.createServer(app);

// View engine beállítás
app.set("view engine", "ejs");
app.set("views", path.join(__dirname, "views"));

// Middleware
app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, "public")));

// Route-ok
const homeRoutes = require("./routes/index");
const apiRoutes = require("./routes/api");

app.use("/", homeRoutes);
app.use("/api", apiRoutes);

const PORT = process.env.PORT || 3333;

// Szerver indítása
server.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});

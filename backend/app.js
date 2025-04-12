const express = require("express");
const app = express();
const path = require("path");
const bodyParser = require("body-parser");

app.set("view engine", "ejs");
app.set("views", path.join(__dirname, "views"));

app.use(bodyParser.json());
app.use(express.static(path.join(__dirname, "public")));

const homeRoutes = require("./routes/index");
app.use("/", homeRoutes);

const PORT = process.env.PORT || 3333;
app.listen(PORT, () => {
    console.log(`Server is running on http://localhost:${PORT}`);
});
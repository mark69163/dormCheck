const express = require("express");
const router = express.Router();

const HomeController = require("../controllers/homeController");
const homeController = new HomeController(); // csak ha nem kell neki pl. wss paraméter

router.get("/", (req, res) => homeController.index(req, res));

module.exports = router;

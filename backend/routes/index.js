const express = require("express");

module.exports = (homeController) => {
    const router = express.Router();

    router.get("/", (req, res) => homeController.index(req, res));

    return router;
};
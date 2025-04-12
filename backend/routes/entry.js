const express = require("express");
const router = express.Router();

router.get("/entry", (req, res) => {
    res.render("entry");
});

module.exports = router;

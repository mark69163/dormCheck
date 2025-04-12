const express = require("express");
const router = express.Router();
const CardModel = require("../models/CardModel");
const UserModel = require("../models/UserModel");

const API_KEY = process.env.API_KEY;

router.post("/card/v1/entrylog", async (req, res) => {
    const { cardid } = req.body;
    const apikey = req.headers['x-api-key'];

    if (!apikey || apikey !== API_KEY) {
        return res.status(401).json({ error: "Invalid API key!" });
    }

    if (!req.body || typeof req.body.cardid === 'undefined' || req.body.cardid.trim() === "") {
        return res.status(400).json({ error: "Card ID is required!" });
    }

    if (!cardid || cardid.trim() === "") {
        return res.status(400).json({ error: "Card ID is required!" });
    }

    try {
        const status = await CardModel.validateCard(cardid);

        if (status === "UNAUTHORIZED") {
            await CardModel.addCardCheck("UNKNOWN", -1, "UNAUTHORIZED");
            return res.status(403).json({ message: "Invalid card!" });
        }

        if (status === "UNASSIGNED") {
            await CardModel.addCardCheck(cardid, -1, "UNASSIGNED");
            return res.status(403).json({ message: "Card exists but not assigned!" });
        }

        if (status === "AUTHORIZED") {
            const user = await UserModel.getUserByCardId(cardid);
            const userid = user ? user.userid : -1;

            if (!userid) {
                await CardModel.addCardCheck(cardid, -1, "UNAUTHORIZED");
                return res.status(406).json({ message: "Assigned card but expired!" });
            }

            await CardModel.addCardCheck(cardid, userid, "ENTRY");
            return res.status(200).json({ message: "Access granted." });
        }

    } catch (err) {
        console.error("Database error: ", err);
        res.status(500).json({ error: "Server error" });
    }
});

module.exports = router;

exports.index = (req, res) => {
    res.render("home", { message: "HELLO MVC!" });
};

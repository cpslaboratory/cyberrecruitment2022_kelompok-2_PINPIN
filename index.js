const express = require("express");
const app = express();
const path = require("path");
const port = process.env.PORT || 80;
const staticpath = path.join(__dirname, "/");

var antares = require("antares-http");

app.use(express.static(staticpath));

app.get("/", function (req, res) {
  res.sendFile(staticpath + "/index.html");
});

app.get("/api", function (req, res) {
  antares.setAccessKey("6100fc96a0000379:2536d3e0e1149aec");
  antares.get("CPS", "RFID").then(function (response) {
    const data = response.content;
    res.json(data);
  });
});

app.listen(port);

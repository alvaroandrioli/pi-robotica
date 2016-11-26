'use strict';

var express = require("express");
var app = express();
var cors = require('cors')
var server = require("http").createServer(app);
var config = require("./config");
var SerialPort = require("serialport");
var events = require("events");
var eventEmitter = new events.EventEmitter();
var bodyParser = require('body-parser')

app.use(bodyParser.json());
app.use(cors());

var getMyArduinoPort = function(err, ports) {
  var myPorts = ports.filter(function(port) {
    return (port.serialNumber) && (port.serialNumber.indexOf('arduino') > -1);
  }).pop();

  if (!myPorts)
    console.log(new Error("Nenhum arduino encontrado!"));

  var port = new SerialPort(myPorts.comName, {
    baudRate: config.BAUD_RATE,
    parser: SerialPort.parsers.readline(config.LINE_PARSE)
  });

  var onOpen = function() {
    console.log("Serial port is opened!");
  }

  var onData = function(data) {
    // console.log("Data received = '" + data + "'");
    eventEmitter.emit("serial.data", data);
  }

  eventEmitter.on("command.received", function(command) {
    console.log("EVENT command.received ON - " + command);
    port.write(command);
  });

  var onError = function(err) {
    console.log(err);
  }

  port.on("open", onOpen);      //listening open
  port.on("data", onData);      //listening data
  port.on("error", onError);    //listening error
}

SerialPort.list(getMyArduinoPort);  //callback to serialport

eventEmitter.on("serial.data", function(data) {
  console.log("EVENT serial.data ON - " + data);
});

app.get("/code/:c", function(req, res) {
  console.log("REST COMMAND RECEIVED - " + req.params.c);
  eventEmitter.emit("command.received", req.params.c);
  res.sendStatus(200);
});

app.post("/code/", function(req, res) {
  console.log("REST COMMAND RECEIVED - " + req.body.c);
  eventEmitter.emit("command.received", req.body.c);
  res.sendStatus(200);
});


server.listen(config.PORT, function() {
  console.log("SERVER ON - " + config.PORT);
});

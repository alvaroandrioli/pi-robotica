var config = require('./config.js');

config.PORT = process.env.PORT ? process.env.PORT : config.PORT;

config.BAUD_RATE = process.env.BAUD_RATE ? process.env.BAUD_RATE : config.BAUD_RATE;

config.LINE_PARSE = process.env.LINE_PARSE ? process.env.LINE_PARSE : config.LINE_PARSE;

module.exports = config;

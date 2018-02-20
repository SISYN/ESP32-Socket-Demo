/**************************************************************************************************************
 * @file index.js
 * @author Dan Lindsey
 * @version 0.0.1
 * @copyright Dan Lindsey 2018
 * @description WebSocket server for ESP32 socket demo @ mdlindsey.com
 **************************************************************************************************************/
/**************************************************************************************************************
 * Application configuration
 **************************************************************************************************************/
'use strict';


// Setup Socket.io server for the browser
var
  PortSocketIO = 1336,
  http = require('http'),
  app = http.createServer(function(req,res) {
    res.end('0');
  }),
  io = require('socket.io').listen(app);
  app.listen(PortSocketIO);
  console.log('Socket.io listening on port '+PortSocketIO);

io.on('connection', function(client) {
  console.log('New client ('+client.id+')');

  client.on('disconnect', function() {
    console.log('Client disconnected '+client.id);
  });
});


// Setup WebSocket server for the ESP32
var
  PortWebSocket = 1337,
  WebSocket = require('ws'),
  WebSocketServer = WebSocket.Server,
  Socket = new WebSocketServer({
    port: PortWebSocket
  });

Socket.on('connection', function connection(ws) {
  console.log('Client connected');
  ws.on('message', function(data) {
    //console.log('Received data:');
    //console.log(data);
    //console.log('Emitting update to socket.io');
    io.emit('update', data);
  });
  ws.on('error', function(er) {
      console.log(er);
  });
  ws.on('close', function() {
    for(var i = 0; i < WebSocketClients.length; i++)
      if ( WebSocketClients[i] == ws )
        delete WebSocketClients[i];
  });
});

console.log('WebSocket listening on port '+PortWebSocket+'.');

var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var fs = require('fs');

// var Almond = require('./lib/almond.js').Almond
// var almond = new Almond();
var Devices = require('./lib/devices/devices.js').Devices
var devices = new Devices();
devices.connect();

app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});

io.on('connection', function(socket){  
	console.log('a user connected');
	socket.on('disconnect', function(){
		console.log('user disconnected');
	});

  socket.on('fetch', function(data){
    console.log('hey hey');

  });

});

var devicesIO= io.of('/devices');
devicesIO.on('connection', function(socket){
  console.log('device listener connected');

  socket.on('fetch', function(data){
    console.log('fetch');
    var response = {
      success: true,
      data: devices.toJSON()
    }
    socket.emit('fetch', response)
  });

  devices.on('change', function(devices){
    var deviceJSON = devices.toJSON();   
    socket.emit('update', deviceJSON);
  })
});

var attrIO= io.of('/attrs');
attrIO.on('connection', function(socket){
  console.log('attr listener connected');

  socket.on('save', function(data){
    console.log('save');

    var callback = function(error, stdout, stderr){
      var response = {};

      if( error ){
        console.log('there was an error');
        response.success = false;
      }

      response.data = stdout;

      socket.emit('update', response)
    }

    var attrJSON = data.data;
    attrJSON.callback = callback;

    var deviceData = devices.set(attrJSON);
  });
});

http.listen(1337, function(){
  console.log('listening on *:1337');
});


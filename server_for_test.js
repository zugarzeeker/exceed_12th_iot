var express = require('express');
var app = express();
var port = 8888;
var data = {board: "", web: ""};
var round = 0;

app.get('/', function(request, response) {
	response.send("Welcome to iot server exceed camp : )");
});

app.get('/read/:type', function(request, response) {
	var type = request.params.type;
	response.send(data[type]);
	console.log("Round : " + (round++) + " | RequestData" + type[0].toUpperCase() + type.slice(1).toLowerCase() + " : " + data[type]);
});

app.get('/write/:type/:value', function(request, response) {
	var type = request.params.type;
	data[type] = request.params.value;
	response.send(data[type]);
	console.log("Round : " + (round++) + " | WriteData" + type[0].toUpperCase() + type.slice(1).toLowerCase() + " : " + data[type]);
});

app.listen(port, function() {
	console.log("Listening on port " + port);
});

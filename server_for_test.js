var express = require('express');
var app = express();
var port = 8888;
var data = {board: "", web: ""};
var round = 0;
var log = "";

app.get('/', function(request, response) {
  response.send("Welcome to iot server exceed camp : )");
});

app.get('/:group/read/:type', function(request, response) {
  var type = request.params.type;
  response.send(data[type]);
  text = "Group : " + request.params.group + " | Round : " + (round++) + " | RequestData" + type[0].toUpperCase() + type.slice(1).toLowerCase() + " : " + data[type];
  log += "<pre>" + text + "</pre>";
  console.log(text);
});

app.get('/:group/write/:type/:value', function(request, response) {
  var type = request.params.type;
  data[type] = request.params.value;
  response.send(data[type]);
  text = "Group : " + request.params.group + " | Round : " + (round++) + " | WriteData" + type[0].toUpperCase() + type.slice(1).toLowerCase() + " : " + data[type];
  log += "<pre>" + text + "</pre>";
  console.log(text);
});

app.get('/log', function (request, response) {
  if (log === "") {
    response.send("<pre>No log ja :P</pre><pre>(try '/1/write/web/test' then come back na krush)</pre>");
  }
  response.send(log);
});

app.listen(port, function() {
  console.log("Listening on port " + port);
});

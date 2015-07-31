var express = require('express');
var app = express();
var port = 1234;
var groupData = {};
var round = 0;
var log = "";

app.set('view engine', 'ejs');

app.get('/', function(request, response) {
  response.send("Welcome to iot server exceed camp : ) | Round : " + round);
  round++;
});

app.get('/code', function(request, response) {
  response.render("code.ejs");
  round++;
});


app.get('/:group/read/:type', function(request, response) {
  var group = request.params.group;
  var type = request.params.type;
  var value = groupData[group][type];
  response.send(value);
  text = "Group : " + request.params.group + " | Round : " + (round++) + " | RequestData" + type[0].toUpperCase() + type.slice(1).toLowerCase() + " : " + value;
  log += "<pre>" + text + "</pre>";
  console.log(text);
});

app.get('/:group/write/:type/:value', function(request, response) {
  var group = request.params.group;
  var type = request.params.type;
  var value = request.params.value;
  var data = {board: "", web: ""};
  console.log("type = " + type);
  data[type] = value;
  groupData[group] = data;
  response.send(value);
  text = "Group : " + request.params.group + " | Round : " + (round++) + " | WriteData" + type[0].toUpperCase() + type.slice(1).toLowerCase() + " : " + value;
  log += "<pre>" + text + "</pre>";
  console.log(text);
  // console.log(groupData)
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

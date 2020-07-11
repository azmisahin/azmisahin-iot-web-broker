var mosca = require("mosca");

var settings = {
  port: 1883,
};

var server = new mosca.Server(settings);

server.on("clientConnected", function (client) {
  console.log("client.id", client.id);
  console.log("client.address", client.connection.stream.remoteAddress);
  console.log("==================================================");
});

// fired when a message is received
server.on("published", function (packet, client) {
  var message = packet.payload.toString("utf8");
  console.log("messageId", packet.messageId);
  console.log("payload", packet.payload);
  console.log("qos", packet.qos);
  console.log("retain", packet.retain);
  console.log("message", message);
  console.log("--------------------------------------------------");
});

server.on("ready", setup);

// fired when the mqtt server is ready
function setup() {
  console.log("MQTT broker running");
}
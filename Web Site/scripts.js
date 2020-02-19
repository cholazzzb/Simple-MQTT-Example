var mqtt;
var reconnectTimeout = 2000;
var host = "localhost";
var port = 3000;

function onMessageArrived(msg) {
  switch (msg.destinationName) {
    case "topic3":
      console.log(msg.payloadString);
    case "topic4":
      console.log(msg.payloadString);
  }
}
function onConnect() {
  console.log("Connected ");
  mqtt.subscribe("topic3");
  mqtt.subscribe("topic4");
  setInterval(publishMQTT, 1000);
}

function MQTTconnect() {
  console.log("connecting to " + host + " " + port);
  mqtt = new Paho.MQTT.Client(host, port, "clientjs");
  var options = {
    timeout: 3,
    onSuccess: onConnect,
    onFailure: onFailure
  };
  mqtt.onMessageArrived = onMessageArrived;
  mqtt.connect(options);
}

function onFailure(message) {
  console.log("Connection Attempt to Host " + host + "Failed");
  setTimeout(MQTTconnect, reconnectTimeout);
}

function onConnectionLost(responseObject) {
  console.log("oow");
  if (responseObject.errorCode !== 0) {
    console.log("onConnectionLost:" + responseObject.errorMessage);
  }
}

function publishMQTT() {
  var time = new Date();
  value = Math.round((Math.abs(Math.sin(time.getSeconds())) * 100) % 255);

  message1 = new Paho.MQTT.Message(value.toString());
  message1.destinationName = "topic1";
  mqtt.send(message1);
  console.log("topic 1 Published");
  message2 = new Paho.MQTT.Message(value.toString());
  message2.destinationName = "topic2";
  mqtt.send(message1);
  console.log("topic 2 Published");
}

MQTTconnect();

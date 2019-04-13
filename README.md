# Microgreen WiFi Controller

## Next steps:

### create MQTT broker on AWS

### Create MQTT mananger in Python on AWS: http://www.steves-internet-guide.com/python-mqtt-publish-subscribe/

This simple mananger should be able just to start, connect to broker, send commands (received via terminal on execution such as 'controller.py light-on') to nodeMCU and confirm reception (such as 'commands received by edge device'). In the next level of implementation, an app or just another terminal controlled Python code will call this controllet.py when it's needed.


### Add MQTT connection to NodeMCU directed to Broker: https://www.filipeflop.com/blog/controle-monitoramento-iot-nodemcu-e-mqtt/

This code should just stay connected to broker, subscribe to some channels, interpret and execute received commands. 
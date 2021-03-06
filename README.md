# Microgreen WiFi Controller

Simple connected control system for domestic microgreen environmental control using free software and open source hardware.

Software:
    
    Connection: WiFi
    Protocol: MQTT
    Controller interface: Python

Hardware:
    
    MCU: NodeMCU V1.0
    Board CAD: Eagle

### - Use MQTT free online service
    
    https://www.cloudmqtt.com/

## Next steps:

### - Read RTC data

    https://www.filipeflop.com/blog/relogio-rtc-ds1307-arduino/
    - Works with 5V I2C

### - Create MQTT mananger in Python on AWS: 

http://www.steves-internet-guide.com/python-mqtt-publish-subscribe/

This simple mananger should be able just to start, connect to broker, send commands (received via terminal on execution such as 'controller.py light-on') to nodeMCU and confirm reception (such as 'commands received by edge device'). In the next level of implementation, an app or just another terminal controlled Python code will call this controllet.py when it's needed.


### - Add MQTT connection to NodeMCU directed to Broker: 

https://www.filipeflop.com/blog/controle-monitoramento-iot-nodemcu-e-mqtt/
https://techtutorialsx.com/2017/04/09/esp8266-connecting-to-mqtt-broker/   < MQTT User and Password
https://github.com/ItKindaWorks/ESP8266/issues/9   < Nice example using NodeMCU MAC to name device, also using MQTT Username and Password

This code should just stay connected to broker, subscribe to some channels, interpret and execute received commands. 

## Ideas/Future Implementation:

### - Telegram bot as interface
### - API as interface
### - Online database to store sensing data 
### - Real Time Clock


https://www.w3schools.com/python/python_mysql_getstarted.asp

# Microgreen WiFi Controller

Simple connected control system for domestic microgreen environmental control using free software and open source hardware.

Software:
    
    Connection: WiFi
    Protocol: MQTT
    Controller interface: Python

Hardware:
    
    MCU: NodeMCU V1.0
    Board CAD: Eagle

## Next steps:

### - Create MQTT broker on AWS

https://medium.com/@achildrenmile/mqtt-broker-on-aws-ec2-hands-on-install-configure-test-out-f12dd2f5c9d0

#### Installing mosquitto on ec2 machine:

Install dependencies:

    sudo yum group install "Development Tools" //to be able to run cmake
    sudo yum install cmake // to be able to compile libwebsockets    
    whereis gcc // to check if gcc is avaiable
    sudo yum install git //to be able to copy libwebsockets repository
    git clone https://github.com/warmcat/libwebsockets.git
    sudo yum install -y openssl-devel
    cd libwebsockets
    mkdir build
    cd build
    cmake .. -DCMAKE_C_COMPILER=/usr/bin/gcc
    make
    sudo make install
    ldconfig

links:
https://www.cyberciti.biz/faq/centos-rhel-7-redhat-linux-install-gcc-compiler-development-tools/
https://stackoverflow.com/questions/15051347/how-do-i-correctly-set-a-cmakelists-txt-file
http://blog.yatis.io/install-secure-robust-mosquitto-mqtt-broker-aws-ubuntu/
https://github.com/eclipse/mosquitto/issues/699

Add the repository:

    sudo wget http://download.opensuse.org/repositories/home:/oojah:/mqtt/CentOS_CentOS-7/home:oojah:mqtt.repo -O /etc/yum.repos.d/mqtt.repo

Installing:

    -- stoped here (error: can't find libwebsocket)
    sudo yum install mosquitto mosquitto-clients

#### Configuring Mosquitto:

    sudo nano /etc/mosquitto/mosquitto.conf


### - Create MQTT mananger in Python on AWS: 

http://www.steves-internet-guide.com/python-mqtt-publish-subscribe/

This simple mananger should be able just to start, connect to broker, send commands (received via terminal on execution such as 'controller.py light-on') to nodeMCU and confirm reception (such as 'commands received by edge device'). In the next level of implementation, an app or just another terminal controlled Python code will call this controllet.py when it's needed.


### - Add MQTT connection to NodeMCU directed to Broker: 

https://www.filipeflop.com/blog/controle-monitoramento-iot-nodemcu-e-mqtt/

This code should just stay connected to broker, subscribe to some channels, interpret and execute received commands. 

## Ideas/Future Implementation:

### - Telegram bot as interface
### - API as interface
### - Online database to store sensing data 

https://www.w3schools.com/python/python_mysql_getstarted.asp

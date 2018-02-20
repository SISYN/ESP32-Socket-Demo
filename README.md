# ESP32 Real-Time Socket Demo
## Published by [Dan Lindsey](http://mdlindsey.com)

### NodeJS
This directory contains the NodeJS server file you will need to run to allow data transmission from the ESP32 to the web browser client(s). Note, you will have to install all dependencies, so use the following command.

```
cd /path/to/your/nodejs/file
npm install
```

### ESP32
This program was compiled in the Arduino IDE, so if you're using `PlatformIO` package for `Atom` or some other IDE, you will need to include the `Arduino` base library, like so.

```
#include <Arduino.h>
```

This example uses the [NodeJoy Library](https://github.com/sisyn/nodejoy) to conveniently fetch the device's WiFi MAC address as a `String` but you can remove that line if you don't need it and then you can remove the `<NodeJoy.h>` directive.

### ReactJS
This is just a front-end sample of how you could setup a Socket.io client server. There are many, better examples available online, so I would suggest scraping this for an example that suits your project.

However, if you want to implement this on your portfolio as I did, I do have my full portfolio template on GitHub as well, located at [SISYN/React-Portfolio-Template](https://github.com/sisyn/react-portfolio-template).

Instalación

Para ejecutar el proyecto es necesario instalar Node.js, Node-RED y Arduino IDE.

1. Instalación de Node.js
Ingresa a la página oficial de Node.js.
Descarga la versión LTS correspondiente a Windows.
Ejecuta el instalador.
Completa la instalación manteniendo las opciones predeterminadas.
Abre el Símbolo del sistema —CMD— y ejecuta:
node --version && npm --version

Debe aparecer un resultado similar a:

v18.15.0
9.5.0

Los números pueden ser diferentes dependiendo de la versión instalada. Node-RED recomienda utilizar una versión LTS de Node.js. Documentación oficial de Node-RED.

2. Instalación de Node-RED

En CMD ejecuta:

npm install -g node-red

Cuando finalice la instalación, inicia Node-RED con:

node-red

Después abre en el navegador:

http://localhost:1880

La ventana de CMD debe permanecer abierta mientras se utiliza Node-RED.

Para acceder al Dashboard utiliza:

http://localhost:1880/ui
3. Instalación de nodos adicionales

Dentro de Node-RED:

Abre el menú principal.
Selecciona Manage palette.
Ingresa a la pestaña Install.
Busca e instala:
node-red-dashboard
node-red-node-serialport

Estos paquetes permiten crear el Dashboard y comunicarse con la ESP32 mediante el puerto serial.

4. Instalación de Arduino IDE
Ingresa a la página oficial de Arduino.
Descarga Arduino IDE para Windows.
Ejecuta el instalador.
Completa la instalación manteniendo las opciones recomendadas.
5. Instalación de la tarjeta ESP32

En Arduino IDE:

Abre File → Preferences.
Busca Additional Boards Manager URLs.
Agrega la siguiente dirección oficial:
https://espressif.github.io/arduino-esp32/package_esp32_index.json
Presiona OK.
Abre Tools → Board → Boards Manager.
Busca:
esp32
Instala el paquete esp32 by Espressif Systems.

La URL anterior corresponde al paquete estable oficial de Arduino-ESP32. Documentación de Espressif.

Si el proyecto fue probado específicamente con la versión 2.0.17, selecciónala en el administrador antes de presionar Install.

La URL de Bluepad32 solamente es necesaria para proyectos que utilicen controles Bluetooth compatibles con esa biblioteca. Para este proyecto con BME680, NeoPixel y comunicación serial se puede utilizar el paquete oficial de Espressif.

6. Instalación de las bibliotecas

En Arduino IDE:

Abre Tools → Manage Libraries.
Busca e instala:
Adafruit BME680 Library
Adafruit Unified Sensor
Adafruit NeoPixel
7. Selección de la placa
Conecta la ESP32 mediante USB.
Abre Tools → Board.
Selecciona el modelo correspondiente. Para una ESP32 genérica puede utilizarse:
ESP32 Dev Module
Abre Tools → Port.
Selecciona el puerto COM de la ESP32.
Compila y carga el programa.
8. Ejecución del proyecto
Carga el programa en la ESP32.
Cierra el Monitor Serial de Arduino IDE.
Ejecuta Node-RED:
node-red
Abre el editor:
http://localhost:1880
Importa el flujo del proyecto.
Configura el puerto serial con una velocidad de 9600 baudios.
Presiona Deploy.
Abre el Dashboard:
http://localhost:1880/ui

Es importante cerrar el Monitor Serial antes de utilizar Node-RED, ya que ambos programas no pueden controlar el mismo puerto COM simultáneamente.

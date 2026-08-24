# Welcome Kit Galileo – ESP32, BME680 y Node-RED

Sistema de monitoreo y control desarrollado con el **Welcome Kit de Universidad Galileo**.

El proyecto permite medir temperatura, humedad y resistencia de gases mediante un sensor BME680. También permite controlar tres NeoPixel desde un Dashboard de Node-RED, utilizando MQTT y comunicación serial.

## Características

- Medición de temperatura.
- Medición de humedad.
- Lectura de resistencia de gases.
- Control de tres NeoPixel.
- Selector de color.
- Control de brillo.
- Encendido y apagado.
- Dashboard accesible desde computadora o teléfono.
- Comunicación entre computadoras mediante MQTT.
- Comunicación local entre Node-RED y ESP32 mediante USB/Serial.

## Arquitectura del sistema

```text
Teléfono o PC transmisora
           ↓
        Node-RED
           ↓
          MQTT
           ↓
   PC receptora con Node-RED
           ↓
       USB/Serial
           ↓
 ESP32 + BME680 + NeoPixel

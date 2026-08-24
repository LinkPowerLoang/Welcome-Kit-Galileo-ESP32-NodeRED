# Welcome Kit Galileo: ESP32, BME680 y Node-RED

Sistema de monitoreo y control desarrollado con el **Welcome Kit de Universidad Galileo**.

Este proyecto permite medir temperatura, humedad y resistencia de gases mediante un sensor BME680. También permite controlar tres NeoPixel desde un Dashboard de Node-RED utilizando MQTT y comunicación serial.

---

## Características

- Medición de temperatura en grados Celsius.
- Medición de humedad relativa.
- Lectura de resistencia de gases.
- Control de tres NeoPixel.
- Encendido y apagado desde Node-RED.
- Selector visual de color.
- Control de brillo de 0 a 255.
- Visualización mediante indicadores y gráficas.
- Dashboard accesible desde una computadora o teléfono.
- Comunicación entre computadoras mediante MQTT.
- Comunicación local entre Node-RED y ESP32 mediante USB/Serial.

---

## Funcionamiento general

El sistema utiliza dos computadoras:

1. La computadora transmisora contiene los controles del Dashboard.
2. La computadora receptora tiene conectada la ESP32 mediante USB.
3. Las dos computadoras intercambian información mediante MQTT.
4. La ESP32 controla los NeoPixel y realiza las mediciones del BME680.

```text
Teléfono o PC transmisora
           │
           ▼
        Node-RED
           │
           ▼
          MQTT
           │
           ▼
   PC receptora con Node-RED
           │
           ▼
       USB/Serial
           │
           ▼
 ESP32 + BME680 + NeoPixel
```

La ESP32 no necesita conectarse directamente a una red Wi-Fi, ya que se comunica localmente con la computadora receptora mediante USB.

---

## Componentes

| Componente | Cantidad |
|:---|:---:|
| ESP32 del Welcome Kit Galileo | 1 |
| Sensor BME680 | 1 |
| NeoPixel | 3 |
| Cables de conexión | Varios |
| Cable USB | 1 |
| Computadora con Node-RED | 1 |
| Teléfono o segunda computadora | Opcional |

---

## Conexiones

### Sensor BME680

| Pin del BME680 | Pin de la ESP32 |
|:---|:---:|
| VDD o VCC | 3V3 |
| VSS o GND | GND |
| SDI o SDA | GPIO 21 |
| SCL | GPIO 22 |

También se pueden utilizar otros pines I²C modificando las siguientes líneas del programa:

```cpp
#define SDA_BME680 21
#define SCL_BME680 22
```

Por ejemplo:

```cpp
#define SDA_BME680 32
#define SCL_BME680 33
```

### NeoPixel

| Conexión NeoPixel | ESP32 |
|:---|:---:|
| DIN del primer NeoPixel | GPIO 25 |
| VCC | 5V |
| GND | GND |

Los tres NeoPixel deben conectarse en cadena:

```text
GPIO 25 ──► DIN NeoPixel 1
DOUT 1  ──► DIN NeoPixel 2
DOUT 2  ──► DIN NeoPixel 3
```

Todos los NeoPixel deben compartir la misma alimentación y tierra.

---

# Instalación

## 1. Instalar Node.js

Ingresa a la página oficial:

[Descargar Node.js](https://nodejs.org/en/download)

1. Descarga la versión **LTS** correspondiente a Windows.
2. Ejecuta el instalador.
3. Mantén las opciones predeterminadas.
4. Al terminar, abre el Símbolo del sistema o CMD.

Verifica la instalación con:

```bash
node --version
npm --version
```

Debe aparecer un resultado similar a:

```text
v18.15.0
9.5.0
```

Las versiones pueden ser diferentes dependiendo de la versión instalada.

---

## 2. Instalar Node-RED

Abre CMD y ejecuta:

```bash
npm install -g node-red
```

Cuando termine la instalación, inicia Node-RED con:

```bash
node-red
```

Node-RED mostrará una dirección local. Normalmente es:

```text
http://localhost:1880
```

Abre esa dirección en el navegador para ingresar al editor.

> La ventana de CMD debe permanecer abierta mientras Node-RED está funcionando.

---

## 3. Instalar los nodos adicionales

Dentro de Node-RED:

1. Abre el menú principal.
2. Selecciona **Manage palette**.
3. Ingresa a la pestaña **Install**.
4. Busca e instala los siguientes paquetes:

```text
node-red-dashboard
node-red-node-serialport
```

Estos paquetes permiten crear el Dashboard y establecer la comunicación serial con la ESP32.

---

## 4. Instalar Arduino IDE

Descarga Arduino IDE desde:

[Descargar Arduino IDE](https://www.arduino.cc/en/software)

1. Selecciona la versión correspondiente a Windows.
2. Ejecuta el instalador.
3. Completa la instalación con las opciones recomendadas.

---

## 5. Instalar la placa ESP32

En Arduino IDE:

1. Abre **File → Preferences**.
2. Busca **Additional Boards Manager URLs**.
3. Agrega la siguiente dirección:

```text
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

4. Presiona **OK**.
5. Abre **Tools → Board → Boards Manager**.
6. Busca `esp32`.
7. Instala **esp32 by Espressif Systems**.

Si el proyecto requiere específicamente la versión `2.0.17`, selecciónala antes de presionar **Install**.

Después selecciona la placa:

```text
Tools → Board → ESP32 Arduino → ESP32 Dev Module
```

---

## 6. Instalar las bibliotecas

Dentro de Arduino IDE:

1. Abre **Tools → Manage Libraries**.
2. Busca e instala las siguientes bibliotecas:

| Biblioteca | Función |
|:---|:---|
| Adafruit BME680 Library | Lectura del sensor BME680 |
| Adafruit Unified Sensor | Dependencia para sensores Adafruit |
| Adafruit NeoPixel | Control de los tres NeoPixel |

---

## 7. Cargar la programación

1. Conecta la ESP32 a la computadora mediante USB.
2. Abre el programa `.ino`.
3. Selecciona la placa ESP32.
4. Selecciona el puerto COM correspondiente.
5. Presiona **Upload**.
6. Espera a que la programación termine.
7. Cierra el Monitor Serial antes de utilizar Node-RED.

> Node-RED y el Monitor Serial de Arduino IDE no pueden utilizar simultáneamente el mismo puerto COM.

---

# Configuración de Node-RED

## Configuración serial

El nodo serial debe configurarse con los siguientes valores:

| Configuración | Valor |
|:---|:---:|
| Baud Rate | 9600 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |
| Split input | `\n` |
| Deliver | ASCII strings |
| Add character to output | `\n` |

---

## Importar el flujo

1. Abre Node-RED.
2. Ingresa al menú principal.
3. Selecciona **Import**.
4. Selecciona el archivo:

```text
node-red-flow.json
```

5. Presiona **Import**.
6. Configura el broker MQTT.
7. Configura el puerto serial de la ESP32.
8. Presiona **Deploy**.

---

# Control de los NeoPixel

La ESP32 reconoce los siguientes comandos:

| Acción | Mensaje enviado |
|:---|:---|
| Encender los tres NeoPixel | `1` |
| Apagar los tres NeoPixel | `0` |
| Cambiar a blanco | `COLOR:255,255,255` |
| Cambiar a rosa | `COLOR:255,105,180` |
| Cambiar a rojo | `COLOR:255,0,0` |
| Cambiar a verde | `COLOR:0,255,0` |
| Cambiar a azul | `COLOR:0,0,255` |
| Cambiar el brillo | `BRILLO:100` |

El brillo puede configurarse entre:

```text
0 = brillo mínimo
255 = brillo máximo
```

Después de recibir la señal `1`, los colores y el brillo pueden modificarse sin volver a enviar la señal de encendido.

Cuando recibe `0`, los NeoPixel se apagan. Los nuevos colores y valores de brillo se guardan, pero no se aplican hasta recibir nuevamente `1`.

---

# Información del BME680

La ESP32 realiza una lectura del BME680 cada dos segundos.

Los datos son enviados hacia Node-RED en formato JSON:

```json
{
  "temperatura": 25.40,
  "humedad": 60.20,
  "gas": 48.75
}
```

## Mediciones

| Medición | Unidad |
|:---|:---:|
| Temperatura | °C |
| Humedad | % |
| Resistencia de gas | kΩ |

> El BME680 detecta cambios generales relacionados con gases y compuestos orgánicos volátiles. La lectura de gas no identifica exactamente qué sustancia está presente.

---

# Topics MQTT

| Información | Topic MQTT |
|:---|:---|
| Control de NeoPixel | `wk/mg/1` |
| Temperatura | `wk/bme680/temperatura` |
| Humedad | `wk/bme680/humedad` |
| Gas | `wk/bme680/gas` |

El topic `wk/mg/1` se utiliza únicamente para enviar comandos a los NeoPixel.

Los datos del sensor se publican en topics diferentes para evitar ciclos de comunicación.

---

# Dashboard

El Dashboard permite:

- Encender y apagar los NeoPixel.
- Seleccionar cualquier color.
- Modificar el brillo.
- Visualizar la temperatura.
- Visualizar la humedad.
- Visualizar la resistencia de gases.
- Consultar gráficas en tiempo real.

Para abrir el Dashboard desde la computadora:

```text
http://localhost:1880/ui
```

---

## Acceso desde un teléfono

El teléfono y la computadora deben estar conectados a la misma red Wi-Fi.

En la computadora abre CMD y ejecuta:

```bash
ipconfig
```

Busca la dirección IPv4, por ejemplo:

```text
192.168.1.25
```

En el navegador del teléfono escribe:

```text
http://192.168.1.25:1880/ui
```

No utilices `localhost` desde el teléfono, porque esa dirección se refiere al propio teléfono.

---

# Imágenes del proyecto

## Flujo de Node-RED

![Flujo de Node-RED](images/flujo-node-red.png)

## Dashboard

![Dashboard de Node-RED](images/dashboard.png)

## Conexión del circuito

![Conexión del circuito](images/conexiones.png)

Para que las imágenes aparezcan correctamente, crea una carpeta llamada `images` y utiliza exactamente estos nombres:

```text
images/
├── flujo-node-red.png
├── dashboard.png
└── conexiones.png
```

---

# Estructura del repositorio

```text
Welcome-Kit-Galileo-ESP32-NodeRED/
├── README.md
├── Welcome_Kit_BME680_NeoPixel.ino
├── node-red-flow.json
└── images/
    ├── flujo-node-red.png
    ├── dashboard.png
    └── conexiones.png
```

---

# Solución de problemas

## El BME680 no aparece

Verifica:

- Que VCC esté conectado a 3V3.
- Que GND esté conectado a GND.
- Que SDA esté conectado al GPIO 21.
- Que SCL esté conectado al GPIO 22.
- Que SDA y SCL no estén intercambiados.
- Que las bibliotecas estén instaladas.

## Node-RED no recibe información

Verifica:

- Que el puerto COM sea correcto.
- Que la velocidad sea de 9600 baudios.
- Que el Monitor Serial esté cerrado.
- Que el nodo Serial In indique `connected`.
- Que el carácter separador sea `\n`.

## Solo enciende un NeoPixel

Verifica:

- Que la cantidad esté definida como `3`.
- Que la señal entre por DIN.
- Que DOUT del primero esté conectado a DIN del segundo.
- Que DOUT del segundo esté conectado a DIN del tercero.
- Que todos compartan VCC y GND.

## El teléfono no abre el Dashboard

Verifica:

- Que el teléfono y la computadora estén en la misma red.
- Que Node-RED permanezca ejecutándose.
- Que se esté utilizando la dirección IPv4 correcta.
- Que el Firewall de Windows permita el puerto 1880.

---

# Archivos importantes

| Archivo | Descripción |
|:---|:---|
| `README.md` | Documentación del proyecto |
| `Welcome_Kit_BME680_NeoPixel.ino` | Programa de la ESP32 |
| `node-red-flow.json` | Flujo importable de Node-RED |
| `images/` | Capturas y fotografías del proyecto |

---

# Autor

Proyecto desarrollado utilizando el **Welcome Kit de Universidad Galileo**.

## Repositorio

[Welcome-Kit-Galileo-ESP32-NodeRED](https://github.com/LinkPowerLoang/Welcome-Kit-Galileo-ESP32-NodeRED)

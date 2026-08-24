# Welcome Kit Galileo: ESP32, BME680 y Node-RED

Proyecto desarrollado utilizando el **Welcome Kit de Universidad Galileo**.

El sistema permite controlar tres NeoPixel desde un Dashboard de Node-RED. Es posible encenderlos, apagarlos, seleccionar su color y controlar su brillo.

También permite recibir información de un sensor BME680 para visualizar temperatura, humedad y resistencia de gases.

La comunicación entre computadoras se realiza mediante MQTT, mientras que la ESP32 se comunica localmente con Node-RED por medio del puerto USB/Serial.

---

# Características

- Control de tres NeoPixel.
- Encendido y apagado desde Node-RED.
- Selección visual de colores.
- Control de brillo entre 0 y 255.
- Lectura de temperatura.
- Lectura de humedad.
- Lectura de resistencia de gases.
- Comunicación MQTT entre computadoras.
- Comunicación serial entre Node-RED y ESP32.
- Dashboard accesible desde una computadora o teléfono.

---

# Instalación

## 1. Instalar Node.js

Ingresa a la página oficial:

[Descargar Node.js](https://nodejs.org/en/download)

1. Descarga la versión **LTS** para Windows.
2. Ejecuta el instalador.
3. Mantén las opciones predeterminadas.
4. Al finalizar, abre el Símbolo del sistema o CMD.

Comprueba la instalación ejecutando:

```bash
node --version
npm --version
```

Debe aparecer un resultado similar a:

```text
v18.15.0
9.5.0
```

Los números pueden cambiar dependiendo de la versión instalada.

---

## 2. Instalar Node-RED

Abre CMD y ejecuta:

```bash
npm install -g node-red
```

Después de finalizar la instalación, inicia Node-RED con:

```bash
node-red
```

Abre la siguiente dirección en el navegador:

```text
http://localhost:1880
```

Para acceder al Dashboard utiliza:

```text
http://localhost:1880/ui
```

> La ventana de CMD debe permanecer abierta mientras Node-RED esté funcionando.

---

## 3. Instalar los nodos adicionales

Dentro de Node-RED:

1. Abre el menú principal.
2. Selecciona **Manage palette**.
3. Ingresa a la pestaña **Install**.
4. Instala los siguientes paquetes:

```text
node-red-dashboard
node-red-node-serialport
```

Estos paquetes permiten utilizar el Dashboard y establecer la comunicación serial con la ESP32.

---

## 4. Instalar Arduino IDE

Descarga Arduino IDE desde:

[Descargar Arduino IDE](https://www.arduino.cc/en/software)

Para instalarlo:

1. Descarga la versión correspondiente a Windows.
2. Ejecuta el instalador.
3. Mantén las opciones recomendadas.
4. Espera a que finalice la instalación.
5. Abre Arduino IDE.

---

## 5. Instalar el controlador USB CP210x

Este paso solamente es necesario si Arduino IDE no reconoce la ESP32 o si el puerto COM no aparece en:

```text
Tools → Port
```

El repositorio incluye el controlador USB CP210x para Windows:

[Descargar controlador CP210x para Windows](CP210x_Universal_Windows_Driver.zip)

Para instalarlo:

1. Descarga el archivo:

```text
CP210x_Universal_Windows_Driver.zip
```

2. Haz clic derecho sobre el archivo ZIP.
3. Selecciona **Extraer todo**.
4. Abre la carpeta extraída.
5. Busca el archivo:

```text
silabser.inf
```

> Si Windows oculta las extensiones, el archivo puede aparecer únicamente como `silabser`. Su tipo será “Información sobre instalación”.

6. Haz clic derecho sobre el archivo `silabser.inf`.
7. Selecciona **Instalar**.

En Windows 11 puede ser necesario seleccionar:

```text
Mostrar más opciones → Instalar
```

8. Confirma el permiso de administrador si Windows lo solicita.
9. Espera a que Windows confirme que la instalación terminó correctamente.
10. Desconecta y vuelve a conectar la ESP32.
11. Reinicia Arduino IDE.
12. Verifica que el puerto aparezca en:

```text
Tools → Port
```

> No es necesario instalar este controlador si la ESP32 ya aparece correctamente en un puerto COM.

---

## 6. Instalar la tarjeta ESP32

En Arduino IDE:

1. Abre **File → Preferences**.
2. Busca **Additional Boards Manager URLs**.
3. Agrega la siguiente dirección:

```text
https://espressif.github.io/arduino-esp32/package_esp32_index.json
```

4. Presiona **OK**.
5. Abre **Tools → Board → Boards Manager**.
6. Busca:

```text
esp32
```

7. Instala **esp32 by Espressif Systems**.

Si el proyecto requiere la versión `2.0.17`, selecciónala antes de presionar **Install**.

Después selecciona la placa:

```text
Tools → Board → ESP32 Arduino → ESP32 Dev Module
```

---

## 7. Instalar las bibliotecas

En Arduino IDE:

1. Abre **Tools → Manage Libraries**.
2. Busca e instala las siguientes bibliotecas:

| Biblioteca | Función |
|:---|:---|
| Adafruit BME680 Library | Lectura del sensor BME680 |
| Adafruit Unified Sensor | Dependencia para los sensores Adafruit |
| Adafruit NeoPixel | Control de los NeoPixel |

---

## 8. Programación de la ESP32

La programación completa de Arduino se encuentra disponible en el siguiente archivo:

[Ver programación de la ESP32](ProgramacionWelcomeKit2026/ProgramacionWelcomeKit2026.ino)

Para cargar la programación:

1. Conecta la ESP32 a la computadora mediante un cable USB.
2. Abre el archivo `ProgramacionWelcomeKit2026.ino`.
3. Selecciona la placa ESP32.
4. Selecciona el puerto COM correspondiente.
5. Presiona el botón **Upload**.
6. Espera hasta que Arduino IDE confirme que la carga terminó.
7. Cierra el Monitor Serial.
8. Inicia Node-RED.

> Node-RED y el Monitor Serial de Arduino IDE no pueden utilizar simultáneamente el mismo puerto COM.

---

# Broker MQTT

Para realizar las pruebas de comunicación MQTT se utiliza el cliente web de HiveMQ:

[HiveMQ WebSocket Client](https://www.hivemq.com/demos/websocket-client/)

Este cliente permite publicar y recibir mensajes utilizando los mismos topics configurados en Node-RED.

El topic utilizado para controlar los NeoPixel es:

```text
wk/mg/1
```

---

# Flujo de Node-RED

El flujo está dividido en dos partes principales: envío de comandos y recepción de información.

## Envío de comandos

La primera parte contiene los controles del Dashboard:

```text
Control de colores → Function Color
Control de brillo → Function Brillo
Encendido/Apagado → Function Encendido/Apagado
```

Las tres funciones se conectan al nodo MQTT Out que utiliza el siguiente topic:

```text
wk/mg/1
```

## Recepción de comandos

La segunda parte recibe los mensajes MQTT y los envía a la ESP32 mediante el puerto serial:

```text
MQTT In → Serial Out → ESP32
```

Las respuestas y mediciones de la ESP32 se reciben mediante el nodo Serial In:

```text
ESP32 → Serial In ─┬→ Function Mensaje Brillo
                   ├→ Function Mensaje Color
                   └→ Function Datos Sensor
```

## Imagen del flujo

La siguiente imagen muestra el flujo completo desarrollado en Node-RED:

![Flujo completo de Node-RED](Imagenes/flujo-node-red.png)

---

# Funciones de Node-RED

## Function – Color

Esta función recibe el color hexadecimal seleccionado en el Dashboard y lo convierte a formato RGB.

```javascript
let color = String(msg.payload).replace("#", "");

let rojo = parseInt(color.substring(0, 2), 16);
let verde = parseInt(color.substring(2, 4), 16);
let azul = parseInt(color.substring(4, 6), 16);

msg.payload = "COLOR:" + rojo + "," + verde + "," + azul;

return msg;
```

Ejemplo:

```text
Entrada: #ff69b4
Salida: COLOR:255,105,180
```

---

## Function – Brillo

Esta función recibe el valor seleccionado en el control de brillo y lo limita entre 0 y 255.

```javascript
let brillo = Number(msg.payload);

brillo = Math.max(0, Math.min(255, brillo));

msg.payload = "BRILLO:" + brillo;

return msg;
```

Ejemplo:

```text
Entrada: 100
Salida: BRILLO:100
```

---

## Function – Encendido y apagado

Esta función recibe el estado del Switch del Dashboard.

```javascript
let estado = Number(msg.payload);

if (estado === 1) {
    msg.payload = "1";
    return msg;
}

if (estado === 0) {
    msg.payload = "0";
    return msg;
}

return null;
```

El funcionamiento es:

| Estado del Switch | Mensaje |
|:---|:---:|
| Encendido | `1` |
| Apagado | `0` |

---

# Funciones para recibir mensajes

## Function – Mensaje de brillo

Esta función permite mostrar únicamente el valor del brillo enviado por la ESP32.

```javascript
let mensaje = String(msg.payload).trim();

if (mensaje.startsWith("BRILLO:")) {
    let valor = mensaje.substring(7);

    msg.payload = Number(valor);

    return msg;
}

return null;
```

Ejemplo:

```text
Entrada: BRILLO:100
Salida: 100
```

---

## Function – Mensaje de color

Esta función permite mostrar únicamente el color confirmado por la ESP32.

```javascript
let mensaje = String(msg.payload).trim();

if (!mensaje.startsWith("COLOR:")) {
    return null;
}

let valores = mensaje.substring(6).split(",");

if (valores.length !== 3) {
    return null;
}

let rojo = Number(valores[0]);
let verde = Number(valores[1]);
let azul = Number(valores[2]);

msg.payload =
    "RGB(" +
    rojo + "," +
    verde + "," +
    azul + ")";

return msg;
```

Ejemplo:

```text
Entrada: COLOR:255,105,180
Salida: RGB(255,105,180)
```

---

## Function – Datos del sensor

La ESP32 envía los datos del BME680 en formato JSON.

```javascript
let texto = String(msg.payload).trim();

if (!texto.startsWith("{")) {
    return null;
}

let datos;

try {
    datos = JSON.parse(texto);
}
catch (error) {
    return null;
}

msg.payload =
    "Temperatura: " + datos.temperatura + " °C | " +
    "Humedad: " + datos.humedad + " % | " +
    "Gas: " + datos.gas + " kΩ";

return msg;
```

Ejemplo de información mostrada:

```text
Temperatura: 25.40 °C | Humedad: 60.20 % | Gas: 48.75 kΩ
```

---

# Configuración serial

Los nodos Serial In y Serial Out deben utilizar la misma configuración:

| Configuración | Valor |
|:---|:---:|
| Baud Rate | 9600 |
| Data Bits | 8 |
| Parity | None |
| Stop Bits | 1 |
| Split input | `\n` |
| Deliver | ASCII strings |
| Add character to output | `\n` |

Los dos nodos deben utilizar el mismo puerto COM y la misma configuración serial.

---

# Comandos utilizados

| Acción | Comando |
|:---|:---|
| Encender los NeoPixel | `1` |
| Apagar los NeoPixel | `0` |
| Cambiar el color | `COLOR:R,G,B` |
| Cambiar el brillo | `BRILLO:valor` |

Ejemplos:

```text
1
0
COLOR:255,105,180
BRILLO:100
```

---

# Archivos del proyecto

```text
Welcome-Kit-Galileo-ESP32-NodeRED/
├── README.md
├── CP210x_Universal_Windows_Driver.zip
├── Imagenes/
│   └── flujo-node-red.png
└── ProgramacionWelcomeKit2026/
    └── ProgramacionWelcomeKit2026.ino
```

| Archivo | Descripción |
|:---|:---|
| [`README.md`](README.md) | Documentación e instrucciones del proyecto |
| [`ProgramacionWelcomeKit2026.ino`](ProgramacionWelcomeKit2026/ProgramacionWelcomeKit2026.ino) | Programación completa de la ESP32 |
| [`CP210x_Universal_Windows_Driver.zip`](CP210x_Universal_Windows_Driver.zip) | Controlador USB CP210x para Windows |
| [`flujo-node-red.png`](Imagenes/flujo-node-red.png) | Imagen del flujo desarrollado en Node-RED |

---

# Repositorio

El proyecto completo se encuentra disponible en:

[Welcome-Kit-Galileo-ESP32-NodeRED](https://github.com/LinkPowerLoang/Welcome-Kit-Galileo-ESP32-NodeRED)

---

# Créditos

## Autor

**Mateo García**

- GitHub: [LinkPowerLoang](https://github.com/LinkPowerLoang)
- Estudiante de la carrera de Ingeniería.
- Seleccionado nacional de Robótica en 2020 y 2021.
- Actualmente, coach de la Selección Nacional de Robótica.

Proyecto desarrollado utilizando el **Welcome Kit de Universidad Galileo**.

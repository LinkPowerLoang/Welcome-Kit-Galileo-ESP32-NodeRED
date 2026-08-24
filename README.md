# Broker MQTT y HiveMQ WebSocket Client

Para transmitir los comandos entre las computadoras se utiliza MQTT.

Como herramienta de prueba se utiliza el cliente web de HiveMQ:

[HiveMQ WebSocket Client](https://www.hivemq.com/demos/websocket-client/)

Este cliente permite:

- Conectarse a un broker MQTT desde el navegador.
- Publicar mensajes.
- Suscribirse a topics.
- Comprobar si los mensajes están llegando correctamente.
- Probar el sistema sin instalar otro programa.

> HiveMQ WebSocket Client es el cliente de prueba utilizado para publicar y recibir mensajes. El broker es el servidor MQTT configurado dentro del cliente y en Node-RED.

---

## Configuración de conexión

En la sección **Connection** del cliente de HiveMQ configura:

| Configuración | Valor |
|:---|:---|
| Host | `broker.hivemq.com` |
| Port | `8884` |
| Client ID | Un nombre único |
| Username | Vacío |
| Password | Vacío |
| Keep Alive | `60` |
| SSL | Activado |
| Clean Session | Activado |

Ejemplo de Client ID:

```text
WelcomeKit-Galileo-PC1
```

Cada computadora o dispositivo debe utilizar un Client ID diferente.

Otros ejemplos:

```text
WelcomeKit-Galileo-PC2
WelcomeKit-Galileo-Telefono
WelcomeKit-Galileo-Pruebas
```

Después de completar la configuración, presiona:

```text
Connect
```

El cliente debe indicar que la conexión fue realizada correctamente.

---

## Publicar comandos

En la sección **Publish** configura:

| Configuración | Valor |
|:---|:---|
| Topic | `wk/mg/1` |
| QoS | `0` |
| Retain | Desactivado |
| Message | Comando que se desea enviar |

### Encender los NeoPixel

```text
Topic: wk/mg/1
Message: 1
```

### Apagar los NeoPixel

```text
Topic: wk/mg/1
Message: 0
```

### Cambiar el color a rosa

```text
Topic: wk/mg/1
Message: COLOR:255,105,180
```

### Cambiar el brillo

```text
Topic: wk/mg/1
Message: BRILLO:100
```

Después de escribir el mensaje, presiona:

```text
Publish
```

Node-RED recibirá el comando mediante el nodo MQTT In y lo enviará a la ESP32 por el puerto serial.

---

## Suscribirse al topic de control

En la sección **Subscriptions**:

1. Presiona **Add New Topic Subscription**.
2. Coloca el topic:

```text
wk/mg/1
```

3. Selecciona QoS `0`.
4. Presiona **Subscribe**.

Después de suscribirse, el cliente mostrará todos los mensajes publicados en ese topic.

---

## Suscribirse a los datos del BME680

Para recibir las mediciones del sensor se pueden agregar tres suscripciones:

| Información | Topic |
|:---|:---|
| Temperatura | `wk/bme680/temperatura` |
| Humedad | `wk/bme680/humedad` |
| Resistencia de gases | `wk/bme680/gas` |

También es posible recibir todos los datos del BME680 utilizando el comodín `#`:

```text
wk/bme680/#
```

Con esta suscripción se reciben todos los topics que comiencen con:

```text
wk/bme680/
```

---

## Configuración MQTT en Node-RED

Dentro del nodo MQTT de Node-RED utiliza el mismo broker:

| Configuración | Valor |
|:---|:---|
| Server | `broker.hivemq.com` |
| Port | `1883` |
| Protocol | MQTT |
| Client ID | Un nombre único |
| Username | Vacío |
| Password | Vacío |
| Keep Alive | `60` |

Ejemplo de Client ID para Node-RED:

```text
NodeRED-WelcomeKit-PC1
```

El cliente web utiliza el puerto seguro de WebSocket, mientras que Node-RED puede utilizar el puerto MQTT TCP. Ambos pueden intercambiar información si están conectados al mismo broker y utilizan los mismos topics.

---

## Prueba de comunicación

Para comprobar la comunicación:

1. Ejecuta Node-RED.
2. Verifica que el nodo MQTT indique `connected`.
3. Abre el [HiveMQ WebSocket Client](https://www.hivemq.com/demos/websocket-client/).
4. Conéctate al broker.
5. Suscríbete a:

```text
wk/mg/1
```

6. Publica el mensaje:

```text
1
```

7. Node-RED debe recibir el mensaje.
8. La ESP32 debe encender los tres NeoPixel.
9. Publica:

```text
0
```

10. Los tres NeoPixel deben apagarse.

---

## Consideraciones de seguridad

El broker público de HiveMQ debe utilizarse solamente para pruebas, prácticas educativas y demostraciones.

Los mensajes enviados a topics públicos podrían ser observados por otros usuarios. Por esta razón:

- No publiques contraseñas.
- No publiques información personal.
- No publiques tokens o credenciales.
- Utiliza topics difíciles de repetir accidentalmente.
- No lo utilices para sistemas críticos.

En lugar de un topic demasiado general como:

```text
wk/mg/1
```

se recomienda utilizar uno más específico:

```text
galileo/welcome-kit/equipo01/control
```

Los topics del sensor podrían organizarse así:

```text
galileo/welcome-kit/equipo01/temperatura
galileo/welcome-kit/equipo01/humedad
galileo/welcome-kit/equipo01/gas
```

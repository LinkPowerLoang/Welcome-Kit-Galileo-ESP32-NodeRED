#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>
#include <Adafruit_NeoPixel.h>

// =====================================================
// CONFIGURACIÓN DEL BME680
// =====================================================

#define SDA_BME680 32
#define SCL_BME680 33

Adafruit_BME680 bme;

bool bmeConectado = false;

unsigned long tiempoAnterior = 0;
const unsigned long intervaloLectura = 2000;

// =====================================================
// CONFIGURACIÓN DE LOS NEOPIXEL
// =====================================================

#define PIN_NEOPIXEL 25
#define CANTIDAD_LEDS 3

Adafruit_NeoPixel leds(
  CANTIDAD_LEDS,
  PIN_NEOPIXEL,
  NEO_GRB + NEO_KHZ800
);

// Color inicial: blanco
int rojoGuardado = 255;
int verdeGuardado = 255;
int azulGuardado = 255;

// Brillo inicial
int brilloGuardado = 100;

// Estado de los NeoPixel
bool sistemaActivo = false;

// =====================================================
// BUSCAR DISPOSITIVOS I2C
// =====================================================

void buscarDispositivosI2C() {
  Serial.println("BUSCANDO_I2C");

  int encontrados = 0;

  for (byte direccion = 1; direccion < 127; direccion++) {
    Wire.beginTransmission(direccion);

    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C_ENCONTRADO:0x");

      if (direccion < 16) {
        Serial.print("0");
      }

      Serial.println(direccion, HEX);

      encontrados++;
    }
  }

  if (encontrados == 0) {
    Serial.println("ERROR:NO_HAY_DISPOSITIVOS_I2C");
  }
}

// =====================================================
// FUNCIONES NEOPIXEL
// =====================================================

void mostrarColor() {
  leds.setBrightness(brilloGuardado);

  for (int i = 0; i < CANTIDAD_LEDS; i++) {
    leds.setPixelColor(
      i,
      leds.Color(
        rojoGuardado,
        verdeGuardado,
        azulGuardado
      )
    );
  }

  leds.show();
}

void apagarNeoPixel() {
  leds.clear();
  leds.show();
}

// =====================================================
// PROCESAR COMANDOS RECIBIDOS DESDE NODE-RED
// =====================================================

void procesarComando(String dato) {
  dato.trim();

  // Encender los tres NeoPixel
  if (dato == "1") {
    sistemaActivo = true;

    mostrarColor();

    Serial.println("ESTADO:ENCENDIDO");
  }

  // Apagar los tres NeoPixel
  else if (dato == "0") {
    sistemaActivo = false;

    apagarNeoPixel();

    Serial.println("ESTADO:APAGADO");
  }

  // Cambiar brillo
  else if (dato.startsWith("BRILLO:")) {
    int nuevoBrillo = dato.substring(7).toInt();

    brilloGuardado = constrain(nuevoBrillo, 0, 255);

    if (sistemaActivo) {
      mostrarColor();
    }

    Serial.print("BRILLO:");
    Serial.println(brilloGuardado);
  }

  // Cambiar color
  else if (dato.startsWith("COLOR:")) {
    String valores = dato.substring(6);

    int rojo;
    int verde;
    int azul;

    int resultado = sscanf(
      valores.c_str(),
      "%d,%d,%d",
      &rojo,
      &verde,
      &azul
    );

    if (resultado == 3) {
      rojoGuardado = constrain(rojo, 0, 255);
      verdeGuardado = constrain(verde, 0, 255);
      azulGuardado = constrain(azul, 0, 255);

      if (sistemaActivo) {
        mostrarColor();
      }

      Serial.print("COLOR:");
      Serial.print(rojoGuardado);
      Serial.print(",");
      Serial.print(verdeGuardado);
      Serial.print(",");
      Serial.println(azulGuardado);
    }
    else {
      Serial.println("ERROR:COLOR_INVALIDO");
    }
  }

  // Comando no reconocido
  else if (dato.length() > 0) {
    Serial.print("ERROR:COMANDO_INVALIDO:");
    Serial.println(dato);
  }
}

// =====================================================
// LEER Y ENVIAR DATOS DEL BME680
// =====================================================

void leerBME680() {
  if (!bmeConectado) {
    Serial.println("ERROR:BME680_NO_CONECTADO");
    return;
  }

  if (!bme.performReading()) {
    Serial.println("ERROR:LECTURA_BME680");
    return;
  }

  float temperatura = bme.temperature;
  float humedad = bme.humidity;

  // Convertir resistencia de gas de ohmios a kiloohmios
  float gases = bme.gas_resistance / 1000.0;

  // Enviar una línea JSON a Node-RED
  Serial.print("{\"temperatura\":");
  Serial.print(temperatura, 2);

  Serial.print(",\"humedad\":");
  Serial.print(humedad, 2);

  Serial.print(",\"gas\":");
  Serial.print(gases, 2);

  Serial.println("}");
}

// =====================================================
// SETUP
// =====================================================

void setup() {
  // Debe coincidir con Node-RED
  Serial.begin(9600);
  Serial.setTimeout(50);

  // Iniciar NeoPixel
  leds.begin();
  leds.setBrightness(brilloGuardado);
  apagarNeoPixel();

  // Iniciar comunicación I2C
  Wire.begin(SDA_BME680, SCL_BME680);

  delay(500);

  // Buscar dispositivos I2C
  buscarDispositivosI2C();

  // Buscar BME680 en 0x76
  bmeConectado = bme.begin(0x76);

  // Si no está en 0x76, buscar en 0x77
  if (!bmeConectado) {
    bmeConectado = bme.begin(0x77);
  }

  if (bmeConectado) {
    // Configuración del sensor
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150);

    Serial.println("BME680_LISTO");
  }
  else {
    Serial.println("ERROR:BME680_NO_ENCONTRADO");
  }

  Serial.println("ESP32_LISTO");
}

// =====================================================
// LOOP
// =====================================================

void loop() {
  // Recibir comandos de Node-RED
  if (Serial.available() > 0) {
    String comando = Serial.readStringUntil('\n');

    procesarComando(comando);
  }

  // Leer el BME680 cada 2 segundos
  unsigned long tiempoActual = millis();

  if (tiempoActual - tiempoAnterior >= intervaloLectura) {
    tiempoAnterior = tiempoActual;

    leerBME680();
  }
}
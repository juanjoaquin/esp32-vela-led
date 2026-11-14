
const int PIN_LED = 2;
const int FRECUENCIA = 5000;   // Hz
const int RESOLUCION = 8;      // brillo de 0 a 255

int brilloActual = 150;

void escribirBrillo(int brillo) {
  #if ESP_ARDUINO_VERSION_MAJOR >= 3
    ledcWrite(PIN_LED, brillo);
  #else
    ledcWrite(0, brillo);
  #endif
}

void setup() {
  #if ESP_ARDUINO_VERSION_MAJOR >= 3
    ledcAttach(PIN_LED, FRECUENCIA, RESOLUCION);
  #else
    ledcSetup(0, FRECUENCIA, RESOLUCION);
    ledcAttachPin(PIN_LED, 0);
  #endif
}

void loop() {
  int objetivo = random(60, 256);

  while (brilloActual != objetivo) {
    if (brilloActual < objetivo) brilloActual++;
    else brilloActual--;
    escribirBrillo(brilloActual);
    delay(random(2, 8));
  }

  // De vez en cuando, una pequeña ráfaga de viento (parpadeo rápido)
  if (random(0, 10) == 0) {
    for (int i = 0; i < 4; i++) {
      escribirBrillo(random(40, 120));
      delay(random(30, 80));
    }
  }

  delay(random(20, 120));
}
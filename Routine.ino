void runRoutine() {

  routine_running = true;
  Serial.println("Routine started...");
  // OLEDclear();
  OLEDClearButtonLabel(BUTTON_LEFT, NORMAL);

  getReady();

  for (int i = 0; i < REPS; i++) {
    OLEDProgressBar(i + 1, REPS, 3);
    holdIt(i);

    // Skip the last relax - you're done anyway
    if (i != (REPS - 1)) {
      relaxIt(i);
    }
  }

  finishIt();

  routine_running = false;
}

void myDelay(int ms) {

  while (ms > 0) {
    delay(1);
    rightButton.update();
    leftButton.update();
    --ms;
  }

  isRoomDark(); // Check if the light value changed so RGB LED can respond
}

void getReady(void) {

  Serial.println("Get Ready...");
  clearColorRGB();
  OLEDDisplayAction("GET READY", 1);
  blinkColorRGB(0, 0, 255, 5);

  for (int i = 0; i < READY_TIME; i++) {
    beep(BUZZER_DURATION);
    OLEDProgressBar((READY_TIME - i), READY_TIME, 1);
    myDelay(1000 - BUZZER_DURATION);
    Serial.print(".");
  }

  OLEDProgressBar(0, READY_TIME, 1);
  setColorRGB(200, 200, 0);
  beep(1000);
  Serial.println();
}

void holdIt(int rep) {

  clearColorRGB();
  OLEDDisplayAction("HOLD", 1);
  Serial.print("Hold");
  setColorRGB(0, 255, 0);

  for (int i = 0; i < HOLD_TIME; i++) {
    beep(BUZZER_DURATION);
    OLEDProgressBar((HOLD_TIME - i), HOLD_TIME, 1);
    myDelay(1000 - BUZZER_DURATION);
    Serial.print(".");
  }

  OLEDProgressBar(0, HOLD_TIME, 1);
  setColorRGB(200, 200, 0);
  beep(1000);
  Serial.println();
}

void relaxIt(int rep) {

  clearColorRGB();
  OLEDDisplayAction("RELAX", 1);
  Serial.print("Relax");
  setColorRGB(255, 0, 0);

  for (int i = 0; i < RELAX_TIME; i++) {
    beep(BUZZER_DURATION);
    OLEDProgressBar((RELAX_TIME - i), RELAX_TIME, 1);
    myDelay(1000 - BUZZER_DURATION);
    Serial.print(".");
  }

  OLEDProgressBar(0, RELAX_TIME, 1);
  setColorRGB(200, 200, 0);
  beep(1000);
  Serial.println();
}

void finishIt(void) {

  clearColorRGB();
  OLEDDisplayAction("GREAT JOB!", 1);
  blinkColorRGB(0, 0, 255, 5);
  Serial.println("Finished");
  myDelay(1000);
}

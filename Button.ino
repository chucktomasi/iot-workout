void initializeButtons() {

  Serial.print("Initializing buttons...");
  leftButton.onPress(onLeftButtonPressed);
  leftButton.onRelease(onLeftButtonReleased);
  leftButton.onHoldRepeat(1000, 500, onLeftButtonHeld);

  rightButton.onPress(onRightButtonPressed);
  rightButton.onRelease(onRightButtonReleased);
  rightButton.onHoldRepeat(1000, 500, onRightButtonHeld);
  Serial.println("OK");
}

void onLeftButtonPressed(Button& btn) {
  Serial.println("Left button pressed.");
  if (routine_running == false) {
    runRoutine();
    initializeOLED();
  }
}

void onLeftButtonHeld(Button& btn, uint16_t duration, uint16_t repeatCount){

        Serial.print("Left button has been held for ");
        Serial.print(duration);
        Serial.print(" ms; this event has been fired ");
        Serial.print(repeatCount);
        Serial.println(" times");

}

void onLeftButtonReleased(Button& btn, uint16_t duration) {
  Serial.print("Left button released. Duration=");
  Serial.println(duration);
}

void onRightButtonPressed(Button& btn) {
  Serial.println("Right button pressed.");

  if (mute == false) {
    mute = true;
    OLEDButtonLabel("MUTE", BUTTON_RIGHT, INVERSE);
  } else {
    mute = false;
    OLEDButtonLabel("MUTE", BUTTON_RIGHT, NORMAL);
  }

  Serial.print("Mute: ");
  Serial.println(mute);
}

void onRightButtonHeld(Button& btn, uint16_t duration, uint16_t repeatCount){

        Serial.print("Right button has been held for ");
        Serial.print(duration);
        Serial.print(" ms; this event has been fired ");
        Serial.print(repeatCount);
        Serial.println(" times");

}

void onRightButtonReleased(Button& btn, uint16_t duration) {
  Serial.print("Right button released. Duration=");
  Serial.println(duration);
}


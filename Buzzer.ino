void initializeBuzzer() {
  Serial.print("Initializing buzzer...");
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.println("OK");
}


void beep(int dur) {

  if (mute == false) {
    digitalWrite(BUZZER_PIN, HIGH);
  }
  myDelay(dur);
  digitalWrite(BUZZER_PIN, LOW);
}

void initializePhotoCell() {
  Serial.print("Initializing photo cell...");
  isRoomDark();
  Serial.print("OK");
}

bool isRoomDark(void) {

  int light_val = getPhotoCellValue();

  if (light_val < PHOTO_CELL_OFF_VALUE) {
    is_dark = true;
  }

  if (light_val > PHOTO_CELL_ON_VALUE) {
    is_dark = false;
  }

  return is_dark;
}

int getPhotoCellValue(void) {

  int light_val = analogRead(PHOTO_CELL_PIN);
  // Serial.print("Photo cell value=");
  // Serial.println(light_val);

  return light_val;
}

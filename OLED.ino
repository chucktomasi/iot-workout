#define LINE_HEIGHT 20
#define PROGRESSBAR_HEIGHT 5
#define STATUS_OFFSET 20
#define STATUS_GAP 3

void initializeOLED(void) {

  Serial.print("Initializing OLED...");

  /* getHeight() and getWidth() are not available in the library I use
  oled_screen_height = display.getHeight();
  oled_screen_width  = display.getWidth();
  */

  Serial.print(oled_screen_width);
  Serial.print("x");
  Serial.print(oled_screen_height);

  OLEDclear();
  OLEDDisplayAction("WORKOUT", 1);
  OLEDDrawMenuBox();
  OLEDButtonLabel("START", BUTTON_LEFT, NORMAL);
  OLEDButtonLabel("MUTE", BUTTON_RIGHT, mute);
  Serial.println(" OK");
}

void OLEDDisplayAction(String msg, int line) {

  int x = oled_screen_width / 2;
  int y = LINE_HEIGHT * (line - 1); // Line 1-4

  OLEDClearAction(line);

  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);
  display.drawString(x, y, msg);
  display.display();
}

void OLEDclear() {
  display.init();
  display.clear();

  display.flipScreenVertically();
  display.setContrast(255);
  display.setColor(WHITE);

  display.setFont(ArialMT_Plain_16);
}

void OLEDClearAction(int line) {

  int y = LINE_HEIGHT * (line - 1);
  
  display.setColor(BLACK);
  display.fillRect(0, y, oled_screen_width, LINE_HEIGHT);
  display.display();
}

void OLEDDisplayCount(int num) {

  int x = oled_screen_width / 2;

  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_24);
  display.drawString(x, 40, String(num));
  display.display();
}

void OLEDClearCount() {
  display.setColor(BLACK);
  display.fillRect(0, 40, 128, 24);
  display.display();
}

/***
 *
 * count = what number segment to draw
 * total = total number of segments to use (to fill the screen)
 * line = which vertal position (1-3) to place the progress bar
 *
 ***/
void OLEDProgressBar(int count, int total, int line) {

  int y_pos = (line * PROGRESSBAR_HEIGHT) + STATUS_OFFSET + STATUS_GAP;
  int bar_length = (oled_screen_width / total) * count;

  // Erase old bar
  display.setColor(BLACK);
  display.fillRect(0, y_pos, oled_screen_width, PROGRESSBAR_HEIGHT);
  display.display();

  // Draw new status bar
  display.setColor(WHITE);
  display.fillRect(0, y_pos, bar_length, PROGRESSBAR_HEIGHT);
  display.display();
}

/***
 *
 * text is the label to place
 * pos is either BUTTON_RIGHT or BUTTON_LEFT to indicate X position
 *
 ***/
void OLEDButtonLabel(String text, int pos, bool inverse) {

  int labelCenter = 64; // Default somewhere...

  display.setFont(ArialMT_Plain_10);
  
  if (pos == BUTTON_LEFT) {
    labelCenter = oled_screen_width / 4; // 32 on 128px
  } else {
    labelCenter = (oled_screen_width / 4) + (oled_screen_width / 2); // 96 on 128px
  }

  if (inverse) {
    OLEDClearButtonLabel(pos, INVERSE);
    display.setColor(BLACK);
  } else {
    OLEDClearButtonLabel(pos, BLACK);
    display.setColor(WHITE);
  }

  int textWidth = display.getStringWidth(text);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(labelCenter, MENU_BAR_Y + 3, text);
  display.display();
}

void OLEDClearButtonLabel(int pos, bool inverse) {

  int x;
  int y = MENU_BAR_Y + 1;
  int height = oled_screen_height - y;
  int width = oled_screen_width / 2 - 1;

  if (pos == BUTTON_LEFT) {
    x = 0;
  } else {
    x = (oled_screen_width / 2) + 1;
  }

  if (inverse) {
    display.setColor(WHITE);
  } else {
    display.setColor(BLACK);
  }
  display.fillRect(x, y, width, height);
  display.display();
}

void OLEDDrawMenuBox(void) {

  int mid_point = oled_screen_width / 2;

  display.setColor(WHITE);
  display.drawHorizontalLine(0, MENU_BAR_Y, oled_screen_width);
  display.drawLine(mid_point, MENU_BAR_Y, mid_point, oled_screen_height);
  display.display();
}

void OLEDClearButtonRow() {

  display.setColor(BLACK);
  display.fillRect(0, MENU_BAR_Y, oled_screen_width, oled_screen_height - MENU_BAR_Y);
  display.display();
}


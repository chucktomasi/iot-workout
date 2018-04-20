#include <Button.h>
#include <ButtonEventCallback.h>
#include <PushButton.h>
#include <Bounce2.h>
#include <SSD1306.h>
#include <FastLED.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include "HttpClient.h"

// WiFi Settings
char *ssid = "tomasipublic";
char *password = "onezerone";
char *netname;
char *netnamePrefix = "wrk-";

// Web Server definition
ESP8266WebServer server(80);

#define TRUE 1
#define FALSE 0

// TGB definitions
#define RGB_LED_PIN        D7
#define NUM_LEDS           1
#define COLOR_ORDER        RGB
#define RGB_LED_BRIGHTNESS 30
#define RGB_LED_MODEL      WS2811

CRGB led_array[NUM_LEDS];

// Button definitions
#define RIGHT_BUTTON D6
#define LEFT_BUTTON  D3

PushButton leftButton = PushButton(LEFT_BUTTON, ENABLE_INTERNAL_PULLUP);
PushButton rightButton = PushButton(RIGHT_BUTTON, ENABLE_INTERNAL_PULLUP);

// Buzzer definitions
#define BUZZER_PIN      D5
#define BUZZER_DURATION 200 // ms

// OLED definitions
#define OLED_ADDRESS	0x3c
#define OLED_SDA_PIN	D2
#define OLED_SDC_PIN	D1
#define BUTTON_RIGHT    70 // Screen position on the botom
#define BUTTON_LEFT     10
#define MENU_BAR_X      0
#define MENU_BAR_Y      50 // Height of divider bar
#define INVERSE         true
#define NORMAL          false
int oled_screen_width = 128; // Default width
int oled_screen_height = 64;

SSD1306 display = SSD1306(OLED_ADDRESS, OLED_SDA_PIN, OLED_SDC_PIN);

// Routine definitions
#define READY_TIME 3 // 3 seconds to get read
#define HOLD_TIME  10 // number of seconds to hold
#define RELAX_TIME 5 // number of seconds to relax
#define REPS       10 // number of times to repeat

// Photo cell definitions
#define PHOTO_CELL_OFF_VALUE 200 // If it dips below this, turn off RGB LED
#define PHOTO_CELL_ON_VALUE 300 // If it rises above this, turn on RGB LED
#define PHOTO_CELL_PIN A0

int is_dark = false;
int routine_running = false;
int mute = false;

void setup() {
  Serial.begin(115200);
  Serial.println("setup()");

  initializeRGB();
  initializeOLED();
  initializeButtons();
  initializeBuzzer();
  initializePhotoCell();
  initializeWifi();
}

void loop() {

  rightButton.update();
  leftButton.update();
}

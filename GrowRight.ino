#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT11.h>
#include <Wire.h>
#include <SPI.h>

#define ldr A3
#define mois A1
#define clk 2
#define dt 3
#define sw 4
#define thout 7

DHT11 thMeter(thout);

int lastStateClock;
int currentStateClock;
int counter = 0;
unsigned long lastButtonPress = 0;
int btn = 0;
int posm = 22;

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET 4      // Reset pin #
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int m_value = 0;
int t_value = 0;
int h_value = 0;
int l_value = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(sw, INPUT_PULLUP);
  pinMode(dt, INPUT);
  pinMode(clk, INPUT);

  lastStateClock = digitalRead(clk);
}

void loop() {
  if (btn == 1 && posm == 42) {
    btn = ListPage(posm, btn);
  } else if (btn == 1 && posm == 22) {
    btn = Moisturem(btn);
  } else {
    posm = Menu(posm);
    btn = 0;
  }

  int buttonState = digitalRead(sw);
  if (buttonState == LOW) {
    if (millis() - lastButtonPress > 50) {
      btn = 1;
    }
    lastButtonPress = millis();
  }
  delay(1);
}

int Menu(int pos) {
  currentStateClock = digitalRead(clk);

  if (lastStateClock != currentStateClock && currentStateClock == 1) {
    if (digitalRead(dt) == currentStateClock) {
      counter++;
      if (counter > 1) { counter = 0; }
    } else {
      counter--;
      if (counter < 0) { counter = 1; }
    }

    if (counter < 1) {
      pos = 22;
    } else {
      pos = 42;
    }
  }
  lastStateClock = currentStateClock;
  display.clearDisplay();
  display.setTextSize(2);  // Normal 1:1 pixel scale
  display.setTextColor(WHITE);
  if (pos == 22) {
    display.setCursor(0, pos);
    display.println(">");
    display.setCursor(10, 22);
    display.println("Start!");
    display.setCursor(10, 42);
    display.println("Seed List");
    display.display();
  } else {
    display.setCursor(0, pos);
    display.println(">");
    display.setCursor(12, 22);
    display.println("Start!");
    display.setCursor(12, 42);
    display.println("Seed List");
    display.display();
  }
  return pos;
}

int ListPage(int pos, int btn) {
  btn = 0;
  display.clearDisplay();
  display.setTextSize(1);  // Normal 1:1 pixel scale

  display.setTextColor(WHITE);
  display.setCursor(10, 8);
  display.println("Rose");
  display.setCursor(10, 18);
  display.println("Cactus");
  display.setCursor(10, 28);
  display.println("Pepper");
  display.setCursor(10, 38);
  display.println("Eggplant");
  display.setCursor(10, 48);
  display.println("Tomato");
  display.display();
  delay(10000);
  return btn;
}

int Moisturem(int btn) {
  btn = 0;
  int value1 = analogRead(mois);
  int value2 = analogRead(mois);
  int value3 = analogRead(mois);
  int value = 1000 - ((value1 + value2 + value3) / 3);
  display.clearDisplay();
  delay(1000);
  display.setTextSize(1);  // Normal 1:1 pixel scale
  display.setTextColor(WHITE);
  display.setCursor(10, 15);
  display.print("Moisture: ");
  display.println(value);
  display.display();

  m_value = value;
  delay(3000);
  Temp();

  Light();
  Result();
  return btn;
}

void Temp() {
  int temperature = 0;
  int humidity = 0;
  int result = thMeter.readTemperatureHumidity(temperature, humidity);
  display.setCursor(10, 25);
  display.print("Temp: ");
  display.print(temperature);
  display.display();

  delay(3000);
  display.setCursor(10, 35);
  display.print("Humidity: ");
  display.print(humidity);
  display.print("%");
  display.display();

  t_value = temperature;
  h_value = humidity;
  delay(3000);
}

void Light() {
  int lux1 = analogRead(ldr);
  int lux2 = analogRead(ldr);
  int lux3 = analogRead(ldr);
  int lux4 = analogRead(ldr);
  int lux5 = analogRead(ldr);
  int lux6 = analogRead(ldr);
  int lux = 100 - (lux1 + lux2 + lux3 + lux4 + lux5 + lux6) / 8;

  if (lux < 11) { lux = 11; }

  display.setCursor(10, 45);
  display.print("Light: ");
  display.print(lux);
  display.display();

  l_value = lux;
  delay(5000);
}

void Result() {
  int cur = 0;
  int plant = 0;
  display.clearDisplay();
  display.setTextSize(1);  // Normal 1:1 pixel scale
  display.setTextColor(WHITE);
  display.setCursor(10, 8);
  display.println("Available Plants:");
  cur = 18;
  if (m_value >= 550 && m_value <= 700 && t_value >= 20 && t_value <= 33 && h_value >= 45
      && h_value <= 75 && l_value >= 10 && l_value <= 55) {
    display.setCursor(10, cur);
    display.println("Rose");
    cur += 10;
    plant = 1;
  }
  if (m_value >= 500 && m_value <= 650 && t_value >= 18 && t_value <= 36 && h_value >= 25
      && h_value <= 80 && l_value >= 40 && l_value <= 100) {
    display.setCursor(10, cur);
    display.println("Cactus");
    cur += 10;
    plant = 1;
  }

  if (m_value >= 625 && m_value <= 750 && t_value >= 16 && t_value <= 30 && h_value >= 45
      && h_value <= 80 && l_value >= 10 && l_value <= 75) {
    display.setCursor(10, cur);
    display.println("Pepper");
    cur += 10;
    plant = 1;
  }
  if (m_value >= 650 && m_value <= 825 && t_value >= 20 && t_value <= 30 && h_value >= 55
      && h_value <= 85 && l_value >= 50 && l_value <= 100) {
    display.setCursor(10, cur);
    display.println("Eggplant");
    cur += 10;
    plant = 1;
  }
  if (m_value >= 750 && m_value <= 850 && t_value >= 16 && t_value <= 29 && h_value >= 45
      && h_value <= 80 && l_value >= 25 && l_value <= 70) {
    display.setCursor(10, cur);
    display.println("Tomato");
    cur += 10;
    plant = 1;
  }
  if (plant == 0) {
    display.setCursor(10, 25);
    display.println("No Suitable Plants!");
  }
  display.display();
  delay(15000);
}

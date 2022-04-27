#include "main.h"

void connectWiFi() {
  delay(2000);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  Serial << "Connect to " << WIFI_SSID << endl;
}

void mode1() {
  /* вжжжжж 1 */
}

void mode2() {
  /* вжжжжж 2 */
}

void mode3() {
  /* вжжжжж 3 */
}

void newMsg(FB_msg& msg) {
  if (msg.text == "РЕЖИМ 1") {
    bot.editMenuID(bot.lastBotMsg(), menu1, "");
    bot.sendMessage("Вращение 1", msg.chatID);
    bot.showMenuText(menu1, msg.chatID);
    mode1();
  }
  if (msg.text == "РЕЖИМ 2") {
    bot.editMenuID(bot.lastBotMsg(), menu1, "");
    bot.sendMessage("Вращение 2", msg.chatID);
    bot.showMenuText(menu1, msg.chatID);
    mode2();
  }
  if (msg.text == "РЕЖИМ 3") {
    bot.editMenuID(bot.lastBotMsg(), menu1, "");
    bot.sendMessage("Вращение 3", msg.chatID);
    bot.showMenuText(menu1, msg.chatID);
    mode3();
  }
  if (msg.text == "Датчик движения") {
    bot.editMenuID(bot.lastBotMsg(), menu1, "");
    if (movingFlag) {
      movingFlag = 0;
      bot.sendMessage("Датчик движения отключен", msg.chatID);
    } else {
      movingFlag = 1;
      bot.sendMessage("Датчик движения включен", msg.chatID);
    }
    bot.showMenuText(menu1, msg.chatID);

  }

  Serial << msg.text << endl;
}

void setup() {
  connectWiFi();
  Serial.begin(9600);
  Serial.println();
  bot.attach(newMsg);
  bot.showMenu(menu1);

  pinMode(15, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
}

void loop() {
  bot.tick();
}

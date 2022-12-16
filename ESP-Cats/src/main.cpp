#include "main.h"

void otaUpdater() {
  httpUpdater.setup(&httpServer, "/firmware");
  httpServer.begin();
}

void mode1() {
  /* вжжжжж 1 */
  Serial << "mode1" << endl;

  motor.startMotor();
  // motor.moveForward(255, 150);
  motor.moveForward(80, 1800);
  motor.moveBackward(180, 500);
  motor.moveForward(150, 800);
  motor.moveBackward(200, 1300);
  motor.moveForward(255, 2000);
  motor.moveBackward(90, 1500);

  motor.stopMotor();

}

void mode2() {
  /* вжжжжж 2 */
  Serial << "mode2" << endl;

  motor.startMotor();

  motor.moveForward(255, 150);
  motor.moveForward(90, 1800);
  motor.moveForward(240, 2500);
  motor.moveBackward(200, 2300);
  motor.moveBackward(120, 1500);
  motor.moveForward(180, 1000);

  motor.stopMotor();

}

void mode3() {
  /* вжжжжж 3 */

  motor.startMotor();

  motor.moveForward(255, 150);
  motor.moveForward(250, 2200);
  motor.moveForward(100, 600);
  motor.moveForward(80, 2150);
  motor.moveForward(250, 3100);

  motor.stopMotor();
}

void mode4() {
  /* вжжжжж 4 */
  motor.startMotor();

  for (int i = 0; i < 10; i++) {
    motor.moveForward(255, 150);
    motor.moveForward(250, 600);
    motor.moveForward(100, 600);
    motor.moveForward(80, 700);
    motor.moveForward(250, 800);

    motor.moveBackward(200, 600);
    motor.moveBackward(90, 600);
    motor.moveBackward(255, 500);
    motor.moveBackward(120, 600);
  }
  motor.stopMotor();
}

void chooseMode(){
  // int mode = 0;
    curMode = 1 + rand() % 3;

    switch (curMode) {
    case 1: {
        mode1();
        break;
    }
    case 2: {
        mode2();
        break;
    }
    case 3: {
        mode3();
        break;
    }
    }
}

void sensorDetect() {
  // if (movingFlag) {
  //   if (digitalRead(sensorPin) == 1) {
  //     if (millis() - lastTime > 5000) { //delay (5000)
  //       chooseMode();
  //       lastTime = millis();
  //     }
  //   }
  // }
}

void newMsg(FB_msg& msg) {
  if (msg.text == "РЕЖИМ 1") {
    mode1();
    bot.sendMessage("Вращение 1", msg.chatID);
    // mode1();
  }
  if (msg.text == "РЕЖИМ 2") {
    // bot.sendMessage("Вращение 2", msg.chatID);
    FB_Time formTime = bot.getTime(3);
    bot.sendMessage(formTime.timeString(), msg.chatID);
    bot.sendMessage(formTime.dateString(), msg.chatID);
    mode2();
  }
  if (msg.text == "РЕЖИМ 3") {
    // bot.editMenuID(bot.lastBotMsg(), menu1, "");
    bot.sendMessage("Вращение 3", msg.chatID);
    mode3();
  }
  if (msg.text == "РЕЖИМ 4") {
    // bot.editMenuID(bot.lastBotMsg(), menu1, "");
    bot.sendMessage("Вращение 4", msg.chatID);
    mode4();
  }
  if (msg.text == "Датчик движения") {
    // bot.editMenuID(bot.lastBotMsg(), menu1, "");
    if (movingFlag) {
      movingFlag = 0;
      digitalWrite(4, LOW);
      bot.sendMessage("Датчик движения отключен", msg.chatID);
    } else {
      movingFlag = 1;
      digitalWrite(4, HIGH);
      bot.sendMessage("Датчик движения включен", msg.chatID);
    }
  }
  if (msg.text == "/start") {
    // bot.editMenuID(bot.lastBotMsg(), menu1, "");
    bot.showMenu(menu1, msg.chatID);
    bot.sendMessage(verBuild, msg.chatID);
  }
  if (msg.text == "Обновление прошивки") {
    // bot.editMenuID(bot.lastBotMsg(), menu1, "");
    String updMsg = "Адрес для прошивки: " + WiFi.localIP().toString() + "/firmware";
    bot.sendMessage(verBuild, msg.chatID);
    bot.sendMessage(updMsg, msg.chatID);
  }
  if (msg.text == "Состояние сети") {
    // bot.editMenuID(bot.lastBotMsg(), menu1, "");
    String updMsg = "Имя сети: " + WiFi.SSID() + " | MAC: " + WiFi.macAddress() + " | IP: " + WiFi.localIP().toString();
    bot.sendMessage(updMsg, msg.chatID);
  }

  if (msg.OTA) bot.update();


  Serial << msg.text << endl;
}

// void apLED(){
//   digitalWrite(15, HIGH);
// }
//
// void stLED(){
//   digitalWrite(15, LOW);
//   digitalWrite(13, HIGH);
// }

void setup() {
  Serial.begin(9600);
  Serial.println();
  pinMode(15, OUTPUT);
  pinMode(13, OUTPUT);
  // pinMode(12, OUTPUT);
  // pinMode(4, OUTPUT);
  // pinMode(A0, INPUT);
  // connectWiFi();
  // apLED();
  wifiManager.autoConnect("WeMos Connect");

  // stLED();
  otaUpdater();
  bot.attach(newMsg);
}

void loop() {
  bot.tick();
  httpServer.handleClient();
  // sensorDetect();
}

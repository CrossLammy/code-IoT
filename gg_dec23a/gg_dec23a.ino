#include "arduino_secrets.h"


#include "thingProperties.h"
int ledGrow = 22;
int relay1 = 23;
int led1 = 18;//แสดงสถานะปั้ม 
int led2 = 17;//แสดงสถานะ ledGrowlight
boolean state1 = false;
int manualswitch1 = 19;//กดปั้ม

void setup() {
  int state1 = true;
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(ledGrow, OUTPUT); //ไฟ
  pinMode(relay1, OUTPUT); //ปัม
  pinMode(led1, OUTPUT); //ไฟแสดงปั้ม
  pinMode(led2, OUTPUT);//ไฟแสดง LEDgrowlight
  pinMode(manualswitch1, INPUT_PULLUP); //สวิสปั้ม
  digitalWrite(relay1, state1);
  //digitalWrite(led1, HIGH);
  delay(1500);
  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);


  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  //ระบบ ปั้ม+ปุ่มกด
  if (digitalRead(manualswitch1) == LOW)
  {
    Serial.println("Switch 1 Pressed");
    light1 = !light1;
    onLight1Change();
    while (digitalRead(manualswitch1) == LOW) {}
    delay(500);
  }

  // ledGrowlight code อิอิ
  if (schedule.isActive()) {
    digitalWrite(ledGrow, LOW);
    ledgrow_status = true;
  } else {
    digitalWrite(ledGrow, HIGH);
    ledgrow_status = false;
  }
  //ระบบไฟแสดงสถานะ ledGrowlight
  if(ledgrow_status == HIGH){
    digitalWrite(led2,HIGH);
  } else{
    digitalWrite(led2,LOW);
  }

}

void onLight1Change()  {
  digitalWrite(relay1, state1);
  state1 = !state1;

  if (state1 == true) { //ไฟแสดงจริงปั้ม
    digitalWrite(led1, HIGH);
  } else {
    digitalWrite(led1, LOW);
  }
}

void onLedgrowStatusChange()  {
  
}

void onScheduleChange()  {
  
}
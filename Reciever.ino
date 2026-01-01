#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);   // CE, CSN
const byte address[6] = "CAR01";

const int buzzer = 3;
const int led = 4;

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);

  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();

  Serial.println("Receiver Ready...");
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));

    Serial.println(text);

    // Alert indication
    digitalWrite(led, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
  }
}
#include <SPI.h>
#include <LoRa.h>


//Connections to the LoRa module SX1278
//VCC     3.3V
//GND     GND
//MISO    GPIO 19
//MOSI    GPIO 23
//SCK     GPIO 5
//NSS(CS) GPIO 18
//RST     GPIO 14
//DIO0    GPIO 26


#define SS 18
#define RST 14
#define DIO0 26

void setup() {
    Serial.begin(115200);
    while (!Serial);

    Serial.println("LoRa Receiver");
    
    LoRa.setPins(SS, RST, DIO0);
    
    if (!LoRa.begin(915E6)) {  // LoRa frequency (change based on your region)
      
//      LoRa Frequency: The default is 915MHz, but depending on your location, change it to:
//      EU: 868E6
//      US: 915E6
//      Asia: 433E6

        Serial.println("Starting LoRa failed!");
        while (1);
    }
    
    Serial.println("LoRa Initialized.");
}

void loop() {
    int packetSize = LoRa.parsePacket();
    if (packetSize) {
        Serial.print("Received: ");
        String receivedMessage = "";

        while (LoRa.available()) {
            receivedMessage += (char)LoRa.read();  // Append received characters
        }

        Serial.println(receivedMessage);
        Serial.print("Signal Strength (RSSI): ");
        Serial.println(LoRa.packetRssi());
    }
}

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// BLE Service and Characteristic UUIDs
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Button Pins
#define BUTTON_FIRE_PIN 12  // Fire trigger button
#define BUTTON_RELOAD_PIN 13 // Reload button
#define BUTTON_JUMP_PIN 14   // Jump button
#define BUTTON_CROUCH_PIN 27 // Crouch button

BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

// Custom callback class for connection events
class MyServerCallbacks: public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Device connected");
  };

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Device disconnected");
    // Restart advertising after disconnection
    pServer->getAdvertising()->start();
  }
};

void setup() {
  Serial.begin(115200);

  // Set up button pins with internal pull-up resistors
  pinMode(BUTTON_FIRE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RELOAD_PIN, INPUT_PULLUP);
  pinMode(BUTTON_JUMP_PIN, INPUT_PULLUP);
  pinMode(BUTTON_CROUCH_PIN, INPUT_PULLUP);

  // Initialize BLE
  BLEDevice::init("ESP32_Gamepad");  // This is the Bluetooth name that will show up

  // Create BLE server and set callback functions
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create BLE service and characteristic
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ |
                      BLECharacteristic::PROPERTY_WRITE |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );
  
  // Start the service
  pService->start();

  // Start BLE advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);  // Add service UUID to the advertising packet
  pAdvertising->setScanResponse(true);         // Enable scan response to include the device name
  pAdvertising->setMinPreferred(0x06);         // Function to help with Android BLE compatibility
  pAdvertising->setMinPreferred(0x12);
  pServer->getAdvertising()->start();          // Start advertising
  
  Serial.println("Waiting for client connection...");
}

void loop() {
  // Read the button states and send corresponding BLE notifications

  // Fire button mapped to "X"
  if (digitalRead(BUTTON_FIRE_PIN) == LOW) {
    pCharacteristic->setValue("X");
    pCharacteristic->notify();
    Serial.println("Fire (X) button pressed");
  }

  // Reload button mapped to "Y"
  if (digitalRead(BUTTON_RELOAD_PIN) == LOW) {
    pCharacteristic->setValue("Y");
    pCharacteristic->notify();
    Serial.println("Reload (Y) button pressed");
  }

  // Jump button mapped to "A"
  if (digitalRead(BUTTON_JUMP_PIN) == LOW) {
    pCharacteristic->setValue("A");
    pCharacteristic->notify();
    Serial.println("Jump (A) button pressed");
  }

  // Crouch button mapped to "B"
  if (digitalRead(BUTTON_CROUCH_PIN) == LOW) {
    pCharacteristic->setValue("B");
    pCharacteristic->notify();
    Serial.println("Crouch (B) button pressed");
  }

  delay(50);  // Add delay to avoid sending too many notifications
}

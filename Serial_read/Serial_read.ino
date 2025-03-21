String inputString = "";  // Stores user input
bool stringComplete = false;

void setup() {
    Serial.begin(9600);
    Serial.println("Type something and press Enter:");
}

void loop() {
    while (Serial.available()) {
        char c = Serial.read();  // Read character by character

        if (c == '\n') {  // Detect "Enter" key
            stringComplete = true;
        } else {
            inputString += c;  // Append characters to the string
        }
    }

    if (stringComplete) {
        Serial.print("You typed: ");
        Serial.println(inputString);

        // Reset for the next input
        inputString = "";
        stringComplete = false;
        Serial.println("\nType something again:");
    }
}

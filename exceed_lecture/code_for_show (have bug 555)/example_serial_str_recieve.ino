void setup() {
	Serial.begin(115200);
}

void loop() {
	serialEvent();
}

void serialEvent() {
	if (Serial.available() > 0) {
		String recieve = Serial.readStringUntil('\r');
		Serial.println("Recieve : " + recieve);
		Serial.flush();
	}
}
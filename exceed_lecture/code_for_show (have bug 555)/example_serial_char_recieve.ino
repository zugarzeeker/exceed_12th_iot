void setup() {
	Serial.begin(115200);
}

void loop() {
	serialEvent();
}

void serialEvent() {
	String recieve = "";
	while (Serial.available() > 0) {
		char ch = Serial.read();
		recieve += ch;
	}
	Serial.println("Recieve : " + recieve);
}
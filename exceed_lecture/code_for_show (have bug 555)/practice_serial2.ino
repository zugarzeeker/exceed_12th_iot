String username = "Your-Username";
void setup() {
	Serial.begin(9600);
	Serial1.begin(115200);
}

void loop() {
	serialEvent();
}

void serialEvent() {
	if (Serial.available() > 0) {
		String sendMessage = Serial.readStringUntil('\r');
		Serial.flush();
		Serial.println(username + " : " + sendMessage);
		Serial1.print(username + " : " + sendMessage);
		Serial1.print('\r');
		
	}
	if (Serial1.available() > 0) {
		String recieveMessage = Serial1.readStringUntil('\r');
		Serial.println(recieveMessage);
	}
}
#define LED1 11
#define LED2 12

void setup() {
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
}

void taskLED1() {
	digitalWrite(LED1, HIGH);
	delay(1000);
	digitalWrite(LED1, LOW);
	delay(500);
}

void taskLED2() {
	digitalWrite(LED2, HIGH);
	delay(700);
	digitalWrite(LED2, LOW);
	delay(300);
}

void loop() {
	taskLED1();
	taskLED2();
}
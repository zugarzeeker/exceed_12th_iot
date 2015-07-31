#include <pt.h>
#define PT_DELAY(pt, ms, ts) \
	ts = millis(); \
	PT_WAIT_WHILE(pt, millis()-ts < (ms));
#define LED1 11
#define LED2 12
#define SW 2

int led1, led2;
int sw;
String val;

struct pt pt_taskLED1;
struct pt pt_taskLED2;
struct pt pt_taskSW;
struct pt pt_taskSendSerial;

PT_THREAD(taskSendSerial(struct pt* pt))
{
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1)
  {
	sendSerial();
	PT_DELAY(pt, 600, ts);
  }
  PT_END(pt);
}


void sendSerial() {
  Serial1.print(sw);
  Serial1.print('\r');
}

void serialEvent() {
  if (Serial1.available() > 0) {
	val = Serial1.readStringUntil('\r');
	Serial.print("value Recieve : ");
	Serial.println(val);
	Serial1.flush();
	setValue();
  }
}

void setValue() {
  switch(val.charAt(0)) {
	case '0': led1 = LOW; break;
	case '1': led1 = HIGH; break;
  }
  switch(val.charAt(1)) {
	case '0': led2 = LOW; break;
	case '1': led2 = HIGH; break;
  }
}


PT_THREAD(taskLED1(struct pt* pt))
{
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1)
  {
	digitalWrite(LED1, led1);
	PT_DELAY(pt, 300, ts);
  }
  PT_END(pt);
}

PT_THREAD(taskLED2(struct pt* pt))
{
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1)
  {
	digitalWrite(LED2, led2);
	PT_DELAY(pt, 300, ts);
  }
  PT_END(pt);
}

PT_THREAD(taskSW(struct pt* pt))
{
  static uint32_t ts;
  PT_BEGIN(pt);
  while (1)
  {
	sw = digitalRead(SW);
	PT_DELAY(pt, 150, ts);
  }
  PT_END(pt);
}

void setup()
{
  Serial1.begin(115200);
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(SW, INPUT);

  PT_INIT(&pt_taskLED1);
  PT_INIT(&pt_taskLED2);
  PT_INIT(&pt_taskSW);
  PT_INIT(&pt_taskSendSerial);
}


void loop()
{
  taskLED1(&pt_taskLED1);
  taskLED2(&pt_taskLED2);
  taskSW(&pt_taskSW);

  serialEvent();
  taskSendSerial(&pt_taskSendSerial);
}

#include <pt.h>
#include <LiquidCrystal.h>

#define PT_DELAY(pt, ms, ts) \
	ts = millis(); \
	PT_WAIT_WHILE(pt, millis() - ts < (ms));

#define LED1 11
#define LED2 12
#define LED3 13
#define LED4 14
#define LDR A1
#define SW 2

struct pt pt_taskLED1;
struct pt pt_taskLED2;
struct pt pt_taskLDR;
struct pt pt_taskSW;

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() 
{
	pinMode(LED1, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED4, OUTPUT);
	pinMode(SW, INPUT);
	pinMode(LDR, INPUT);
	lcd.begin(16, 2);
}

PT_THREAD(taskLED1(struct pt* pt))
{
	static uint32_t ts;
	PT_BEGIN(pt);
	while (1)
	{
		digitalWrite(LED1, HIGH);
		PT_DELAY(pt, 1000, ts);
		digitalWrite(LED1, LOW);
		PT_DELAY(pt, 500, ts);
	}
	PT_END(pt);
}

PT_THREAD(taskLED2(struct pt* pt))
{
	static uint32_t ts;
	PT_BEGIN(pt);
	while (1)
	{
		digitalWrite(LED1, HIGH);
		PT_DELAY(pt, 700, ts);
		digitalWrite(LED1, LOW);
		PT_DELAY(pt, 300, ts);
	}
	PT_END(pt);
}

PT_THREAD(taskLDR(struct pt* pt))
{
	static uint32_t ts;
	PT_BEGIN(pt);
	while (1)
	{
		lcd.clear();
		if (analogRead(LDR) < 500) {
			lcd.print("Dark");
		}
		else {
			lcd.print("Light");
		}
		PT_DELAY(pt, 150, ts);
	}
	PT_END(pt);
}

PT_THREAD(taskSW(struct pt* pt))
{
	static uint32_t ts;
	PT_BEGIN(pt);
	while (1)
	{
		int sw = digitalRead(SW);
		digitalWrite(LED3, sw);
		digitalWrite(LED4, !sw);
		PT_DELAY(pt, 150, ts);
	}
	PT_END(pt);
}

void loop()
{
  taskLED1(&pt_taskLED1);
  taskLED2(&pt_taskLED2);
  taskLDR(&pt_taskLDR);
  taskSW(&pt_taskSW);
}


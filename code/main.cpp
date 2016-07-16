#include <Arduino.h>
#include "main.h"
#include "Motor/Motor.h"
#include "Fuzzy_Set/FuzzySet.h"
#include "Data/data.h"
#include "FuzzySystem/FuzzySystem.h"

int count = 0;

unsigned long previous_time = 0;
unsigned long current_time = 0;

unsigned long timeDifference = 0;

Motor rightMotor(8, 10, 11);

void tick() {
	count++;
}

void serialEvent() {
	Serial.println("====, ==== ");
}

void setup() {

	//serialEventRun();

	Serial.begin(9600);
	attachInterrupt(0, tick, FALLING);
	rightMotor.forward();

	rightMotor.setSpeed(0);

	delay(1000);
	count = 0;

	initSets();

	desiredRpm = 50;
	error = 0;
	derror = 0;

}
int low;
int high;
long total;

const long r = 60000;

double rpm;
FuzzySet test(10, 20, 30);
int previousError = 0;
void loop() {

	if (Serial.available()) {
		desiredRpm = Serial.parseInt();
	}

	high = pulseIn(2, HIGH);
	low = pulseIn(2, LOW);

	total = high + low;

	//	Serial.print(total);Serial.print(",");

	rpm = r/( 0.485 * total);

	previousError = error;
	error = desiredRpm - rpm;

	derror = error - previousError;

	//Serial.println("<<<<<<<<<< >>>>>>>>>>>>");
	calculateOutput();
	//Serial.print("RPM : ");
	Serial.println((int)(ceil(rpm)));
	//Serial.println(200);
	//Serial.print(" = ");
	//Serial.println(out);
	rightMotor.setSpeed(ceil(out));

	/*while (!Serial.available()) {
	 delay(10);
	 }
	 Serial.println(Serial.parseInt());
	 */
	delay(100);
}

int main() {
	init();
	setup();

	while (1) {
		loop();
	}

}


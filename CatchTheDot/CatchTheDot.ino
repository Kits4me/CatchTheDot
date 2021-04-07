/*
 Name:		CatchTheDot.ino
 Created:	4/6/2021 8:05:50 PM
 Author:	amird
 Using:     Kits4.me Games kit
*/

#define pinRedBtn 2
#define pinGreenBtn 3


int spd = 100;
int colorONtimeMs = 500;
int colorOFFtimeMs = 800;
long lastLightStartedMs;
long lastColoredStartTimeMs;
long lastOffStartTimeMs;
bool colorsEnabled = false;
bool colorIsOn = false;

void setup() {
	pinMode(pinRedBtn, INPUT);
	pinMode(pinGreenBtn, INPUT);
	neoSetup();
	newRound();
}
void loop() {
	if (millis() - lastLightStartedMs >= spd) {
		chooseColor();
		NextRobin();
		lastLightStartedMs = millis();
	}
}

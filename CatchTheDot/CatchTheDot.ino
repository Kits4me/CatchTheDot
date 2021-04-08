/*
 Name:		CatchTheDot.ino
 Created:	4/6/2021 8:05:50 PM
 Author:	amird
 Using:     Kits4.me Games kit
*/

#define pinRedBtn 2
#define pinGreenBtn 3


int spd = 200;
int colorONtimeMs = 800;
int colorOFFtimeMs = 1400;
long lastLightStartedMs;
long lastColoredStartTimeMs;
long lastOffStartTimeMs;
bool colorsEnabled = false;
bool colorIsOn = false;

int score;
void setup() {
	pinMode(pinRedBtn, INPUT_PULLUP);
	pinMode(pinGreenBtn, INPUT_PULLUP);
	neoSetup();
	setup_7seg();
	score = 0;
	newRound();
}
void loop() {
	if (digitalRead(pinRedBtn) == LOW) {
		if (isRed()) {
			GoodAns();
		}
		else {
			BadAns();
		}
	}
	if (digitalRead(pinGreenBtn) == LOW) {
		if (isGreen()) {
			GoodAns();
		}
		else {
			BadAns();
		}
	}
	if (millis() - lastLightStartedMs >= spd) {
		chooseColor();
		NextRobin();
		lastLightStartedMs = millis();
	}
	showNum(score, spd);
}
void GoodAns() {
	score++;
	LightUpperLineInGreen();
}
void BadAns() {
	score--;
	if (score < 0) {
		score = 0;
	}
	LightLowerLineInRed();
}

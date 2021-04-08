/*
 Name:		CatchTheDot.ino
 Created:	4/6/2021 8:05:50 PM
 Author:	amird
 Using:     Kits4.me Games kit
*/

#define pinRedBtn 2
#define pinGreenBtn 3


int GameLongMs = 20000;
bool GameEnabled;
long GameStartTime;

int spd = 200;
int colorONtimeMs = 800;
int colorOFFtimeMs = 1000;
long lastLightStartedMs;
long lastColoredStartTimeMs;
long lastOffStartTimeMs;
bool colorsEnabled = false;
bool colorIsOn = false;

int score;
void NewGame() {
	score = 0;
	GameEnabled = true;
	GameStartTime = millis();
	newRound();
}
void setup() {
	pinMode(pinRedBtn, INPUT_PULLUP);
	pinMode(pinGreenBtn, INPUT_PULLUP);
	neoSetup();
	setup_7seg();
	NewGame();
}
void loop() {
	if (millis() - GameStartTime >= GameLongMs) {
		GameEnabled = false;
		MatOffAll();
		if ((digitalRead(pinGreenBtn) == LOW) && (digitalRead(pinRedBtn) == LOW)) {
			while (digitalRead(pinGreenBtn) == LOW) { delay(50); }
			while (digitalRead(pinRedBtn) == LOW) { delay(50); }
			NewGame();
		}
	}
	else {
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

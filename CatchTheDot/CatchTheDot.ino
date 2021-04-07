/*
 Name:		CatchTheDot.ino
 Created:	4/6/2021 8:05:50 PM
 Author:	amird
 Using:     Kits4.me Games kit
*/

// the setup function runs once when you press reset or power the board
void setup() {
	neoSetup();
}
int spd = 100;
// the loop function runs over and over again until power down or reset
void loop() {
	NextRobin();
	delay(spd);
}

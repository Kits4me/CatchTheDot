/*
 Name:		CatchTheDot.ino
 Created:	4/6/2021 8:05:50 PM
 Author:	amird
*/

// the setup function runs once when you press reset or power the board
void setup() {
	strip.begin();
}
int spd = 1000;
// the loop function runs over and over again until power down or reset
void loop() {
	NextRobin();
	delay(spd);
}

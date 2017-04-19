/*
 VOCAS Tech Serial Simple Demo
 By: Richard Pape
 VOCAS Technologies Technologies
 Date: October 1, 2015
 License: This code is public domain.

 Uses the Nose library to store, and recall scents.

 This example code uses a function to find the peak values rather
 than allowing the Nose library to take care of sampling.

 Prepare a small bowl of Distilled White Vinegar.

 Once the code is uploaded move the sensors to clean air and press the button next to the LED

 The shield will take 10 seconds to smell the air. Once the shield learns air it will turn off the LED for 2 seconds.

 Now place the sensor over the bowl of Vinegar but dont let it touch the sensors and press the button again.

 In about 10 seconds the shield will learn Vinegar.

 Now when you click the button it will take 10 seconds to recognize the smell. 
 
 If it recognizes Vinegar it will turn on the LED for 2 seconds. If it doesn't recognize vinegar the led will stay off

 If you change the intro variable to 1 you can walkthrough instructions on the serial terminal 
 Open serial monitor at 9600 baud to see instructions.
 */
#include <Nose.h>

Nose myNose(A0, A1, A2, A3);       //Creates a new instance of the Nose with the analog pins of the senors identified.

const bool intro = 1;             //Change to 1 to activate the Serial Terminal walkthough guide

const int buttonPin = 4;
int scentAir[4] = {153, 119, 256, 231};
int scentVinegar[4] = {267, 499, 329, 478};

//Variables
int scent[4];                      //An integer array to store the sensor readings.
String SmellID;                    //A string to store the smells id
int smellnum = 0;                  //An integer to track the address location of a smell.
bool buttonState = 0;
int LedPin = 5;

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(LedPin, OUTPUT);

  Serial.begin(9600);              //Start serial communication.

  myNose.learn(scentAir, "Air", 0);
  myNose.learn(scentVinegar, "Vinegar", 1);
  if (intro == 1) {
    //Send the instructions to the user via the serial port.
    //You may comment this entire section to skip the intro.
    Serial.println("Welcome to the VOCAS NOSE!");
    Serial.println();
    delay(1500);
    Serial.println("Let's do a little experiment.");
    delay(2000);
    Serial.print("I can smell and identify white distilled vinegar.");
    delay(3000);
    Serial.println(" Put some in a bowl for me.");
    delay(3000);
    Serial.println();
    Serial.println("Now, when you expose me to the vinegar be sure to not let me touch it, I can");
    Serial.print("break that way.");
    delay(5000);
    Serial.println(" Also, when you expose me to the vinegar hold me so my sensors");
    Serial.println("are facing downward into the bowl of vinegar.");
    delay(5000);
    Serial.println();
    Serial.println("First I need you to teach me what normal air and vinegar smell like.");
    delay(5000);
    //Comment only to here to skip the intro.
    Serial.println();
    Serial.println("Keep me away from the vinegar and press the button by the LED to teach me air.");
    Serial.println();
  }
  else {
    digitalWrite(LedPin, HIGH);
    delay(2000);
  }
  buttonState = digitalRead(buttonPin);
  while (buttonState) {
    buttonState = digitalRead(buttonPin);
  }

  if (intro == 1) {
    //Now expose the Sensor to the scent for 10 seconds.
    Serial.println("Okay. I will now smell for 10 seconds to get a good sample.");
    delay(2000);
    Serial.print("Collecting scent...");
    delay(1000);
    Serial.println("Please wait.");
  }
  else {
    delay(2000);
  }
  findPeak();

  myNose.learn(scent, "Air", 0);
  digitalWrite(LedPin, LOW);
  if (intro == 1) {
    Serial.println("I have learned air.");
    delay(2000);

    Serial.println();
    Serial.println("Now press the button again to teach me vinegar.");
  }
  else {
    delay(2000);
    digitalWrite(LedPin, HIGH);
    delay(2000);
  }
  buttonState = digitalRead(buttonPin);
  while (buttonState) {
    buttonState = digitalRead(buttonPin);
  }
  if (intro == 1) {
    Serial.print("Remember don't let me touch the vinegar.");
    delay(2000);
    Serial.println(" Now expose me to the vinegar.");
    delay(3000);
    Serial.println();
    //Now expose the Sensor to the scent for 10 seconds.
    Serial.println("Okay. I will now smell for 10 seconds to get a good sample.");
    delay(2000);
    Serial.print("Collecting scent...");
    delay(1000);
    Serial.println("Please wait.");
  }
  else {
    delay(2000);
  }
  findPeak();

  myNose.learn(scent, "Vinegar", 1);
  digitalWrite(LedPin, LOW);
  if (intro == 1) {
    Serial.println("I have learned vinegar");
    delay(4000);

    Serial.println();
    Serial.println("I am ready for you to test me.");
    delay(1000);
    Serial.println();
    Serial.println("Please press the button by the LED to make me smell.");
    Serial.println();
  }
  else {
    delay(2000);
  }
}


void loop() {
  buttonState = digitalRead(buttonPin);

  //This will watch the serial port.
  //If there is a command waiting it will be read in.
  if (!buttonState) {
    //Now expose the Sensor to the scent for 10 seconds.
    Serial.println("Okay. I will now smell for 10 seconds to get a good sample.");
    delay(2000);
    Serial.print("Collecting scent...");
    delay(1000);
    Serial.println("Please wait.");
    findPeak();

    /*The recognize command requires a 4 integer array to analyse and returns the smell
      that it is guessing. It will compare the values to all of the scents it has
      previously recorded. Then it will return the closest scent.*/
    SmellID = myNose.recognize(scent);

    //This tells the user the closest scent recorded.
    Serial.print("I am smelling ");
    Serial.print(SmellID);
    if (SmellID == "Vinegar") {
      digitalWrite(LedPin, HIGH);
    }

    Serial.println(".");
    Serial.println();
    delay(1500);
    digitalWrite(LedPin, LOW);
    //This requests the next command.
    Serial.println("Press the button by the LED to make me smell again.");
    Serial.println();

  }
}

//This function will sample analog pins 0-4 for 10 seconds and store the peak values in the scent integer array.
void findPeak() {
  long time = millis() + 10000;
  int peak[4];

  for (int i = 0; i < 4; i++) {
    peak[i] = analogRead(i);
    peak[i] = analogRead(i);
  }

  while (time > millis()) {
    for (int i = 0; i < 4; i++) {
      int tempval = analogRead(i);
      tempval = analogRead(i);
      if (tempval > peak[i]) {
        peak[i] = tempval;
      }
    }
  }
  for (int i = 0; i < 4; i++) {
    scent[i] = peak[i];
  }
}

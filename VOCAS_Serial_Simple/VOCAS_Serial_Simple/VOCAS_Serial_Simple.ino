/* 
 VOCAS Tech Serial Simple code
 By: Richard Pape
 Smart Sensor Technologies
 Date: October 1, 2015
 License: This code is public domain.
 
 Uses the Nose library to sample, store, and recall scents.
 
 Open serial monitor at 9600 baud to see instructions.
 */


#include <Nose.h>

Nose myNose(A0,A1,A2,A3);          //Creates a new instance of the Nose with the analog pins of the senors identified.

//Varibles
int scent[4];                      //An integer array to store the sensor readings.
String SmellID;                    //A string to store the smells id.
int smellnum=0;                    //An integer to track the address location of a smell.

void setup() {
  Serial.begin(9600);              //Start serial communication.
  
  //Send the instructions to the user via the serial communication.
  Serial.println("Welcome to the VOCAS Nose!");
  Serial.println();
  Serial.println("Please reply with one of the following options:");
  Serial.println("Learn");
  Serial.println("Recognize");
  Serial.println();
}

void loop() {
  //This will watch the serial port. 
  //If there is a command waiting it will be read in.
  if(Serial.available()>0){
    String command = Serial.readString();
    if(command=="Learn" || command=="learn"){
      
      //This instructs the user to send a serial string to identify the smell.
      Serial.println("What is being learned?");
      Serial.println();
      
      //Wait for a reply.
      while(Serial.available()<1){
      }
      
      //Read in the ID of the scent and store it to SmellID.
      SmellID=Serial.readString();
      
      //Now expose the Sensor to the scent for 10 seconds.
      Serial.println("Apply Scent for 10 seconds.");
      delay(2000);
      Serial.print("Learning ");
      Serial.print(SmellID);
      Serial.println("...");
      
      /*The learnPeak command requires a string as the title of the smell, and the storage location.
        It will sample the previously identified analog pins for 10 seconds and will associate the peak values
        with the supplied String at the supplied address location.*/
      myNose.learnPeak(SmellID,smellnum);
      smellnum++;
      
      //This instructs the user that it has finished sampling
      Serial.print(SmellID);
      Serial.println(" learned.");
      Serial.println();
      delay(1500);
      
      //This requests the next command.
      Serial.println("Now what would you like to do?");
      Serial.println("Learn");
      Serial.println("Recognize");
      Serial.println();
    }
    else if(command=="Recognize" || command=="recognize"){
      
      //Now expose the Sensor to the scent for 10 seconds.
      Serial.println("Apply Scent for 10 seconds.");
      delay(2000);
      Serial.println("Collecting scent...");
      
     /*The recognizePeak command collects, analyses, and returns the smell that it is guessing.
        It will sample the previously identified analog pins for 10 seconds and will compare the peak values
        to all of the scents it has previously recorded. Then it will return the closest scent.*/
      SmellID=myNose.recognizePeak();
      
      //This tells the user the closest scent recorded.
      Serial.print("I am smelling ");
      Serial.print(SmellID);
      Serial.println(".");
      Serial.println();
      delay(1500);
      
      //This requests the next command.
      Serial.println("Now what would you like to do?");
      Serial.println("Learn");
      Serial.println("Recognize");
      Serial.println();
    }
    
    //This indicates to the user that they didn't give a recognizable command.
    else{
      Serial.println("I don't recognize this command.");
      Serial.println();
      Serial.println("Please reply with one of the following options:");
      Serial.println("Learn");
      Serial.println("Recognize");
      Serial.println();
    }
  }
}

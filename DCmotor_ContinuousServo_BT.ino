/*
  includes:
  dc motor & controllers
  servo motor
  bluetooth
*/
//for references & background, check "basics & background" on github
//https://github.com/zinp5/r2d2-mini-project

#include <Servo.h>//include servo class,, necesaary

Servo headMotor;//servo object named headMoter

//-------motor right pins---------- (location of pins on ardy)
int motorSpeedPinR = 5;//speed pin
int motorR1 = 6; //direcitonal 1
int motorR2 = 7; //directional 2
//-------motor right pins----------

//--------Motor Left Pins--------
int motorL2= 8;
int motorL1 = 9;
int motorSpeedPinL = 10;
//--------Motor Left Pins--------


//order of communication
//phone----->BTcontroller(hc05)------>ardy----->command  (dont quote me on this,, just refernece)
  
int command; //this variable holds the value given by the bluetooth controller //Int to store app command state //lets change to char, yeah?
int Speed = 200; //should probably get this var working if we want variable speeds //range is 0 - 255.

void setup() {

  //---------DC motor initialization, set pinmode & speed---------------
  pinMode(motorSpeedPinR , OUTPUT);
  pinMode(motorSpeedPinL , OUTPUT);
  analogWrite(motorSpeedPinR , 255);
  analogWrite(motorSpeedPinL , 255);
  pinMode(motorR1 , OUTPUT);
  pinMode(motorL1 , OUTPUT);
  pinMode(motorR2 , OUTPUT);
  pinMode(motorL2 , OUTPUT);
  //---------DC motor initialization, set pinmode & speed---------------

  //--------headMotor servo initialization----------
  headMotor.attach(3);//signal pin is attatcehed to pin 3
  //--------headMotor servo initialization----------
  
  Stop(); //Initialize with all motors stoped

  Serial.begin(9600);//open up ardy serial, necessary for output, reading
  if(Serial.available() == 0){ Serial.println("--------- problem with reading bluetooth... -----------"); }
}
  
void loop() {
  if (Serial.available() > 0) {//if the thingymabob (either BTmodule or ardy, IDK) is reading something (if its reading, its greater than zero)

    command = Serial.read();//serial.read takes input given from the bluetooth controller and assiges command with the taken value
    Serial.println(command);//print command(what just came from the BTcontroller) to the serial monitor(cntrl-shft-m),, also adds new line

    switch (command) {//basic switch that tells ardy what to do with command that it just recieved
      case 49:
        forward();
        break;

      case 66:
        back();
        break;

      case 100: 
        Stop(); 
        break;

      case 'j':   //no need to call function,, only 1 line
        headMotor.write(0);//cw
        break;

      case 'k'://no need to call function,, only 1 line
        headMotor.write(180);//ccw
        break;

      //switch is probably broken if this ever runs,, make sure the cases work properly
      default:
        Serial.println("---------------------------------------------------------");
        Serial.println("-|-|-|-| 1 |-|-|-|-|-broken switch-|-|-|-|-| 1 |-|-|-|-|-");
        Serial.println("---------------------------------------------------------");
        delay(2000);
        break;
    }//========end of switch=========
  }//=======end of if statement=======
}//========end of loop=======
  
//----------------function definitions------------------

void forward() {
  digitalWrite(motorR1 , HIGH);
  digitalWrite(motorR2 , LOW);
  
  digitalWrite(motorL1 , HIGH);
  digitalWrite(motorL2 , LOW);

  Serial.println("we called forward");
}
  
void back() {
  digitalWrite(motorR1 , LOW);
  digitalWrite(motorR2 , HIGH);
  
  digitalWrite(motorL1 , LOW);
  digitalWrite(motorL2 , HIGH);

  Serial.println("we called backward");
}
 
  
void Stop() { //set both direction pins to low or high to stop
  digitalWrite(motorR1 , LOW);
  digitalWrite(motorR2 , LOW);
  
  digitalWrite(motorL1,LOW);
  digitalWrite(motorL2,LOW);

  headMotor.write(90);

  Serial.println("we called stop");
}
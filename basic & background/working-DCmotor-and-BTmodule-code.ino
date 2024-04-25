//HEAVILY COMMENTED 
//WORKING CODE
//FOR DC MOTOR AND BLUETOOTH

//References from
//https://www.youtube.com/watch?v=uT8-HPMS1cU&ab_channel=TechatHome
//&
//https://www.youtube.com/watch?v=qaFMSq-YNkg&ab_channel=EnjoyMechatronics
//&
//https://www.arduino.cc/reference/en/language/functions/digital-io/pinmode/
//https://arduino.stackexchange.com/questions/35873/whats-the-difference-between-analogwrite-and-digitalwrite
//https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/
//https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
//https://components101.com/modules/l293n-motor-driver-module

//for the BLUETOOTH CONTROLLER,, download this APK(ANDROID ONLY)(KINDA SHADY)
//https://drive.google.com/file/d/1WDyfUH6FnJeDbSP0XKtv6eiSfCAfAm4r/view?usp=drive_link
//watch this vid to go with it
//https://www.youtube.com/watch?v=uT8-HPMS1cU&ab_channel=TechatHome

//IIRC,, the motor were wired like the "enjoy mechanics" tutorial,, so keep that in mind when wiring and testing


  //-----assigning pins for right motor------------
    int mSpeedPin = 3;//for setting speed of motor 
    int mDirection1 = 4;//if wheel on right side,, assigning HIGH moves it backwards 
    int mDirection2 = 5;//if wheel on right side,, assigning HIGH move it forwards 
  //-----assigning pins for right motor-------

  //------assigning pins for left motor-------
    int mSpeedLeft = 10;
    int mDirectionLeft1 = 9;
    int mDirectionLeft2 = 8;
  //-------assigning pins for left motor-------


  //phone----->BTcontroller(hc05)------>ardy----->command  (dont quote me on this,, just refernece)
  
  int command; //this variable holds the value given by the bluetooth controller//Int to store app command state.

  void setup() {
    
    //------assign all 3 pins from MOTOR controller to OUTPUT----
    pinMode(mSpeedPin, OUTPUT);
    pinMode(mDirection1, OUTPUT);
    pinMode(mDirection2, OUTPUT);
    //------assign all 3 pins from MOTOR controller to OUTPUT----

    //LEFT MOTOR PINMODES ARE NEVER IMPLEMENTED IN THIS VERSION
    //LEFT MOTOR PINMODES ARE NEVER IMPLEMENTED IN THIS VERSION
    //LEFT MOTOR PINMODES ARE NEVER IMPLEMENTED IN THIS VERSION

    //---assigning base speeds for both motors-------
    analogWrite(mSpeedPin, 100);//set speed of motor to 100(about half of max speed(255)) 
    analogWrite(mSpeedLeft, 100);//despite pinmode never being set, this still works...
    //assigning base speeds for both motors------

    //okay, as far as I know, serial is like cout and cin(maybe even ifstream or ofstream),, i don't know what .begin(int) is for
    Serial.begin(9600);  //Set the baud rate to your Bluetooth module. (int val is different for every system??? be sure to check(IDK how))
  }
  
  void loop() {
    if (Serial.available() > 0) {//if the thingymabob (either BTmodule or ardy IDK) is reading something (if its reading, its greater than zero)
      command = Serial.read();//serial.read takes input given from the bluetooth controller and assiges command with the taken value
      Serial.println(command);//print command(what just came from the BTcontroller) to the serial monitor(cntrl-shft-m),, also adds new line

      switch (command) {//basic switch that tells ardy what to do with command that it just recieved
      
        case 49://49 is some random int val that we got while testing,, might be different when you try testing again
          forward();
          break;

        default://switch is probably broken if this ever runs,, make sure the cases work properly
          Serial.println("asdfasdf");
          delay(1250);
          break;
      }//========end of switch=========
    }//==========end of if statemnt========
  }//=======end of master loop=========
  
  //--------method / function definitions--------------
  void forward() {
    Serial.println("we called forward");//be sure to add a statement like this to every function call,, just a simple ("We called this function!") 

    //as far as im conserned, the directions should always be opposite of eachother,, so be sure they are always opposite
    //(HIGH is max, LOW is off),, 

    //------assuming motor is on right side,, this move the wheel forward---------
    digitalWrite(mDirection1, LOW);
    digitalWrite(mDirection2, HIGH);
    //------assuming motor is on right side,, this move the wheel forward---------

    //------assuming motor is on left side,, this move the wheel forward---------
    digitalWrite(mDirectionLeft1, HIGH);
    digitalWrite(mDirectionLeft2, LOW);
    //------assuming motor is on left side,, this move the wheel forward---------
    
    delay(2000);//wait 2 seconds before switching

    //------assuming motor is on right side,, this move the wheel backwards---------
    digitalWrite(mDirection1, HIGH);
    digitalWrite(mDirection2, LOW);
    //------assuming motor is on right side,, this move the wheel backwards---------

    //------assuming motor is on left side,, this move the wheel backwards---------
    digitalWrite(mDirectionLeft1, LOW);
    digitalWrite(mDirectionLeft2, HIGH);
    //------assuming motor is on left side,, this move the wheel backwards---------

    delay(2000);//wait 2 seconds before switching
  }
  //--------method / function definitions--------------
  
  

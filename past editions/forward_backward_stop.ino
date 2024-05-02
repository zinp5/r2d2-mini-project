//HEAVILY COMMENTED 
//WORKING CODE
//FOR DC MOTOR AND BLUETOOTH

//note:code is messy and some of the code served no purpose,, still works tho

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


int motorSpeedPinR = 5;
int motorR1 = 6;
int motorR2 = 7;

//Motor Left Pins
int motorL2= 8;
int motorL1 = 9;
int motorSpeedPinL = 10;



  //phone----->BTcontroller------>ardy----->command  (dont quote me on this,, just refernece)
  
  int command; //this variable holds the value given by the bluetooth controller//Int to store app command state.
  int Speed = 204; //should probably get this var working if we want variable speeds //range is 0 - 255.
  int num;
  
  //rest of these vars are unknown purpose
  int Speedsec;
  int buttonState = 0;
  int lastButtonState = 0;
  int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
  int brakeTime = 45;
  int brkonoff = 1; //1 for the electronic braking system, 0 for normal.

  void setup() {
    pinMode(motorSpeedPinR , OUTPUT);
    pinMode(motorSpeedPinL , OUTPUT);
    analogWrite(motorSpeedPinR , 255);
    analogWrite(motorSpeedPinL , 255);
    pinMode(motorR1 , OUTPUT);
    pinMode(motorL1 , OUTPUT);
    pinMode(motorR2 , OUTPUT);
    pinMode(motorL2 , OUTPUT);
    
    Serial.begin(9600);
  }
  
  void loop() {
    if (Serial.available() > 0) {//if the thingymabob (either BTmodule or ardy IDK) is reading something (if its reading, its greater than zero)
      command = Serial.read();//serial.read takes input given from the bluetooth controller and assiges command with the taken value
      Serial.println(command);//print command(what just came from the BTcontroller) to the serial monitor(cntrl-shft-m),, also adds new line
      Stop(); //Initialize with motors stoped.

      switch (command) {//basic switch that tells ardy what to do with command that it just recieved
        case 49:
          forward();
          break;
        case 66:
          back();
          break;
        //(all cases(besides break) are random and dont do anthing... plz fix)
        case 100: 
          Stop(); 
          break;
        
        default://switch is probably broken if this ever runs,, make sure the cases work properly
          Serial.println("asdfasdf");
          delay(1250);
          break;
      }//========end of switch=========
      Speedsec = Turnradius;//no clue what this does
      if (brkonoff == 1) {//or this
        brakeOn();
      } else {//or this
        brakeOff();
      }
    }//==========end of if statemnt========
  }//=======end of master loop=========
  
  //--------method / function definitions--------------
  void forward() {
    //MOTOR Right speed:100
    digitalWrite(motorR1 , HIGH);
    digitalWrite(motorR2 , LOW);
  
  //MOTOR Left speed:100
    digitalWrite(motorL1,HIGH);
    digitalWrite(motorL2,LOW);

    Serial.println("we called forward");
  
  }
  
  //------------the rest of these funcitons are untested
  void back() {
  
   //MOTOR Right speed:100
    digitalWrite(motorR1 , LOW);
    digitalWrite(motorR2 , HIGH);
  
  //MOTOR Left speed:100
    digitalWrite(motorL1,LOW);
    digitalWrite(motorL2,HIGH);
    Serial.println("we called backward");
  }
  
  void Stop() {
      
    digitalWrite(motorR1 , LOW);
    digitalWrite(motorR2 , LOW);
  
  
    digitalWrite(motorL1,LOW);
    digitalWrite(motorL2,LOW);
    Serial.println("we called stop");
  
  }
  
  void brakeOn() {
    //Heres the future use: an electronic braking system!
    // read the pushbutton input pin:
    buttonState = command;
    // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
      // if the state has changed, increment the counter
      if (buttonState == 10) {//not supposed to be 10
        if (lastButtonState != buttonState) {
          // digitalWrite(in1, HIGH);
          // digitalWrite(in2, HIGH);
          // digitalWrite(in3, HIGH);
          // digitalWrite(in4, HIGH);
          delay(brakeTime);
          Stop();
        }
      }
      // save the current state as the last state,
      //for next time through the loop
      lastButtonState = buttonState;
    }
  }
  void brakeOff() {
  
  }
  //--------method / function definitions--------------

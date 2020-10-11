



#include <PS4Controller.h>

#include <AccelStepper.h>


const int motEn = 2;


int pace = 600;
int zip = 200;
int dataIn;
int m;


// Define some steppers and the pins the will use
AccelStepper LFwheel(1, 27, 25);  // (Type:driver, STEP, DIR)
AccelStepper RFwheel(1, 32, 12 );
AccelStepper LRwheel(1, 9, 14 );
AccelStepper RRwheel(1, 4,  0);


void setup()
{  
    pinMode(motEn, OUTPUT);
    digitalWrite(motEn, 0);
    

      PS4.begin("03:03:03:03:03:03");

  
    LFwheel.setMaxSpeed(pace);
    LFwheel.setAcceleration(zip);
    //LFwheel.moveTo(1000000);
    
    RFwheel.setMaxSpeed(pace);
    RFwheel.setAcceleration(zip);
   // RFwheel.moveTo(1000000);

    LRwheel.setMaxSpeed(pace);
    LRwheel.setAcceleration(zip);
    //LRwheel.moveTo(10000000);

    RRwheel.setMaxSpeed(pace);
    RRwheel.setAcceleration(zip);
    //RRwheel.moveTo(1000000);

    Serial.begin(9600);
    //Serial1.begin(9600);
     PS4.attachOnConnect(onConnection);
     PS4.attach(onEvent);
    Serial.println("setup complete");
    //pwrChk();

}

void onConnection(){
  if (PS4.isConnected()){
    Serial.println("controller connected. ready?");
    digitalWrite(motEn, 1);
    PS4.setLed(250,0,0);
    PS4.sendToController();
  }
}

void onEvent(){

  if(PS4.event.button_down.up){
    m = 8;
  }
  if(PS4.event.button_down.down){
    m = 2;
  }
  if(PS4.event.button_down.left){
    m = 4;
  }
  if(PS4.event.button_down.right){
    m = 6;
  }
  if(PS4.event.button_down.upleft){
    m = 7;
  }
  if(PS4.event.button_down.upright){
    m = 9;
  }
  if(PS4.event.button_down.downleft){
    m = 1;
  }
  if(PS4.event.button_down.downright){
    m = 3;
  }
  if(PS4.event.button_down.l1){
    rotLeft();
  }
  if(PS4.event.button_down.r1){
    rotRight();
  }

  else {
    stap();
    }
}


void loop()
{
      
    RRwheel.runSpeed();
    LRwheel.runSpeed();
    LFwheel.runSpeed();
    RFwheel.runSpeed();
    
    look();

   switch (m){
      case 8:
        moveForw();
       break;

      case 0:
        rotLeft();
       break;

      case 9:
        forwRight();
       break;
       
      case 7:
        forwLeft();
       break;
       
      case 4:
        moveLeft();
       break;

      case 6:
        moveRight();
       break;

      case 1:
        backLeft();
       break;

      case 3:
        backRight();
       break;

      case 2:
        moveBack();
       break;
       
      case 5:
        rotRight();
       break;

      default:
        stap();
       break;  
    }
  //pwrChk();
}
void moveForw(){
  Serial.println("moving forward");
  LFwheel.setSpeed(pace);
  RFwheel.setSpeed(pace);
  RRwheel.setSpeed(pace);
  LRwheel.setSpeed(pace);
  }
void moveBack(){
  Serial.println("moving backward");
  LFwheel.setSpeed(-pace);
  RFwheel.setSpeed(-pace);
  RRwheel.setSpeed(-pace);
  LRwheel.setSpeed(-pace);
  }
void moveLeft(){
  Serial.println("moving left");
  LFwheel.setSpeed(-pace);
  RFwheel.setSpeed(pace);
  RRwheel.setSpeed(-pace);
  LRwheel.setSpeed(pace);
  }
void moveRight(){
  Serial.println("moving right");
  LFwheel.setSpeed(pace);
  RFwheel.setSpeed(-pace);
  RRwheel.setSpeed(pace);
  LRwheel.setSpeed(-pace);
  }
void rotLeft(){
  Serial.println("rotating left");
  LFwheel.setSpeed(-pace);
  RFwheel.setSpeed(pace);
  RRwheel.setSpeed(pace);
  LRwheel.setSpeed(-pace);
  }
void rotRight(){
  Serial.println("rotating right");
  LFwheel.setSpeed(pace);
  RFwheel.setSpeed(-pace);
  RRwheel.setSpeed(-pace);
  LRwheel.setSpeed(pace);
  }
void forwLeft(){
  Serial.println("forward leftishly");
  LFwheel.setSpeed(0);
  RFwheel.setSpeed(pace);
  RRwheel.setSpeed(0);
  LRwheel.setSpeed(pace);
  }
void forwRight(){
  Serial.println("forward rightish");
  LFwheel.setSpeed(pace);
  RFwheel.setSpeed(0);
  RRwheel.setSpeed(pace);
  LRwheel.setSpeed(0);
  }
void backLeft(){
  Serial.println("back leftish");
  LFwheel.setSpeed(-pace);
  RFwheel.setSpeed(0);
  RRwheel.setSpeed(-pace);
  LRwheel.setSpeed(0);
  }
void backRight(){
  Serial.println("back right");
  LFwheel.setSpeed(0);
  RFwheel.setSpeed(-pace);
  RRwheel.setSpeed(0);
  LRwheel.setSpeed(-pace);
  }
void stap(){
  Serial.println("STOP");
  LFwheel.setSpeed(0);
  RFwheel.setSpeed(0);
  RRwheel.setSpeed(0);
  LRwheel.setSpeed(0);
  }


void pwrChk(){
  // Monitor the battery voltage
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.00) * 3; // Convert the reading values from 5v to suitable 12V i
  Serial.println(voltage);
  // If voltage is below 11V turn on the LED
  if (voltage < 11) {
  
   }
  }

void look(){
 /* if (PS4.isConnected()) {
    Serial.println("reading serial");
    if ( PS4.data.button.up ){
      moveForw();
    }
    if (PS4.data.button.left){
      moveLeft();  
   } 
  }*/
  
  if (Serial.available() > 0) {
    Serial.println("reading serial");
    dataIn = Serial.read();
    Serial.println(dataIn);
    m = dataIn - 48;
}


}




  



/*
   BYJ48 Stepper motor code
   Connect :
   IN1 >> D8
   IN2 >> D9
   IN3 >> D10
   IN4 >> D11
   VCC ... 5V Prefer to use external 5V Source
   Gnd
   written By :Mohannad Rawashdeh
  https://www.instructables.com/member/Mohannad+Rawashdeh/
     28/9/2013
  */

#define L1  8
#define L2  9
#define L3  10
#define L4  11
#define R5  29
#define R6  27
#define R7  25
#define R8  23

const int delayBetweenSteps = 0;
const int anPin = 1;
int StepsR = 0;
int StepsL = 0;
const int stepsPerTurn = 4095; 
boolean DirectionL = true;
boolean DirectionR = true;// gre
const double Circumference = 7.853981634;
unsigned long last_timeL= 0;
unsigned long last_timeR= 0;
unsigned long currentMicros;
int steps_RemainL=0;
int steps_RemainR=0;
void setup()
{
Serial.begin(9600);
pinMode(L1, OUTPUT); 
pinMode(L2, OUTPUT); 
pinMode(L3, OUTPUT); 
pinMode(L4, OUTPUT);
pinMode(R5, OUTPUT);
pinMode(R6, OUTPUT);
pinMode(R7, OUTPUT);
pinMode(R8, OUTPUT);
analogReference(DEFAULT);
// delay(1000);

}
void loop()
{
 Serial.println(analogRead(anPin));

 
 if(analogRead(anPin) < 200){
  go(1, true);
 }else{
  go(1, true);
 }
 
//delay(1000);


}
bool rotateRXTurnsBack(bool clockwise){
  DirectionR = clockwise; // Turning Clockwise
    currentMicros = micros();
    if((currentMicros-last_timeR)>=delayBetweenSteps){
      //Serial.println("currentMicros: " + currentMicros);
      stepperRB();
      stepperLB();
      last_timeR=currentMicros;
      return true;
    }
    return false;
}
bool rotateRXTurnsForward(bool clockwise){
  DirectionR = clockwise; // Turning Clockwise
    currentMicros = micros();
    if((currentMicros-last_timeR)>=delayBetweenSteps){
      //Serial.println("currentMicros: " + currentMicros);
      stepperRF();
      stepperLF();
      last_timeR=currentMicros;
      return true;
    }
    return false;
}
void go(double Distance, boolean Direction)
{
  int stepsRemain= (int) (Distance*stepsPerTurn/Circumference);
  currentMicros = micros();
  last_timeL = currentMicros;
  last_timeR = currentMicros;
  bool retVal =false;
 
  while(stepsRemain > 0){
    //Serial.println("steps: ");
    //Serial.println(stepsRemain);
    if(Direction == true)
    {
      retVal = retVal || rotateRXTurnsBack(Direction);
      // Move forward
    }else
    {
      retVal = retVal || rotateRXTurnsForward(Direction);
      //Move backwards
     }
     if(retVal){
        stepsRemain--;
     }
     
  }
}

void turnInPlace(int Degree, boolean Direction)
{
  int stepsRemain= (int) (Distance*stepsPerTurn/Circumference);
  currentMicros = micros();
  last_timeL = currentMicros;
  last_timeR = currentMicros;
  bool retVal =false;
  
  if (Direction = true)
  {
     retVal = retVal || rotateRXTurnsForwards(Direction);
    //Turn left 90 degrees
  }else
  {
    retVal = retVal || rotateRXTurnsForward(Direction);
      //Move backwards
    //Turn right 90 degrees
  }
  if(retVal){
        stepsRemain--;
     }
}
void stepperLB(){
    SetDirectionL();
    switch(StepsL){
       case 0:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, LOW);
         digitalWrite(L4, HIGH);///////////////////////
       break; 
       case 1:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, HIGH);
         digitalWrite(L4, HIGH);//////////////////////
       break; 
       case 2:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, HIGH);
         digitalWrite(L4, LOW);/////////////////////
       break; 
       case 3:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, HIGH);
         digitalWrite(L3, HIGH);
         digitalWrite(L4, LOW);/////////////////
       break; 
       case 4:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, HIGH);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);///////////////
       break; 
       case 5:
         digitalWrite(L1, HIGH); 
         digitalWrite(L2, HIGH);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);
       break; 
         case 6:
         digitalWrite(L1, HIGH); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);
       break; 
       case 7:
         digitalWrite(L1, HIGH); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, LOW);
         digitalWrite(L4, HIGH);
       break; 
       default:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);
       break; 
    }
}
void stepperRB(){
    SetDirectionR();
    //Serial.print("StepsR: ");
    //Serial.print(StepsR);
    switch(StepsR){
       case 0:
         digitalWrite(R5, HIGH); 
         digitalWrite(R6, LOW);
         digitalWrite(R7, LOW);
         digitalWrite(R8, HIGH);
       break; 
       case 1:
         digitalWrite(R5, HIGH); 
         digitalWrite(R6, LOW);
         digitalWrite(R7, LOW);
         digitalWrite(R8, LOW);
       break; 
       case 2:
         digitalWrite(L1, HIGH); 
         digitalWrite(L2, HIGH);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);
       break; 
       case 3:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, HIGH);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);
       break; 
       case 4:
         digitalWrite(R5, LOW); 
         digitalWrite(R6, HIGH);
         digitalWrite(R7, HIGH);
         digitalWrite(R8, LOW);
       break; 
       case 5:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, HIGH);
         digitalWrite(L4, LOW);
       break; 
         case 6:
         digitalWrite(R5, LOW); 
         digitalWrite(R6, LOW);
         digitalWrite(R7, HIGH);
         digitalWrite(R8, HIGH);
       break; 
       case 7:
         digitalWrite(R5, LOW); 
         digitalWrite(R6, LOW);
         digitalWrite(R7, LOW);
         digitalWrite(R8, HIGH);
       break; 
       default:
         digitalWrite(R5, LOW); 
         digitalWrite(R6, LOW);
         digitalWrite(R7, LOW);
         digitalWrite(R8, LOW);
       break; 
    }
}

void stepperLF(){
    SetDirectionL();
    switch(StepsL){
       case 0:
         digitalWrite(L1, HIGH); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, LOW);
         digitalWrite(L4, HIGH);///////////////////////
       break; 
       case 1:
         digitalWrite(L1, HIGH); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);//////////////////////
       break; 
       case 2:
         digitalWrite(L1, HIGH); 
         digitalWrite(L2, HIGH);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);/////////////////////
       break; 
       case 3:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, HIGH);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);/////////////////
       break; 
       case 4:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, HIGH);
         digitalWrite(L3, HIGH);
         digitalWrite(L4, LOW);///////////////
       break; 
       case 5:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, HIGH);
         digitalWrite(L4, LOW);
       break; 
         case 6:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, HIGH);
         digitalWrite(L4, HIGH);
       break; 
       case 7:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, LOW);
         digitalWrite(L4, HIGH);
       break; 
       default:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);
       break; 
    }
}

void stepperRF(){
    SetDirectionR();
    //Serial.print("StepsR: ");
    //Serial.print(StepsR);
    switch(StepsR){
       case 0:
         digitalWrite(R5, HIGH); 
         digitalWrite(R6, LOW);
         digitalWrite(R7, LOW);
         digitalWrite(R8, HIGH);
       break; 
       case 1:
         digitalWrite(R5, HIGH); 
         digitalWrite(R6, LOW);
         digitalWrite(R7, LOW);
         digitalWrite(R8, LOW);
       break; 
       case 2:
         digitalWrite(L1, HIGH); 
         digitalWrite(L2, HIGH);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);
       break; 
       case 3:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, HIGH);
         digitalWrite(L3, LOW);
         digitalWrite(L4, LOW);
       break; 
       case 4:
         digitalWrite(R5, LOW); 
         digitalWrite(R6, HIGH);
         digitalWrite(R7, HIGH);
         digitalWrite(R8, LOW);
       break; 
       case 5:
         digitalWrite(L1, LOW); 
         digitalWrite(L2, LOW);
         digitalWrite(L3, HIGH);
         digitalWrite(L4, LOW);
       break; 
         case 6:
         digitalWrite(R5, LOW); 
         digitalWrite(R6, LOW);
         digitalWrite(R7, HIGH);
         digitalWrite(R8, HIGH);
       break; 
       case 7:
         digitalWrite(R5, LOW); 
         digitalWrite(R6, LOW);
         digitalWrite(R7, LOW);
         digitalWrite(R8, HIGH);
       break; 
       default:
         digitalWrite(R5, LOW); 
         digitalWrite(R6, LOW);
         digitalWrite(R7, LOW);
         digitalWrite(R8, LOW);
       break; 
    }
}
void SetDirectionR(){
  if(DirectionR){ StepsR++;}
  if(!DirectionR){ StepsR--; }
  if(StepsR>7){StepsR=0;}
  if(StepsR<0){StepsR=7; }
}
void SetDirectionL(){
  if(DirectionL){ StepsL++;}
  if(!DirectionL){ StepsL--; }
  if(StepsL>7){StepsL=0;}
  if(StepsL<0){StepsL=7; }
}

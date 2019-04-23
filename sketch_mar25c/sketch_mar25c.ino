

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

#define IN1  8
#define IN2  9
#define IN3  10
#define IN4  11
#define IN5  29
#define IN6  27
#define IN7  25
#define IN8  23

const int delayBetweenSteps = 1000;
const int anPin = 1;
int StepsR = 0;
int StepsL = 0;
const long stepsPerTurn = 4095; 
const double Circumference = 7.853981634;
const double turnCircumference = 21.9911485751;
const double fullTurn = 360;
unsigned long last_timeL= 0;
unsigned long last_timeR= 0;
unsigned long currentMicrosL;
unsigned long currentMicrosR;
int steps_RemainL=0;
int steps_RemainR=0;
void setup()
{
Serial.begin(9600);
pinMode(IN1, OUTPUT); 
pinMode(IN2, OUTPUT); 
pinMode(IN3, OUTPUT); 
pinMode(IN4, OUTPUT);
pinMode(IN5, OUTPUT);
pinMode(IN6, OUTPUT);
pinMode(IN7, OUTPUT);
pinMode(IN8, OUTPUT);
analogReference(DEFAULT);
// delay(1000);

}
void loop()
{
 Serial.println(analogRead(anPin));

 //delay(5000);
 //go(100, true);
 turnInPlace(70.0, false);
 //go(100, true);
 

  
 
 /*if(analogRead(anPin) < 200){
  go(1, true);
 }else{
  go(1, false);
 }*/
 
delay(2000);


}
bool rotateL(bool clockwise){
    currentMicrosL = micros();
   // Serial.print("currentMicros: ");
   // Serial.print(currentMicrosL-last_timeL);
   // Serial.print("delay: ");
   // Serial.println(delayBetweenSteps);
 
    if((currentMicrosL-last_timeL)>=delayBetweenSteps){
      stepperL(clockwise);
      last_timeL=currentMicrosL;
      // Serial.print("lastTimeL: ");
     // Serial.print(last_timeL);
      return true;
    }
    return false;
}
bool rotateR(bool clockwise){
    currentMicrosR = micros();
    if((currentMicrosR-last_timeR)>=delayBetweenSteps){
      //Serial.println("currentMicros: " + currentMicrosR);
      stepperR(clockwise);
      last_timeR=currentMicrosR;
      return true;
    }
    return false;
}
void go(double Distance, boolean Direction)
{
  long stepsRemain= (long) (Distance*stepsPerTurn/Circumference);
  currentMicrosL = micros();
  currentMicrosR = currentMicrosL;
  last_timeL = currentMicrosL;
  last_timeR = currentMicrosR;

 
  while(stepsRemain > 0){
      bool retValR = false;
     bool retValL =false;
    
    while(true){
    //  delay(500);
      //Serial.print("steps: ");
      //Serial.print(stepsRemain);
     // Serial.print("retValL");
     // Serial.print(retValL);
     // Serial.print("retValR");
     // Serial.println(retValR);
      if(Direction == true)
      {
        if(!retValR){
          retValR =  rotateR(Direction);
        }
        if(!retValL){

          retValL =  rotateL(!Direction);
        }
        // Move forward
      }else
      {
        if(!retValR){
          retValR =  rotateR(!Direction);
        }
        if(!retValL){
          retValL =  rotateL(Direction);
        }
        //Move backwards
       }
       if(retValR && retValL){
          stepsRemain--;
          break;
       }
    }
     
  }
}

void turnInPlace(double Degree, boolean Direction)
{
  long stepsRemain= (long) (Degree/fullTurn*turnCircumference*stepsPerTurn/Circumference);
 currentMicrosL = micros();
  currentMicrosR = currentMicrosL;
  last_timeL = currentMicrosL;
  last_timeR = currentMicrosR;

 
  while(stepsRemain > 0){
     bool retValR = false;
     bool retValL =false;
    
    while(true){
    //  delay(500);
     //Serial.print("steps: ");
     //Serial.print(stepsRemain);
     // Serial.print("retValL");
     // Serial.print(retValL);
     // Serial.print("retValR");
     // Serial.println(retValR);
      if(Direction == true)
      {
        if(!retValR){
          retValR =  rotateR(!Direction);
        }
        if(!retValL){

          retValL =  rotateL(!Direction);
        }
        // Move forward
      }else
      {
        if(!retValR){
          retValR =  rotateR(!Direction);
        }
        if(!retValL){
          retValL =  rotateL(!Direction);
        }
        //Move backwards
       }
       if(retValR && retValL){
          stepsRemain--;
          break;
       }
    }
     
  }
}
void stepperL(bool direction){
   setDirectionL(direction);
   switch(StepsL){
   case 0:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, HIGH);
   break; 
   case 1:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, HIGH);
   break; 
   case 2:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, LOW);
   break; 
   case 3:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, HIGH);
     digitalWrite(IN8, LOW);
   break; 
   case 4:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
   case 5:
     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, HIGH);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
     case 6:
     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
   case 7:
     digitalWrite(IN5, HIGH); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, HIGH);
   break; 
   default:
     digitalWrite(IN5, LOW); 
     digitalWrite(IN6, LOW);
     digitalWrite(IN7, LOW);
     digitalWrite(IN8, LOW);
   break; 
    }
}
void stepperR(bool direction){
   setDirectionR(direction);
   switch(StepsR){
   case 0:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   case 1:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, HIGH);
   break; 
   case 2:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 3:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, HIGH);
     digitalWrite(IN4, LOW);
   break; 
   case 4:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 5:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, HIGH);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
     case 6:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
   case 7:
     digitalWrite(IN1, HIGH); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, HIGH);
   break; 
   default:
     digitalWrite(IN1, LOW); 
     digitalWrite(IN2, LOW);
     digitalWrite(IN3, LOW);
     digitalWrite(IN4, LOW);
   break; 
    }
}
void setDirectionR(bool direction){
  if(direction){StepsR++;}
  else{StepsR--;}
  if(StepsR>7){StepsR=0;}
  if(StepsR<0){StepsR=7; }
}
void setDirectionL(bool direction){
  if(direction){StepsL++;}
  else{StepsL--;}
  if(StepsL>7){StepsL=0;}
  if(StepsL<0){StepsL=7; }
}

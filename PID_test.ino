#define LF 2
#define LB 4
#define LEN 5
#define RF 7
#define RB 8
#define REN 6
#define Lsence A0
#define Rsence A1

void setup() {
  Serial.begin(9600);
  for(int i=2;i<9;i++){
    pinMode(i,OUTPUT);
  }
  for(int i=2;i<9;i++){
    digitalWrite(i,LOW);
  }

}

bool Lwall=0;
bool Rwall=0;

float kp=150;
float kd=400;
float ki=0;

int lstval=0;
long total_err=0;
int M=250;

void loop() {
Lwall=!digitalRead(Lsence);
Rwall=!digitalRead(Rsence);
Serial.print(Lwall);Serial.print(" L ,  R");Serial.println(Rwall);

  int err=Lwall-Rwall;

 int PIDval=PIDcontroll(err);
  
  TURN(M+PIDval,M-PIDval);

  
  


}

int PIDcontroll(int err){
   int Pterm = err*kp;
  int Dterm = (err-lstval)*kd;
  int Iterm = total_err*ki;
  
  int diff=Pterm+Dterm+Iterm;

  lstval=err;
  total_err =+ err;

  return diff;
}

void STOP(){
  digitalWrite(LF,LOW);
  digitalWrite(LB,LOW);
  digitalWrite(RF,LOW);
  digitalWrite(RB,LOW);
  analogWrite(LEN,LOW);
  analogWrite(REN,LOW);
}

void FORWARD(int Speed){
  digitalWrite(LF,HIGH);
  digitalWrite(LB,LOW);
  digitalWrite(RF,HIGH);
  digitalWrite(RB,LOW);
  analogWrite(LEN,Speed);
  analogWrite(REN,Speed);
}

void BACKWARD(int Speed){
  digitalWrite(LF,LOW);
  digitalWrite(LB,HIGH);
  digitalWrite(RF,LOW);
  digitalWrite(RB,HIGH);
  analogWrite(LEN,Speed);
  analogWrite(REN,Speed);
}

void TURN(int LSpeed, int RSpeed){
  if(LSpeed>255){
    LSpeed=255;
  }
  if(LSpeed<0){
    LSpeed=0;
  }
  if(RSpeed>255){
    RSpeed=255;
  }
  if(RSpeed<0){
    RSpeed=0;
  }
  digitalWrite(LF,HIGH);
  digitalWrite(LB,LOW);
  digitalWrite(RF,HIGH);
  digitalWrite(RB,LOW);
  analogWrite(LEN,LSpeed);
  analogWrite(REN,RSpeed);
}

void TURNRIGHT(int Speed){
  digitalWrite(LF,HIGH);
  digitalWrite(LB,LOW);
  digitalWrite(RF,LOW);
  digitalWrite(RB,LOW);
  analogWrite(LEN,Speed);
  analogWrite(REN,LOW);
}

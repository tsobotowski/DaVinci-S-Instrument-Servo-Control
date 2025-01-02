#include <Servo.h>

Servo one; 
Servo two;
Servo three; 
Servo four; 

//Servo limits ***VERY IMPORTANT***
int lim1 = 140;
int lim2 = 70; //TEMP
int lim3 = 70; //TEMP
int lim4 = 70; //TEMP
int limGrip = 50; //TEMP 

void center(){ //Center all servos
  one.write(90);
  two.write(90);
  three.write(90);
  four.write(90);
}

void setOne(int pos){
  if(abs(pos) > lim1){ 
    return;
  }
  else{
    pos += 90;
  one.write(pos); 
}
}

void setTwo(int pos){
  if(abs(pos) > lim2){ // fix
    return;
  }
  else{
    pos += 90;
  two.write(pos); 
}
}

void setThree(int pos){//TODO ADD RELATION FOR GRIPS SO THEY ARENT FORCED PAST CLOSE OR OPEN
  if(abs(pos) > lim3){ // fix
    return;
  }
  else{
    pos += 90;
  three.write(pos); 
}
}
void setFour(int pos){ // TODO ADD RELATION FOR GRIPS SO THEY ARENT FORCED PAST CLOSE OR OPEN  || abs(pos - three.read()) > limGrip
  if(abs(pos) > lim4){ // fix
    return;
  }
  else{
    pos += 90;
  four.write(pos); 
}
}

void solve(int x, int y, int grip, int r){
  int onePos = r;
  int twoPos = x;
  int threePos = (x + y) + (grip / 2);
  int fourPos = (x + y)  - (grip / 2);
  set(onePos, twoPos, threePos, fourPos);
  Serial.println(abs(threePos - fourPos));
}

void set(int onePos, int twoPos, int threePos, int fourPos){
  setOne(onePos);
  setTwo(twoPos);
  setThree(threePos);
  setFour(fourPos);
}

void setup() {
  one.attach(6);  
  two.attach(9);
  three.attach(10);
  four.attach(11);
  center();

  Serial.begin(9600);//TEMP
}

void loop() {
int x = analogRead(0);
int y = analogRead(1);
int z = analogRead(2);
int g = analogRead(3);

x = map(x, 0, 1023, -90, 90);
y = map(y, 0, 1023, -90, 90);
z = map(z, 0, 1023, -180, 180);
g = map(g, 0, 1023, -50, 50);
Serial.println(g);
solve(x, y, g, z);



}

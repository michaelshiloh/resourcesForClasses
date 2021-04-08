const int REDLEDPIN = 2;
const int GREENLEDPIN = 5;
const int POTPIN = A0;
const int LDRPIN = A1; 

void setup() {
  Serial.begin(9600);
  Serial.println("0,0");
  pinMode(2, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop() {
  while (Serial.available()) {
    int firstValue = Serial.parseInt();
    int secondValue = Serial.parseInt();
    if (Serial.read() == '\n') {
      digitalWrite(REDLEDPIN, firstValue);
      digitalWrite(GREENLEDPIN, secondValue);
      int potValue = analogRead(POTPIN);
      delay(1);
      int LDRValue = analogRead(LDRPIN);
      delay(1);
      Serial.print(potValue);
      Serial.print(',');
      Serial.println(LDRValue);
    }
  }
}

/*

import processing.serial.*;
Serial myPort;
int xPos=0;
int yPos=0;
boolean clickOnLeft=false;
boolean clickOnRight=false;

void setup(){
  size(960,720);
  printArray(Serial.list());
  String portname=Serial.list()[1];
  println(portname);
  myPort = new Serial(this,portname,9600);
  myPort.clear();
  myPort.bufferUntil('\n');
}

void draw(){
  background(255);
  ellipse(xPos,yPos,30,30);
  if (mousePressed){
    if(mouseX<=width/2)
      clickOnLeft=true;
    else
      clickOnRight=true;
  }else{
    clickOnLeft=clickOnRight=false;
  }
}

void serialEvent(Serial myPort){
  String s=myPort.readStringUntil('\n');
  s=trim(s);
  if (s!=null){
    println(s);
    int values[]=int(split(s,','));
    if (values.length==2){
      xPos=(int)map(values[0],0,1023,0, width);
      yPos=(int)map(values[1],0,1023,0, height);
    }
  }
  myPort.write(int(onOff)+","+int(onOff2)+"\n");
}

 */

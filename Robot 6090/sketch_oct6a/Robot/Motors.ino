const int ENB = 2;
const int input1 = 4; 
const int input2 = 5;  
const int fast = 255;
const int medium = 127; 
const int slow = 60;
const int ENB2 = 3;
const int input3 = 1; 
const int input4 = 2; 


void setup() { 
  pinMode ( input1 , OUTPUT); 
  pinMode ( input2 , OUTPUT); 
  pinMode ( ENB , OUTPUT); 
 
 /* pinMode ( input3 , OUTPUT); 
  pinMode ( input4 , OUTPUT); 
  pinMode ( ENB2 , OUTPUT); 
  Serial.begin (9600);*/
}

void moveForward() {
    // Set motor speeds

  digitalWrite(ENB,HIGH);
  digitalWrite(input1,HIGH);
  digitalWrite(input2,LOW);

 /* digitalWrite(ENB2,HIGH);
  digitalWrite(trigger2,HIGH);*/
}

void stopMotors() {
    // Set motor speeds to zero
  digitalWrite(ENB,LOW);
/*
  digitalWrite(ENB2,LOW);
  digitalWrite(trigger2,LOW); */
}

void turnRight() {
    // Left motor forward
    // Right motor backward
}
const int sensor = A0; 
int sensor_value = 100; 
float voltage = 0; 

 



void objectMove(){
  moveForward();
}

void objectHalt(int sensor_value){
  if(sensor_value <= 10){ // distance to stop from walls
    stopMotors();
  }
}

void loop() { 

  // put your main code here, to run repeatedly: 
  

  objectMove();
 // objectHalt(sensor_value);



} 
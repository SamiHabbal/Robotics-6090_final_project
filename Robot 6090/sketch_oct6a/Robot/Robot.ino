const int sensor = A0; 
int sensor_value = 0; 
float voltage = 0; 

 

void setup() { 

  // put your setup code here, to run once: 

  //pinMode(data. INPUT); 

  Serial.begin (9600); 

} 

void objectMove(){
  moveMotor();
}

void objectHalt(int sensor_value){
  if(sensor_value <= 10){ // distance to stop from walls
    stopMotor();
  }
}

void loop() { 

  // put your main code here, to run repeatedly: 
  


  objectHalt(sensor_value);



} 
int x_axis = 0; // analog input 0 is x-axis
int y_axis = 1; //analog input 1 is y-axis

int x_pos;
int y_pos;
int pitch

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  x_pos = analogRead(x_axis);
  y_pos = analogRead(y_axis);
  //button_pressed = digitalRead(joystick_button);


  //sawtooth 
  if(x_pos > 730)
  {
    //sawtooth code
  }
  if(x_pos < 430)
  {
    //square wave code
  }
  if((x_pos > 440) && (x_pos < 620))
  {
    //sin wave code
  }

  Serial.print(x_pos);
  Serial.print(" ");
  Serial.print(y_pos);
  Serial.print(" ");
  Serial.println(button_pressed);
  delay(100);
}

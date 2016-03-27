//----Bumpers
  int ledPin = 13; // Arduino LED connected to digital pin 13
  int inPin = 7;   // input freq X360
  int changpin = 4;  
  int pinpulse = 6;  
  int pinLedRed = 3;
  int pinLedGreen = 5;
  int pinLedBlue = 9;
  int lightValueR;
  int lightValueG;
  int lightValueB;
  
  int val = 0;     // variable to store the read value
  
  long time_contactor=0;  
  int time_reset_bumper=300;  // reset bumper system after this timer
  int time_second_touch=150; // timer to prevent a second ghost touch
  int time_open_contactor=110; // timer to reset contactor ON state
  
  boolean go_bumper=false;
  int go_second=0;
  int nb_off=0;
  int nb_on=0;
  int old_val=0;
  int freq_bumper=25;  // number of count beforr a second touch
  boolean bypass=false;
  
void setup() {
    Serial.begin(115200);
    
    // Set the pins
    pinMode(ledPin, OUTPUT);      
    pinMode(inPin, INPUT);      
    pinMode(changpin, OUTPUT); 
    pinMode(pinpulse, OUTPUT); 
    pinMode(pinLedRed, OUTPUT);
    pinMode(pinLedGreen, OUTPUT);
    pinMode(pinLedBlue, OUTPUT);
    
    digitalWrite(changpin, 0); 

    // Write a test to the RGB logo 
    //analogWrite(pinLedRed, 128);
    //delay(500);
    //analogWrite(pinLedRed, 0);
    //analogWrite(pinLedGreen, 128);
    //delay(500);
    //analogWrite(pinLedGreen, 0);
    //analogWrite(pinLedBlue, 128);
    //delay(500);
    //analogWrite(pinLedBlue, 0);
    //analogWrite(pinLedGreen, 10);
    //analogWrite(pinLedRed, 128);
}

void loop() {
  bumpers();
  delay(4);
}

// Runs the feedback bumpers
void bumpers(){
  val = digitalRead(inPin);   // read the input pin
  if(val==0) go_bumper=true;
  if(go_bumper==true){
    nb_on+=1;
    if(nb_on==freq_bumper)nb_on=1;
  }
  if(val==1 && old_val==1) {
    nb_off+=1;
  }
  else{
    nb_off=0;
  }
  if(nb_off==5){
    nb_off=0;
    go_bumper=false;
    nb_on=0;
  }
  old_val=val;
    
  if(millis() - time_contactor > time_open_contactor ) digitalWrite(pinpulse, 0); // release contactor
  if(millis() - time_contactor > time_second_touch && go_second==1) go_second=2; 
  if(millis() - time_contactor > time_reset_bumper && go_second==2) go_second=0; 
  
  if((go_bumper==true && nb_on==1 && go_second!=1) || bypass==true){
      if(go_second==0) go_second=1;
      bypass=false;
      go_bumper=false; 
      digitalWrite(pinpulse, 0); //--contactor OFF
      time_contactor = millis();
      digitalWrite(changpin, 255); //---INC counter in 4017
      digitalWrite(changpin, 0);
      digitalWrite(pinpulse, 255); //--contactor ON
  }  
}

// Fires up when a serial connection is established
void serialEvent()
{
  while (Serial.available()) {    
      // Grab Data
      String serialString = Serial.readStringUntil('\n');

      int indexFirst = serialString.indexOf(',');
      int indexSecond = serialString.indexOf(',', indexFirst+1);
      lightValueR = serialString.substring(0, indexFirst).toInt();
      lightValueG = serialString.substring(indexFirst+1, indexSecond).toInt();
      lightValueB = serialString.substring(indexSecond+1).toInt();

      analogWrite(pinLedRed, lightValueR);
      analogWrite(pinLedGreen, lightValueG);
      analogWrite(pinLedBlue, lightValueB);


      // Send the buffer back to confirm reciept
      Serial.print("Buffer: ");
      Serial.println(serialString);
  }
}

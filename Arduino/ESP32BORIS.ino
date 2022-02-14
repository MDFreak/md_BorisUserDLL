const uint8_t DOUT1_PIN = 4;
const uint8_t DOUT2_PIN = 15;
const uint8_t AIN1_PIN = 32;
const uint8_t AIN2_PIN = 33;
const uint8_t DIN1_PIN = 34;
const uint8_t DIN2_PIN = 35;

void setup()
{
  pinMode(DOUT1_PIN, OUTPUT);
  pinMode(DOUT2_PIN, OUTPUT);
  pinMode(DIN1_PIN, INPUT);
  pinMode(DIN2_PIN, INPUT);
  pinMode(AIN1_PIN, INPUT);
  pinMode(AIN2_PIN, INPUT);
  Serial.begin(38400);
}

// Kommandos von BORIS:
//
// !Dxy   : Setze Digitalausgang x (x = 1,2) auf y (y = 0,1)
// !Axyyy : Setze Analogausgang x (x = 1,2) auf yyy (yyy = 000..255)
// ?Dx    : Liefere Wert von Digitaleingang x (x = 1,2), Rückgabewert vom Arduino: 0,1
// ?Ax    : Liefere Wert von Analogeingang x (x = 1,2), Rückgabewert vom Arduino: 0..4095

void loop()
  {
    while (Serial.available() && (Serial.peek() != '!') and (Serial.peek() != '?')) {Serial.read();}  // auf ! oder ? warten
    if (Serial.available() > 2)
    {
      char firstChar = (char)Serial.read();
      // Wert setzen
      if (firstChar == '!')
      {
        char varType = (char)Serial.read();
        char varIndex = (char)Serial.read();
        while (Serial.available() < 1) {};
        if (varType == 'D')
          {
            char varDValue = (char)Serial.read();
            if (varIndex == '1') 
            {
              if (varDValue == '0') {digitalWrite(DOUT1_PIN, LOW);} else {digitalWrite(DOUT1_PIN, HIGH);}
            }    
            if (varIndex == '2') 
            {
              if (varDValue == '0') {digitalWrite(DOUT2_PIN, LOW);} else {digitalWrite(DOUT2_PIN, HIGH);}
            }    
          }  
        if (varType == 'A')
          {
            String valueStringInt = "000";
            while (Serial.available() < 3) {};
            valueStringInt.setCharAt(0, (char)Serial.read());
            valueStringInt.setCharAt(1, (char)Serial.read());
            valueStringInt.setCharAt(2, (char)Serial.read());
            if (varIndex == '1') {dacWrite(DAC1, valueStringInt.toInt());}    
            if (varIndex == '2') {dacWrite(DAC2, valueStringInt.toInt());}    
          }  
        Serial.println("OK");
      }
      // Wert lesen
      if (firstChar == '?')
      {
        char varType = (char)Serial.read();
        char varIndex = (char)Serial.read();
        if (varType == 'A')
          {
            if (varIndex == '1') {Serial.println(analogRead(AIN1_PIN));}    
            if (varIndex == '2') {Serial.println(analogRead(AIN2_PIN));}    
          }  
        if (varType == 'D')
          {
            if (varIndex == '1') {Serial.println(digitalRead(DIN1_PIN));}  
            if (varIndex == '2') {Serial.println(digitalRead(DIN2_PIN));}  
          }
      }    
    }  
  }  



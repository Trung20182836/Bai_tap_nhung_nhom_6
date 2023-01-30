#include<LiquidCrystal.h>

LiquidCrystal lcd (1,2,4,5,6,7);

void setup()
{
  pinMode(9, OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(11, OUTPUT);
  
  TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS22);
  OCR2A = 255;
  
  lcd.begin(16,2);
  lcd.setCursor(5,0);
  lcd.print("WELCOME");
}

void loop()
{
  int K = analogRead(A1);
  int Steering = analogRead(A0);
  int Speed = analogRead(A2);
  int Old_Speed;
  
  lcd.setCursor(0,0);
  lcd.print("  NORMAL MODE   ");
  lcd.setCursor(0,1);
  lcd.print("SPEED");
  lcd.setCursor(7,1);
  lcd.print(OCR2A);
  

  if(OCR2A <= 99)
  {
    lcd.setCursor(9,1);
    lcd.print("      "); 
  }
  else
  {
    lcd.setCursor(11,1);
    lcd.print("        "); 
  }
  while(Old_Speed == analogRead(A2) && (K>450 && K<550))
  {
    K = analogRead(A1);
    lcd.setCursor(10,1);
    lcd.print("      "); 
  }
  
  if (Speed>=0 && Speed<200)
  {
    OCR2A = 50;
  }
  else if (Speed>200 && Speed<=400)
  {
    OCR2A = 100;
  }
  else if (Speed>400 && Speed<=600)
  {
    OCR2A = 150;
  }
    else if (Speed>600 && Speed<=800)
  {
    OCR2A = 200;
  }
    else if (Speed>800 && Speed<=1024)
  {
    OCR2A = 255;
  }
  int counter =0;
  while(K<450)
  {
    if(counter == 0)
    {
      Old_Speed = Speed;
      counter +=1;
    }
    
    Steering = analogRead(A0);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OVERSTEER DTCTED");
    lcd.setCursor(0,1);
    lcd.print("SPEED");
    lcd.setCursor(7,1);
    lcd.print(OCR2A);
    lcd.setCursor(11,1);
    lcd.print("BRKING");
    if (Steering<512)
    {
      digitalWrite(10, LOW);
      digitalWrite(9, HIGH);
    }
    if(Steering>=512)
    {
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
    }
    if(OCR2A>24)
    {
      OCR2A = OCR2A-25;
    }

    delay(200);
    K = analogRead(A1);
  }
  digitalWrite(10, LOW);
  digitalWrite(9, LOW);
  
  counter = 0;
  while(K>550)
  {
    if(counter == 0)
    {
      Old_Speed = Speed;
      counter +=1;
    }
    
    Steering = analogRead(A0);    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("UNDERSTER DTECTED");
    lcd.setCursor(0,1);
    lcd.print("SPEED");
    lcd.setCursor(7,1);
    lcd.print(OCR2A);
    lcd.setCursor(11,1);
    lcd.print("BRKING");
    if (Steering<512)
    {
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
    }
    if(Steering>=512)
    {
      digitalWrite(13, LOW);
      digitalWrite(12, HIGH);
    }
    if(OCR2A>24)
    {
      OCR2A = OCR2A-25;
    }

    delay(200);
   	K = analogRead(A1);
  }

  digitalWrite(13, LOW);
  digitalWrite(12, LOW);

}
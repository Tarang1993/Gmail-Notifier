#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
int outPin = 13; 
int mail = LOW;
 String email= "";
int val; 

void setup()
{
 pinMode(outPin, OUTPUT); 
 Serial.begin(9600);
 lcd.begin(16,2);
 pinMode(outPin,OUTPUT);
 mail = LOW; 
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0,0); 
 if (Serial.available())
 {
   lcd.print("connected");
   lcd.setCursor(0,1);
   val = Serial.read();
   Serial.println(val);
    
   if (val == 110) 
   {
     mail = LOW;
      lcd.clear();
   }

   else if (val !=110) //109 = m in dec
   {
     lcd.clear();
     email += val;
     mail=HIGH;
     getEmail();  
     printEmail();
   }
   
 }
 if(mail == HIGH){
       
 digitalWrite(outPin, mail);  
 
}
else{
      digitalWrite(outPin, LOW);
  }
  
}


void getEmail(){
    while(Serial.available()>0){
      char nextChar = Serial.read(); 
      email += nextChar;
    }
}


void printEmail(){
  int emailLength = email.length();
  lcd.setCursor(0,0);
  lcd.print(email);
  delay(500);
  for (int positionCounter = 0; positionCounter <emailLength-12; positionCounter++) {
    lcd.scrollDisplayLeft(); 
    delay(500);
  }
  lcd.clear();
  lcd.print(email);
  
}

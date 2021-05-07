#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
//temp sensor
const int tmpPin = A0;
//Motor Driver
int Enable = 13;
int inp3 = 8;
int inp4 = 9;  

void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  //temp sensor
  pinMode(tmpPin, INPUT);

  //Motor Driver
  pinMode(Enable, OUTPUT);
  pinMode(inp3, OUTPUT);
  pinMode(inp4, OUTPUT);
}

void loop() {
  //reading analog signal of temp sensor 
  int Temp = analogRead(tmpPin);
  temperature(Temp);
  delay(1000); 
}


//temperature related code
void temperature(int Temp){
  float voltage = Temp * 5.0; //converting reading to voltage
  voltage /= 1024.0; 
  float c = (voltage - .5) * 100; //conveting voltage to celsius
  float f = (c * 9 / 5 + 32); //converting calsius to farenheit 
  Serial.println(c);
  lcd.setCursor(0, 0);
  lcd.print("T=");
  lcd.setCursor(3, 0);
  lcd.print(c);
  lcd.setCursor(8, 0);
  lcd.print("C");
  lcd.setCursor(10, 0);
  lcd.print(f);
  lcd.setCursor(15, 0);
  lcd.print("F");
  
  //temp sensor and fan
  digitalWrite(inp3, LOW);  // To drive the fan in a direction
  digitalWrite(inp4, HIGH);
  lcd.setCursor(0, 1);
    
  if(c < 15) {                 // If the temperature less than 25
      analogWrite(Enable,0);	//Fann OFF
      lcd.print("it's too cold"); 
      delay(10);
    }
  	else if(c>=15 & c<20) {      // If the temperature is between 20 & 30
      analogWrite(Enable, 0);  // 50% of maximum cycle value (255). 
      lcd.print("Fan  OFF");
      delay(10);
    }
    else if(c>=20 & c<30) {      // If the temperature is between 20 & 30
      analogWrite(Enable, 128);  // 50% of maximum cycle value (255). 
      lcd.print("Fan: 50%");
      delay(10);
    }
    else if(c>=30 & c<35) {      // If the temperature is between 30 & 35
      analogWrite(Enable, 178);        // 70% of maximum cycle value (255).
      lcd.print("Fan: 70%");
      delay(10);
    }
  	else if(c>=35 & c<45) {      // If the temperature is between 35 & 40
      analogWrite(Enable, 216);        // 80% of maximum cycle value (255).
      lcd.print("Fan: 85%");
      delay(10);
    }
    else if(c>=45) {                // If the temperature is above 35
      analogWrite(Enable, 255);        // 100%
      lcd.print("Fan:100%");
      delay(10);
    }
}

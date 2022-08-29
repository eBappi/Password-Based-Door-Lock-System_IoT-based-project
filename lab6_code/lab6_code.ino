#include <LiquidCrystal.h>
#include <Servo.h>
#include <Keypad.h>
Servo myservo;
int irPin = 7;  
int LED = 10; 
int buzzerPin = 12;  

int sensorOut = LOW;  
int pos=0; 
LiquidCrystal lcd(A4, A5, A3, A2, A1, A0);
const byte rows=4;
const byte cols=3;
 
char key[rows][cols]={
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
byte rowPins[rows]={0,1,2,3};
byte colPins[cols]={4,5,6};
Keypad keypad= Keypad(makeKeymap(key),rowPins,colPins,rows,cols);
char* password="1122";
int currentposition=0;
 
 
 
void setup()
{
  pinMode(irPin, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
 
displayscreen();
//Serial.begin(9600);
myservo.attach(9); 
 
lcd.begin(16,2);
 
}
 
void loop()
{
if( currentposition==0)
{
displayscreen();
 
}
int l ;
char code=keypad.getKey();
if(code!=NO_KEY)
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("PASSWORD:");
lcd.setCursor(7,1);
lcd.print(" ");
lcd.setCursor(7,1);
for(l=0;l<=currentposition;++l)
{
 
lcd.print("*");

}
 
if (code==password[currentposition])
{
++currentposition;
if(currentposition==4)
{
 
unlockdoor();
currentposition=0;
 
}
 
}

 
else
{
incorrect();
currentposition=0;
 
}
}
}
 

 
void unlockdoor()
{
delay(900);
 
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(1,0);
lcd.print("Access Granted");
lcd.setCursor(4,1);
lcd.println("WELCOME!!");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(16,1);
lcd.println(" ");
lcd.setCursor(14,1);
lcd.println(" ");
lcd.setCursor(13,1);
lcd.println(" ");

for(pos = 180; pos>=0; pos-=5) 
{
myservo.write(pos); 
delay(5); 
}
delay(2000);
 
 
 
delay(1000);
counterbeep();
 
delay(1000);
 
for(pos = 0; pos <= 180; pos +=5) 
{ // in steps of 1 degree
myservo.write(pos); 
delay(15);
 
 
currentposition=0;
 
lcd.clear();
displayscreen();
 
}
}
 

 
void incorrect()
{
delay(500);
lcd.clear();
lcd.setCursor(1,0);
lcd.print("CODE");
lcd.setCursor(6,0);
lcd.print("INCORRECT");
lcd.setCursor(15,1);
lcd.println(" ");
lcd.setCursor(4,1);
lcd.println("GET AWAY!!!");
 
lcd.setCursor(13,1);
lcd.println(" ");
Serial.println("CODE INCORRECT YOU ARE UNAUTHORIZED");
delay(3000);
lcd.clear();
displayscreen();
}


void clearscreen()
{
lcd.setCursor(0,0);
lcd.println(" ");
lcd.setCursor(0,1);
lcd.println(" ");
lcd.setCursor(0,2);
lcd.println(" ");
lcd.setCursor(0,3);
lcd.println(" ");
}


void displayscreen() {

sensorOut = digitalRead(irPin);

  if (sensorOut == LOW)

  {

    Serial.println("No Object!");
  lcd.clear();
  lcd.print("No Object!");

    digitalWrite(LED, LOW);
    digitalWrite(buzzerPin, LOW);

  }

  else

  {

    Serial.println("Somebody there!");
    
  
  lcd.clear();
  lcd.print("Warning!");
  lcd.setCursor(0,1);
  lcd.print("Somebody there");
  
  
  
    digitalWrite(LED, HIGH);
    digitalWrite(buzzerPin, HIGH);

  }

  delay(200);
}


 

void counterbeep()
{
delay(1200);
 
 
lcd.clear();
 
lcd.setCursor(2,15);
lcd.println(" ");
lcd.setCursor(2,14);
lcd.println(" ");
lcd.setCursor(1,0);
delay(200);
lcd.println("CLOSE GET AFTER:::");
 
lcd.setCursor(4,1);
lcd.print("5");
delay(200);
lcd.clear();
lcd.setCursor(1,0);
lcd.println("CLOSE GET AFTER:");
delay(1000);
lcd.setCursor(1,0);
lcd.println("CLOSE GET AFTER:");
lcd.setCursor(4,1); 
lcd.print("4");
delay(100);
lcd.clear();
lcd.setCursor(1,0);
lcd.println("CLOSE GET AFTER:");
delay(1000);

lcd.setCursor(1,0);
lcd.println("CLOSE GET AFTER:");
lcd.setCursor(4,1); 
lcd.print("3");
delay(100);
lcd.clear();
lcd.setCursor(1,0);
lcd.println("CLOSE GET AFTER:");
delay(1000);

lcd.setCursor(1,0);
lcd.println("CLOSE GET AFTER:");
lcd.setCursor(4,1); 
lcd.print("2");
delay(100);
lcd.clear();
lcd.setCursor(1,0);
lcd.println("CLOSE GET AFTER:");
delay(1000);

lcd.setCursor(4,1);
lcd.print("1");
delay(100);
lcd.clear();
lcd.setCursor(1,0);
lcd.println("CLOSE GET:::");

delay(1000);
delay(40);
lcd.clear();
lcd.setCursor(2,0);
lcd.print("RE-LOCKING");
delay(500);
lcd.setCursor(12,0);
lcd.print(".");
delay(500);
lcd.setCursor(13,0);
lcd.print(".");
delay(500);
lcd.setCursor(14,0);
lcd.print(".");
delay(400);
lcd.clear();
lcd.setCursor(4,0);
lcd.print("LOCKED!");
delay(440);
}

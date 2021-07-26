#include <LiquidCrystal.h> //--> Includes the LiquidCrystal Library.

#define samp_siz 4
#define rise_threshold 5

int start = 7;
int count = 0;

byte customChar1[8] = {0b00000,0b00000,0b00011,0b00111,0b01111,0b01111,0b01111,0b01111};
byte customChar2[8] = {0b00000,0b11000,0b11100,0b11110,0b11111,0b11111,0b11111,0b11111};
byte customChar3[8] = {0b00000,0b00011,0b00111,0b01111,0b11111,0b11111,0b11111,0b11111};
byte customChar4[8] = {0b00000,0b10000,0b11000,0b11100,0b11110,0b11110,0b11110,0b11110};
byte customChar5[8] = {0b00111,0b00011,0b00001,0b00000,0b00000,0b00000,0b00000,0b00000};
byte customChar6[8] = {0b11111,0b11111,0b11111,0b11111,0b01111,0b00111,0b00011,0b00001};
byte customChar7[8] = {0b11111,0b11111,0b11111,0b11111,0b11110,0b11100,0b11000,0b10000};
byte customChar8[8] = {0b11100,0b11000,0b10000,0b00000,0b00000,0b00000,0b00000,0b00000};

// Variable declaration & Pulse monitor test script856
int sensorPin = 0; //--> Heart beat sendor PURPLE WIRE connected to the analog PIN 0.
int LED_3 = 3; //--> LED to detect when the heart is beating. LED is connected to PIN 3 on the arduino UNO

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //--> Initialize LiquidCrystal with "lcd".

int Signal; //--> Holds the incomming raw data. Signal value can range from 0-1024
int Threshold = 1003; //--> Determines which signal to "count as a beat", and which to ignore.

void setup() {
  lcd.begin(16, 2);
  //--> Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
  lcd.createChar(1, customChar1);
lcd.createChar(2, customChar2);
lcd.createChar(3, customChar3);
lcd.createChar(4, customChar4);
lcd.createChar(5, customChar5);
lcd.createChar(6, customChar6);
lcd.createChar(7, customChar7);
lcd.createChar(8, customChar8);
  //lcd.clear();
  pinMode(LED_3, OUTPUT); //--> set LED 3 PIN as output
  Serial.begin(9600); //--> sets up serial communication at certain speed.
  Serial.print("Group 6");
}
void loop ()
{
 
   lcd.setCursor(0, 0);
 lcd.print("Place The Finger");
 lcd.print("on the Sensor");
 lcd.setCursor(0, 1);
 lcd.print("");
 
  Signal = analogRead(sensorPin); //--> Read the Heartbeat Sensor's value. Assign this value to the "Signal" variable.
Serial.print("Threshold");
Serial.println(Signal);
  if(Signal > Threshold)
  {//--> If the signal is above "550"(Threshold), then "turn-on" Arduino's on-Board LED.
    digitalWrite(LED_3, HIGH);
  }
  else
  {digitalWrite(LED_3,LOW); //--> Else, the sigal must be below "550", so "turn-off" this LED.
   
  }
  
  float reads[samp_siz], sum;
  long int now, ptr;
  float last, reader, start;
  float first, second, third, before, print_value;
  bool rising;
  int rise_count;
  int n;  
  long int last_beat;
  if(Signal>Threshold){

   lcd.clear();
//   temp=millis();
   
  for (int i = 0; i < samp_siz; i++)
    reads[i] = 0;
  sum = 0;
  ptr = 0;
  while(1)
  {
    n = 0;
    start = millis();
    reader = 0.;
    do
    {
      reader += analogRead (sensorPin);
      n++;
      now = millis();
    }
    while (now < start + 20);
    reader /= n; 
    sum -= reads[ptr];
    sum += reader;
    reads[ptr] = reader;
    last = sum / samp_siz;
    if (last > before)
    {
      rise_count++;
      if (!rising && rise_count > rise_threshold)
      {rising = true;
      first = millis() - last_beat;
      last_beat = millis();
      print_value = 60000. / (0.4 * first + 0.3 * second + 0.3 * third);
//      Serial.print(print_value);
      Serial.print('\n');
//    lcd.setCursor(0,0);
//    lcd.print("H. Monitor by Group 6");
//      lcd.setCursor(0,1);
//      lcd.print("BM ");

         lcd.clear();
         lcd.setCursor(0, 0);
//         count=count*6;
         lcd.setCursor(2, 0);
         lcd.write(byte(1));
         lcd.setCursor(3, 0);
         lcd.write(byte(2));
         lcd.setCursor(4, 0);
         lcd.write(byte(3));
         lcd.setCursor(5, 0);
         lcd.write(byte(4));

         lcd.setCursor(2, 1);
         lcd.write(byte(5));
         lcd.setCursor(3, 1);
         lcd.write(byte(6));
         lcd.setCursor(4, 1);
         lcd.write(byte(7));
         lcd.setCursor(5, 1);
         lcd.write(byte(8));
         lcd.setCursor(7, 1);    
      Serial.print("Output ");
      Serial.println(print_value);
      
      lcd.print(print_value);
      lcd.print(" BPM");
//      if(Signal>Threshold){
//
//   lcd.clear();
//      }
      third = second;
      second = first;
   // delay(2000);
    }
   }
   else
   {
    rising = false;
    rise_count = 0;
//   lcd.clear();
   }
   before = last;
   ptr++;
   ptr%= samp_siz;
  }
  }
}

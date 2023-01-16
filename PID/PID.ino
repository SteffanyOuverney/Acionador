/********************************************************
 * PID Basic Example
 * Reading analog input 0 to control analog PWM output 3
 ********************************************************/

#include <PID_v1.h>

#define PIN_INPUT 14
#define PIN_OUTPUT 8

#define RT0 100000   // Ω
#define B 3950      // K
//--------------------------------------

#define resist 8

#define VCC 5    //Supply voltage
#define R 4700  //R=10KΩ

//Variables
float RT, VR, ln, TX, T0, VRT;
//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
double Kp=19.56, Ki=1, Kd=147;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup()
{
  Serial.begin(9600);
  T0 = 20 + 273.15;                 //Temperature T0 from datasheet, conversion from Celsius to kelvin
  //initialize the variables we're linked to
  Input = TX;
  Setpoint = 100;

  //turn the PID on
  myPID.SetMode(AUTOMATIC);
}

void loop()
{
  
  VRT = analogRead(A14);              //Acquisition analog value of VRT
  VRT = (5.00 / 1023.00) * VRT;      //Conversion to voltage
  VR = VCC - VRT;
  RT = VRT / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor

  TX = TX - 273.15;                 //Conversion to Celsius

  //Serial.print("Temperature:");
  //Serial.print("\t");
  Serial.println(TX);
 // Serial.println("C\t\t");
 // Serial.print(TX + 273.15);        //Conversion to Kelvin
 // Serial.print("K\t\t");
  //Serial.print((TX * 1.8) + 32);    //Conversion to Fahrenheit
  //Serial.println("F");
  delay(100);
  
  Input = TX;
  myPID.Compute();
  analogWrite(PIN_OUTPUT, Output);
}

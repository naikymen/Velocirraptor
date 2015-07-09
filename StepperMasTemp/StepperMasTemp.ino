#include <Time.h>
#include <Stepper.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int stepsPerRevolution = 200;
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int stepCount = 0;
const int stepsbetweentemp = 100;

unsigned long miliahora = millis();
unsigned long miliultima = 60000;
int intervalo = 60000;

#define ONE_WIRE_BUS 3
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(5,OUTPUT);
}

float checktemp() {
  sensors.requestTemperatures();
  return(sensors.getTempCByIndex(0));
}

void loop() {
  //Dar un paso
  myStepper.step(1);
  delay(150);
  
  // Medir la temperatura
  if(miliahora - miliultima >= intervalo) {
    temperatura = checktemp();
    miliahora = millis();
    
    if(temperatura => 28.5){
      digitalWrite(5,LOW);  //Prender los ventiladores
    } else {
      if(temperatura <= 28){
        digitalWrite(5,HIGH); //Apagar los ventiladores
      }
    }
  } else {
    myStepper.step(1);  //Dar un paso
    delay(150);  //Separar los pasos por un delay
  }
  
  
  
}


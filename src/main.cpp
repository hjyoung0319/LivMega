#include <Arduino.h>
#include "Control_LIB/control.h"
#include "Water_LIB/EC_Sensor.h"


#define PUMP_RELAY_PIN            A0   //      12 V
#define LED_RELAY_PIN             A1   //     220 V 
#define AIRCON_RELAY_PIN          A2   //     220 V
#define NUTRIENT_RELAY_PIN        A3   //      12 V
#define A4_RELAY_PIN              A4   // Undefined
#define A5_RELAY_PIN              A5   // Undefined
#define A6_RELAY_PIN              A6   // Undefined
#define A7_RELAY_PIN              A7   // Undefined



#define EC_TX_PIN                 13
#define EC_RX_PIN                 12
#define PH_TX_PIN                 11
#define PH_RX_PIN                 10
#define WATER_TEMP_PIN             9   
#define WATER_HIGH_PIN             8   
#define WATER_LOW_PIN              7 

#define CO2_TX_PIN                 6
#define CO2_RX_PIN                 5
/*Temp,Humid and Lux sensors are I2C Communicate*/

// Timing
unsigned long currentMillis;                    // Snapshot of current time
unsigned long controlECStartMillis;             // Timer to check EC
unsigned long controlAirconStartMillis;         // Timer to check temperature
const unsigned long controlECPeriod = 1000;      // Time in milliseconds between checking nute res water level
const unsigned long controlAirconPeriod = 10000;        // Time between checking floor moisture sensors for flood
unsigned long wifiWaitPeriod = 5000;                    // Time to wait for sensor data after I2C_call function

ECSensor ecSensor;
Control pump, led, aircon, nutrient, a4, a5 ,a6, a7;



void setup() {
  // put your setup code here, to run once:
  ecSensor.set_ECSensor(EC_RX_PIN,EC_TX_PIN);
  ecSensor.begin();
  
  Serial.begin(9600);
  Serial1.begin(115200); // Communicate with esp32 WROOM


}

void loop() {
  // put your main code here, to run repeatedly:

  if (currentMillis - drainBasinMillis >= drainBasinPeriod)
  {
    checkDrainBasin();
  }

  if (currentMillis - waterLvlMillis >= waterLvlPeriod)
  {
    checkWaterLvl();
  }
}
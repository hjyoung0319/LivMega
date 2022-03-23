#include <Arduino.h>
#include <SoftwareSerial.h>

class pHSensor
{
private:
    int rx, tx;

public:
    void set_PHSensor(int rxInput, int txInput) { rx = rxInput, tx = txInput; }
    SoftwareSerial myserial = SoftwareSerial(rx, tx);
    String inputstring = "";             // a string to hold incoming data from the PC
    String sensorstring = "";            // a string to hold the data from the Atlas Scientific product
    bool input_string_complete = false;  // have we received all the data from the PC
    bool sensor_string_complete = false; // have we received all the data from the Atlas Scientific product
    float PH;

    void begin()
    {
        myserial.begin(9600);     // set baud rate for the software serial port to 9600
        inputstring.reserve(10);  // set aside some bytes for receiving data from the PC
        sensorstring.reserve(30); // set aside some bytes for receiving data from Atlas Scientific product
        // /* set PH calibration Export */
        // Serial.println("EC EXPORT START");
        // myserial.println("CAL,DRY");
        // myserial.println("EXPORT");
  
        // myserial.println("EXPORT EB");
    }

    float getPH()
    {
        myserial.listen();
        float pHValue = -1;
        unsigned long currentMillis = millis();

        while (!sensor_string_complete)
        {
            if (millis() > currentMillis + 1000) // if Data Requset fail in 1 sec, Stop and Return -1;
            {
                return pHValue;
            }
            if (myserial.available() > 0)
            {                                                       // if we see that the Atlas Scientific product has sent a character
                String sensorstring = myserial.readStringUntil(13); // get the char we just received
                char pHchar[strlen(sensorstring.c_str())];
                strcpy(pHchar, sensorstring.c_str());
                pHValue = atof(pHchar);
                sensor_string_complete = true;
            }

            return pHValue;
        }
    }
};

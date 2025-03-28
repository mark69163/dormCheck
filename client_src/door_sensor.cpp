#include "door_sensor.h"
#include "settings.h"

void init_door_sensor(){
  pinMode(DOOR_SENS_PIN,INPUT);
}

bool read_door_sensor() {
    static int sensorState;           
    static int lastSensorState = HIGH;  
    const unsigned long debounceTime = 50;
    static unsigned long lastDebounceTime = 0;

    int reading = digitalRead(DOOR_SENS_PIN);  // Read current state of the sensor

    if (reading != lastSensorState) {  
        lastDebounceTime = millis();  // Reset debounce timer if state changed
    }

    if ((millis() - lastDebounceTime) > debounceTime) {  
        if (reading != sensorState) {  
            sensorState = reading;
            if(sensorState==0) return true;  
        }
    }

    lastSensorState = reading;  
    return false;
}



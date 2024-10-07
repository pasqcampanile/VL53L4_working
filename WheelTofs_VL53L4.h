#ifndef WHEELTOFS_VL53L4_H_
#define WHEELTOFS_VL53L4_H_

#include "mbed.h"
#include <cstdint>
#include <VL53L1X.h>

//TOFs
#define TOF_1_XSHUT PA_7 //T1   
#define TOF_2_XSHUT PA_6 //T2
#define TOF_3_XSHUT PA_4 //T3
#define TOF_4_XSHUT PA_3 //T4
#define TOF_5_XSHUT PA_5 //T5   
#define TOF_6_XSHUT PA_1 //T6

#define range1_addr (0x11) //T1  
//#define range2_addr (0x12) //T2
//#define range3_addr (0x13) //T3
//#define range4_addr (0x14) //T4
//#define range5_addr (0x15) //T5  
//#define range6_addr (0x16) //T6

#define TOF_INIT_WAIT 300
#define TIMEOUT_MS 500
#define CONTINOUS_TIME_MS 50

class WheelTofs {

private:
    I2C &i2cTof;  
    Timer timer[6];  
    DigitalInOut xshout[6];  
    VL53L1X VL53L4[6];  

public:
    WheelTofs(I2C &i2c) :
    i2cTof(i2c),
    xshout { DigitalInOut(TOF_1_XSHUT,PIN_OUTPUT,OpenDrainNoPull,0), DigitalInOut(TOF_2_XSHUT,PIN_OUTPUT,OpenDrainNoPull,0), 
            DigitalInOut(TOF_3_XSHUT,PIN_OUTPUT,OpenDrainNoPull,0), DigitalInOut(TOF_4_XSHUT,PIN_OUTPUT,OpenDrainNoPull,0), 
            DigitalInOut(TOF_5_XSHUT,PIN_OUTPUT,OpenDrainNoPull,0), DigitalInOut(TOF_6_XSHUT,PIN_OUTPUT,OpenDrainNoPull,0)},
    VL53L4 { VL53L1X(&i2c, &timer[0]), VL53L1X(&i2c, &timer[1]), 
            VL53L1X(&i2c, &timer[2]), VL53L1X(&i2c, &timer[3]), 
            VL53L1X(&i2c, &timer[4]), VL53L1X(&i2c, &timer[5])}
    {

    }

    void init_tofs() {
        for (int i = 0; i < 6; i++) 
            xshout[i] = 0;

        for (int i = 0; i < 6; i++) {
            xshout[i] = 1;  

            if (!VL53L4[i].init()) 
                printf("Errore sensore %d!\n", i);
            else{
                ThisThread::sleep_for(500ms);
                if (i < 4) 
                    VL53L4[i].setDistanceMode(VL53L1X::Short);  
                else 
                    VL53L4[i].setDistanceMode(VL53L1X::Long);  

                VL53L4[i].setMeasurementTimingBudget(50000);  
                VL53L4[i].setAddress(range1_addr + i); 
                VL53L4[i].setTimeout(TIMEOUT_MS);
                VL53L4[i].startContinuous(CONTINOUS_TIME_MS);  
                printf("Sensore %d settato correttamente su indirizzo %x.\n\n------------------\n", i, 0x11 + i);
            }
        }
        ThisThread::sleep_for(2s);
    }

    void pollSensors(int16_t* dist) {
        for (int i = 0; i < 6; i++) {
            dist[i] = VL53L4[i].read(false);
        }
    }

    void printDistDebug() {
        for (int i = 0; i < 6; i++) {
            uint16_t distanza = VL53L4[i].read();
            printf("\033[32mDistanza %d: \e[1;37m%d mm\n", i, distanza);
        }
        ThisThread::sleep_for(200ms);        
        printf("\033[2J");  
        printf("\033[H");
         
    }
};

#endif //WHEELTOFS_VL53L4_H
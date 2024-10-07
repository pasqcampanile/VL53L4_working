#include "mbed.h"
#include <cstdint>
#include "WheelTofs_VL53L4.h"


#define TIMEOUT_MS 500
#define CONTINOUS_TIME_MS 50

// Pin definiti per la tua configurazione
I2C i2c(PB_4, PA_7); // SDA, SCL
DigitalOut led(LED1);

WheelTofs Tofs(i2c);
int16_t dist[6] = {0};


int main(){
    Tofs.init_tofs();
    while (1) {
        Tofs.printDistDebug();
           
    }
}

/*
int main() {
    for (int i = 0; i < 6; i++) 
        xshout[i] = 0;
    
    uint8_t address_start = 0x11;
    uint8_t address_new = 0;

    printf("Inizializzazione sensori...\n");

    for (int i = 0; i < 6; i++) {
        xshout[i] = 1;

        if (!VL53L4[i].init()) 
        printf("Errore nell'inizializzazione del sensore %d!\n", i);
        
        else printf("Sensore %d inizializzato correttamente.\n", i);
        ThisThread::sleep_for(500ms);
        if (i < 4) 
            VL53L4[i].setDistanceMode(VL53L1X::Short);  // Modalità lunga distanza
        else VL53L4[i].setDistanceMode(VL53L1X::Long);  // Modalità lunga distanza
        VL53L4[i].setMeasurementTimingBudget(50000); // 50ms di budget temporale
        address_new = (0x11 + i);
        VL53L4[i].setAddress(address_new);
        VL53L4[i].setTimeout(TIMEOUT_MS);
        VL53L4[i].startContinuous(CONTINOUS_TIME_MS);  // Misura ogni 50ms
        printf("Sensore %d settato correttamente su indirizzo %x.\n\n------------------\n", i, address_new);
    }

    while (1) {
        uint16_t distanza = VL53L4[0].read();
        printf("Distanza misurata 0: %d mm", distanza);
        distanza = VL53L4[1].read();
        printf("\t\tDistanza misurata 1: %d mm\n", distanza);
        
        ThisThread::sleep_for(500ms);
    }
}*/
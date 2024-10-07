#pragma once

#include "mbed.h"

class VL6180x
{

public:
    struct Identification {
        char model;
        char modelRevMajor;
        char modelRevMinor;
        char moduleRevMajor;
        char moduleRevMinor;
        int date;
        int time;
    };

    VL6180x(PinName sda, PinName scl, char _address = 0xE0);
    VL6180x(I2C* i2c, char address = 0xE0 );
    void initialize();

    int getDistance();
    int getSingleDistance();
    float getAmbientLight();
    Identification getIdentification();
    static void printIdentification(Identification id);
    void startContinuousOperation();
    
    void setRegister(int register, int value);
    int getRegister(int reg);

    void setAddress(uint8_t address);

protected:
    int address;
    I2C* i2c;
    
    static const int I2C_SLAVE_DEFAULT_ADDRESS = 0x52;
    
    static const int IDENTIFICATION_MODEL_ID = 0x000;
    static const int IDENTIFICATION_MODEL_REV_MAJOR = 0x001;
    static const int IDENTIFICATION_MODEL_REV_MINOR = 0x002;
    static const int IDENTIFICATION_MODULE_REV_MAJOR = 0x003;
    static const int IDENTIFICATION_MODULE_REV_MINOR = 0x004;
    static const int IDENTIFICATION_DATE_HI = 0x006;
    static const int IDENTIFICATION_DATE_LO = 0x007;
    static const int IDENTIFICATION_TIME = 0x008;
    static const int SYSTEM_MODE_GPIO0 = 0x010;
    static const int SYSTEM_MODE_GPIO1 = 0x011;
    static const int SYSTEM_HISTORY_CTRL = 0x012;
    static const int SYSTEM_INTERRUPT_CONFIG_GPIO = 0x014;
    static const int SYSTEM_INTERRUPT_CLEAR = 0x015;
    static const int SYSTEM_FRESH_OUT_OF_RESET = 0x016;
    static const int SYSTEM_GROUPED_PARAMETER_HOLD = 0x017;
    static const int SYSRANGE_START = 0x018;
    static const int SYSRANGE_THRESH_HIGH = 0x019;
    static const int SYSRANGE_THRESH_LOW = 0x01A;
    static const int SYSRANGE_INTERMEASUREMENT_PERIOD = 0x01B;
    static const int SYSRANGE_MAX_CONVERGENCE_TIME = 0x01C;
    static const int SYSRANGE_CROSSTALK_COMPENSATION_RATE = 0x01E;
    static const int SYSRANGE_CROSSTALK_VALID_HEIGHT = 0x021;
    static const int SYSRANGE_EARLY_CONVERGENCE_ESTIMATE = 0x022;
    static const int SYSRANGE_PART_TO_PART_RANGE_OFFSET = 0x024;
    static const int SYSRANGE_RANGE_IGNORE_VALID_HEIGHT = 0x025;
    static const int SYSRANGE_RANGE_IGNORE_THRESHOLD = 0x026;
    static const int SYSRANGE_MAX_AMBIENT_LEVEL_MULT = 0x02C;
    static const int SYSRANGE_RANGE_CHECK_ENABLES = 0x02D;
    static const int SYSRANGE_VHV_RECALIBRATE = 0x02E;
    static const int SYSRANGE_VHV_REPEAT_RATE = 0x031;
    static const int SYSALS_START = 0x038;
    static const int SYSALS_THRESH_HIGH = 0x03A;
    static const int SYSALS_THRESH_LOW = 0x03C;
    static const int SYSALS_INTERMEASUREMENT_PERIOD = 0x03E;
    static const int SYSALS_ANALOGUE_GAIN = 0x03F;
    static const int SYSALS_INTEGRATION_PERIOD = 0x040;
    static const int RESULT_RANGE_STATUS = 0x04D;
    static const int RESULT_ALS_STATUS = 0x04E;
    static const int RESULT_INTERRUPT_STATUS_GPIO = 0x04F;
    static const int RESULT_ALS_VAL = 0x050;
    static const int RESULT_HISTORY_BUFFER_0 = 0x052;
    static const int RESULT_HISTORY_BUFFER_1 = 0x054;
    static const int RESULT_HISTORY_BUFFER_2 = 0x056;
    static const int RESULT_HISTORY_BUFFER_3 = 0x058;
    static const int RESULT_HISTORY_BUFFER_4 = 0x05A;
    static const int RESULT_HISTORY_BUFFER_5 = 0x05C;
    static const int RESULT_HISTORY_BUFFER_6 = 0x05E;
    static const int RESULT_HISTORY_BUFFER_7 = 0x060;
    static const int RESULT_RANGE_VAL = 0x062;
    static const int RESULT_RANGE_RAW = 0x064;
    static const int RESULT_RANGE_RETURN_RATE = 0x066;
    static const int RESULT_RANGE_REFERENCE_RATE = 0x068;
    static const int RESULT_RANGE_RETURN_SIGNAL_COUNT = 0x06C;
    static const int RESULT_RANGE_REFERENCE_SIGNAL_COUNT = 0x070;
    static const int RESULT_RANGE_RETURN_AMB_COUNT = 0x074;
    static const int RESULT_RANGE_REFERENCE_AMB_COUNT = 0x078;
    static const int RESULT_RANGE_RETURN_CONV_TIME = 0x07C;
    static const int RESULT_RANGE_REFERENCE_CONV_TIME = 0x080;
    static const int READOUT_AVERAGING_SAMPLE_PERIOD = 0x10A;
    static const int FIRMWARE_BOOTUP = 0x119;
    static const int FIRMWARE_RESULT_SCALER = 0x120;
    static const int I2C_SLAVE_DEVICE_ADDRESS = 0x212;
    static const int INTERLEAVED_MODE_ENABLE = 0x2A3;
};
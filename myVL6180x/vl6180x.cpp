#include "vl6180x.h"
#include "mbed.h"

VL6180x::VL6180x(I2C* _i2c, char _address): i2c(_i2c), address(_address)
{
    address = I2C_SLAVE_DEFAULT_ADDRESS;
}
/*
VL6180x::VL6180x(PinName sda, PinName scl, char _address): i2c(&i2c(sda, scl)), address(_address)
{
    i2c.frequency(400000);   
    address = I2C_SLAVE_DEFAULT_ADDRESS;
}
*/

void VL6180x::initialize()
{

    // Mandatory : private registers
    setRegister(0x0207, 0x01);
    setRegister(0x0208, 0x01);
    setRegister(0x0096, 0x00);
    setRegister(0x0097, 0xfd);
    setRegister(0x00e3, 0x00);
    setRegister(0x00e4, 0x04);
    setRegister(0x00e5, 0x02);
    setRegister(0x00e6, 0x01);
    setRegister(0x00e7, 0x03);
    setRegister(0x00f5, 0x02);
    setRegister(0x00d9, 0x05);
    setRegister(0x00db, 0xce);
    setRegister(0x00dc, 0x03);
    setRegister(0x00dd, 0xf8);
    setRegister(0x009f, 0x00);
    setRegister(0x00a3, 0x3c);
    setRegister(0x00b7, 0x00);
    setRegister(0x00bb, 0x3c);
    setRegister(0x00b2, 0x09);
    setRegister(0x00ca, 0x09);
    setRegister(0x0198, 0x01);
    setRegister(0x01b0, 0x17);
    setRegister(0x01ad, 0x00);
    setRegister(0x00ff, 0x05);
    setRegister(0x0100, 0x05);
    setRegister(0x0199, 0x05);
    setRegister(0x01a6, 0x1b);
    setRegister(0x01ac, 0x3e);
    setRegister(0x01a7, 0x1f);
    setRegister(0x0030, 0x00);

// Recommended : Public registers - See data sheet for more detail
    setRegister(SYSTEM_MODE_GPIO1, 0x10); // Enables polling for ‘New Sample ready’
// when measurement completes
    setRegister(READOUT_AVERAGING_SAMPLE_PERIOD, 0x30); // Set the averaging sample period
// (compromise between lower noise and
// increased execution time)
    setRegister(SYSALS_ANALOGUE_GAIN, 0x46); // Sets the light and dark gain (upper
// nibble). Dark gain should not be
// changed.
    setRegister(SYSRANGE_VHV_REPEAT_RATE, 0xFF); // sets the # of range measurements after
// which auto calibration of system is
// performed
    setRegister(SYSALS_INTEGRATION_PERIOD, 0x63); // Set ALS integration time to 100ms
    setRegister(SYSRANGE_VHV_RECALIBRATE, 0x01); // perform a single temperature calibration
// of the ranging sensor


    setRegister(SYSRANGE_INTERMEASUREMENT_PERIOD, 0x09); // Set default ranging inter-measurement
// period to 100ms
    setRegister(SYSALS_INTERMEASUREMENT_PERIOD, 0x31); // Set default ALS inter-measurement period
// to 500ms
    setRegister(SYSTEM_INTERRUPT_CONFIG_GPIO, 0x24); // Configures interrupt on ‘New Sample
// Ready threshold event’
}

void VL6180x::startContinuousOperation()
{
    setRegister(SYSRANGE_START, 0x03);
    
}

int VL6180x::getDistance()
{
    int distance = 0;
    // should test bit 2  of RESULT_INTERRUPT_STATUS_GPIO ?
    distance = getRegister(RESULT_RANGE_VAL);
    // should clear interrupt ?
    return distance;   
}

int VL6180x::getSingleDistance()
{
    int distance = 0;
    while(getRegister(RESULT_RANGE_STATUS) & 0x01 != 0x01);
    setRegister(SYSRANGE_START, 0x01); // start measurement
    while(getRegister(RESULT_INTERRUPT_STATUS_GPIO) & 0x04 != 0x04);
    distance = getRegister(RESULT_RANGE_VAL);
    setRegister(SYSTEM_INTERRUPT_CLEAR, 0x07);
    return distance;
}

float VL6180x::getAmbientLight()
{
    return 0.0f;
}

void VL6180x::setRegister(int reg, int value)
{
    char data_write[3];
    data_write[0] = ((reg &0xff00 ) >> 8);
    data_write[1] = (reg &0x00ff );
    data_write[2] = value;
    i2c->write(address, data_write, 3);
}

int VL6180x::getRegister(int reg)
{
    char data_write[2];
    char data_read[1];
    data_write[0] = ((reg &0xff00 ) >> 8);
    data_write[1] = (reg &0x00ff ) ;

    i2c->write(address, data_write, 2, 1); //no stop
    i2c->read(address, data_read, 1, 0);

    return data_read[0];
}

VL6180x::Identification VL6180x::getIdentification()
{

    char data_write[2];
    char data_read[10];
    data_write[0] = ( (0x00 &0xff00 ) >> 8);
    data_write[1] = (0x00 &0x00ff ) ;

    i2c->write(address, data_write, 2, 1); //no stop
    i2c->read(address, data_read, 10, 0);

    Identification id;
    id.model = data_read[0];
    id.modelRevMajor = data_read[1];
    id.modelRevMinor = data_read[2];
    id.moduleRevMajor = data_read[3];
    id.moduleRevMinor = data_read[4];
    id.date = data_read[6] << 8 | data_read[7];
    id.time = data_read[8] << 8 | data_read[9];
    return id;
}

void VL6180x::printIdentification(VL6180x::Identification id)
{
    printf("VL6180x Identification:\r\n");
    printf("Model id:   0x%02X\r\n", id.model);
    printf("Model rev:  %d.%d\r\n", id.modelRevMajor, id.modelRevMinor);
    printf("Module rev: %d.%d\r\n", id.moduleRevMajor, id.modelRevMajor);
    printf("Date:       %04d-%02d-%02d (%d)\r\n", ((id.date >> 12) & 0x0F) + 2010, (id.date >> 8) & 0x0F, (id.date >> 3) & 0x1F, id.date & 0x07);
    printf("Time:       %02d:%02d:%02d\r\n", (id.time / 60*60) % 24, (id.time / 60) % 60, id.time % 60);
}

void VL6180x::setAddress(uint8_t _address)
{
    char data[3];
    data[0] = I2C_SLAVE_DEVICE_ADDRESS / 256;
    data[1] = I2C_SLAVE_DEVICE_ADDRESS % 256;
    data[2] = _address & 0x7F;//>> 1;
    i2c->write(address, data, 3); //no stop
    address = _address<<1;
}
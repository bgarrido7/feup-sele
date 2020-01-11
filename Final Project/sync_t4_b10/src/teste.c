#define TSL2561_VISIBLE 2                   ///< channel 0 - channel 1
#define TSL2561_INFRARED 1                  ///< channel 1
#define TSL2561_FULLSPECTRUM 0              ///< channel 0


#ifndef F_CPU
    #define F_CPU           16000000ul //16MHz
#endif

#define I2C_WRITE           0
#define I2C_READ            1

#define MASK_MODE           0b1
#define MASK_ADDRESS        0x7F   
#define MASK_STATUS_CODE    0xF8    
#define MASK_LENGHT_DATA    0xFF

# define Prescaler          1
# define F_SCL              100000 //100kHz

// I2C address options
#define TSL2561_ADDR_LOW          (0x29)    ///< Default address (pin pulled low)
#define TSL2561_ADDRESS        (0x39)    ///< Default address (pin left floating)
#define TSL2561_ADDR_HIGH         (0x49)    ///< Default address (pin pulled high)

// Lux calculations differ slightly for CS package
//#define TSL2561_PACKAGE_CS                ///< Chip scale package     
#define TSL2561_PACKAGE_T_FN_CL             ///< Dual Flat No-Lead package

#define TSL2561_COMMAND_BIT       (0x80)    ///< Must be 1
#define TSL2561_CLEAR_BIT         (0x40)    ///< Clears any pending interrupt (write 1 to clear)
#define TSL2561_WORD_BIT          (0x20)    ///< 1 = read/write word (rather than byte)
#define TSL2561_BLOCK_BIT         (0x10)    ///< 1 = using block read/write

#define TSL2561_CONTROL_POWERON   (0x03)    ///< Control register setting to turn on
#define TSL2561_CONTROL_POWEROFF  (0x00)    ///< Control register setting to turn off

#define TSL2561_LUX_LUXSCALE      (14)      ///< Scale by 2^14
#define TSL2561_LUX_RATIOSCALE    (9)       ///< Scale ratio by 2^9
#define TSL2561_LUX_CHSCALE       (10)      ///< Scale channel values by 2^10
#define TSL2561_LUX_CHSCALE_TINT0 (0x7517)  ///< 322/11 * 2^TSL2561_LUX_CHSCALE
#define TSL2561_LUX_CHSCALE_TINT1 (0x0FE7)  ///< 322/81 * 2^TSL2561_LUX_CHSCALE

// T, FN and CL package values
#define TSL2561_LUX_K1T           (0x0040)  ///< 0.125 * 2^RATIO_SCALE
#define TSL2561_LUX_B1T           (0x01f2)  ///< 0.0304 * 2^LUX_SCALE
#define TSL2561_LUX_M1T           (0x01be)  ///< 0.0272 * 2^LUX_SCALE
#define TSL2561_LUX_K2T           (0x0080)  ///< 0.250 * 2^RATIO_SCALE
#define TSL2561_LUX_B2T           (0x0214)  ///< 0.0325 * 2^LUX_SCALE
#define TSL2561_LUX_M2T           (0x02d1)  ///< 0.0440 * 2^LUX_SCALE
#define TSL2561_LUX_K3T           (0x00c0)  ///< 0.375 * 2^RATIO_SCALE
#define TSL2561_LUX_B3T           (0x023f)  ///< 0.0351 * 2^LUX_SCALE
#define TSL2561_LUX_M3T           (0x037b)  ///< 0.0544 * 2^LUX_SCALE
#define TSL2561_LUX_K4T           (0x0100)  ///< 0.50 * 2^RATIO_SCALE
#define TSL2561_LUX_B4T           (0x0270)  ///< 0.0381 * 2^LUX_SCALE
#define TSL2561_LUX_M4T           (0x03fe)  ///< 0.0624 * 2^LUX_SCALE
#define TSL2561_LUX_K5T           (0x0138)  ///< 0.61 * 2^RATIO_SCALE
#define TSL2561_LUX_B5T           (0x016f)  ///< 0.0224 * 2^LUX_SCALE
#define TSL2561_LUX_M5T           (0x01fc)  ///< 0.0310 * 2^LUX_SCALE
#define TSL2561_LUX_K6T           (0x019a)  ///< 0.80 * 2^RATIO_SCALE
#define TSL2561_LUX_B6T           (0x00d2)  ///< 0.0128 * 2^LUX_SCALE
#define TSL2561_LUX_M6T           (0x00fb)  ///< 0.0153 * 2^LUX_SCALE
#define TSL2561_LUX_K7T           (0x029a)  ///< 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B7T           (0x0018)  ///< 0.00146 * 2^LUX_SCALE
#define TSL2561_LUX_M7T           (0x0012)  ///< 0.00112 * 2^LUX_SCALE
#define TSL2561_LUX_K8T           (0x029a)  ///< 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B8T           (0x0000)  ///< 0.000 * 2^LUX_SCALE
#define TSL2561_LUX_M8T           (0x0000)  ///< 0.000 * 2^LUX_SCALE

// CS package values
#define TSL2561_LUX_K1C           (0x0043)  ///< 0.130 * 2^RATIO_SCALE
#define TSL2561_LUX_B1C           (0x0204)  ///< 0.0315 * 2^LUX_SCALE
#define TSL2561_LUX_M1C           (0x01ad)  ///< 0.0262 * 2^LUX_SCALE
#define TSL2561_LUX_K2C           (0x0085)  ///< 0.260 * 2^RATIO_SCALE
#define TSL2561_LUX_B2C           (0x0228)  ///< 0.0337 * 2^LUX_SCALE
#define TSL2561_LUX_M2C           (0x02c1)  ///< 0.0430 * 2^LUX_SCALE
#define TSL2561_LUX_K3C           (0x00c8)  ///< 0.390 * 2^RATIO_SCALE
#define TSL2561_LUX_B3C           (0x0253)  ///< 0.0363 * 2^LUX_SCALE
#define TSL2561_LUX_M3C           (0x0363)  ///< 0.0529 * 2^LUX_SCALE
#define TSL2561_LUX_K4C           (0x010a)  ///< 0.520 * 2^RATIO_SCALE
#define TSL2561_LUX_B4C           (0x0282)  ///< 0.0392 * 2^LUX_SCALE
#define TSL2561_LUX_M4C           (0x03df)  ///< 0.0605 * 2^LUX_SCALE
#define TSL2561_LUX_K5C           (0x014d)  ///< 0.65 * 2^RATIO_SCALE
#define TSL2561_LUX_B5C           (0x0177)  ///< 0.0229 * 2^LUX_SCALE
#define TSL2561_LUX_M5C           (0x01dd)  ///< 0.0291 * 2^LUX_SCALE
#define TSL2561_LUX_K6C           (0x019a)  ///< 0.80 * 2^RATIO_SCALE
#define TSL2561_LUX_B6C           (0x0101)  ///< 0.0157 * 2^LUX_SCALE
#define TSL2561_LUX_M6C           (0x0127)  ///< 0.0180 * 2^LUX_SCALE
#define TSL2561_LUX_K7C           (0x029a)  ///< 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B7C           (0x0037)  ///< 0.00338 * 2^LUX_SCALE
#define TSL2561_LUX_M7C           (0x002b)  ///< 0.00260 * 2^LUX_SCALE
#define TSL2561_LUX_K8C           (0x029a)  ///< 1.3 * 2^RATIO_SCALE
#define TSL2561_LUX_B8C           (0x0000)  ///< 0.000 * 2^LUX_SCALE
#define TSL2561_LUX_M8C           (0x0000)  ///< 0.000 * 2^LUX_SCALE

// Auto-gain thresholds
#define TSL2561_AGC_THI_13MS      (4850)    ///< Max value at Ti 13ms = 5047
#define TSL2561_AGC_TLO_13MS      (100)     ///< Min value at Ti 13ms = 100
#define TSL2561_AGC_THI_101MS     (36000)   ///< Max value at Ti 101ms = 37177
#define TSL2561_AGC_TLO_101MS     (200)     ///< Min value at Ti 101ms = 200
#define TSL2561_AGC_THI_402MS     (63000)   ///< Max value at Ti 402ms = 65535
#define TSL2561_AGC_TLO_402MS     (500)     ///< Min value at Ti 402ms = 500

// Clipping thresholds
#define TSL2561_CLIPPING_13MS     (4900)    ///< # Counts that trigger a change in gain/integration
#define TSL2561_CLIPPING_101MS    (37000)   ///< # Counts that trigger a change in gain/integration
#define TSL2561_CLIPPING_402MS    (65000)   ///< # Counts that trigger a change in gain/integration

// Delay for integration times
#define TSL2561_DELAY_INTTIME_13MS    (15)    ///< Wait 15ms for 13ms integration
#define TSL2561_DELAY_INTTIME_101MS   (120)   ///< Wait 120ms for 101ms integration
#define TSL2561_DELAY_INTTIME_402MS   (450)   ///< Wait 450ms for 402ms integration

/** TSL2561 I2C Registers */
enum
{
  TSL2561_REGISTER_CONTROL          = 0x00, // Control/power register 
  TSL2561_REGISTER_TIMING           = 0x01, // Set integration time register
  TSL2561_REGISTER_THRESHHOLDL_LOW  = 0x02, // Interrupt low threshold low-byte
  TSL2561_REGISTER_THRESHHOLDL_HIGH = 0x03, // Interrupt low threshold high-byte
  TSL2561_REGISTER_THRESHHOLDH_LOW  = 0x04, // Interrupt high threshold low-byte
  TSL2561_REGISTER_THRESHHOLDH_HIGH = 0x05, // Interrupt high threshold high-byte
  TSL2561_REGISTER_INTERRUPT        = 0x06, // Interrupt settings
  TSL2561_REGISTER_CRC              = 0x08, // Factory use only
  TSL2561_REGISTER_ID               = 0x0A, // TSL2561 identification setting
  TSL2561_REGISTER_CHAN0_LOW        = 0x0C, // Light data channel 0, low byte
  TSL2561_REGISTER_CHAN0_HIGH       = 0x0D, // Light data channel 0, high byte
  TSL2561_REGISTER_CHAN1_LOW        = 0x0E, // Light data channel 1, low byte
  TSL2561_REGISTER_CHAN1_HIGH       = 0x0F  // Light data channel 1, high byte
};

/** Three options for how long to integrate readings for */
typedef enum
{
  TSL2561_INTEGRATIONTIME_13MS      = 0x00,    // 13.7ms
  TSL2561_INTEGRATIONTIME_101MS     = 0x01,    // 101ms
  TSL2561_INTEGRATIONTIME_402MS     = 0x02     // 402ms
}
tsl2561IntegrationTime_t;

/** TSL2561 offers 2 gain settings */
typedef enum
{
  TSL2561_GAIN_1X                   = 0x00,    // No gain
  TSL2561_GAIN_16X                  = 0x10,    // 16x gain
}
tsl2561Gain_t;


void enable(){
i2c_write( TSL2561_CONTROL_POWERON, TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_ADRESS); 
}

void disable(){
i2c_write( TSL2561_CONTROL_POWEROFF, TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_ADRESS);
}


void init(){

uint8_t id=0;
i2c_read(&id, TSL2561_REGISTER_ID, TSL2561_ADRESS);
setIntegrationTime(tsl2561IntegrationTime);
setGain(tsl2561Gain);
disable();
}


void setGain(tsl2561Gain_t gain)
{
  enable();
  i2c_write( _tsl2561IntegrationTime | gain, TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, TSL2561_ADRESS);
  tsl2561Gain = gain;
  disable();
}


void setIntegrationTime(tsl2561IntegrationTime_t time)
{
   enable(); 
  i2c_write( time | _tsl2561Gain, TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, TSL2561_ADRESS);
  tsl2561IntegrationTime = time;
  disable();
}

uint8_t i2c_write( uint8_t data, uint8_t command, uint8_t sla_addr ) {
   
    if ( !i2c_start() )
        return 0; // ERROR

    else {

        if ( !i2c_write_address(sla_addr, TW_WRITE ) )
            return 0; // ERROR    
        
        else {

            if ( !i2c_write_data (command) ) 
                return 0; // ERROR          
            
            else {

                if ( !i2c_write_data(data) )
                     return 0; // ERROR
                
                else
                    i2c_stop();
            }

        }

    }

    return 1; //SUCESS

}

void getData (uint16_t *broadband, uint16_t *ir)
{
 	uint8_t low = 0;
   	uint8_t high = 0;
 	enable();
  	switch (tsl2561IntegrationTime)
  	{
    	case TSL2561_INTEGRATIONTIME_13MS:
      	delay(TSL2561_DELAY_INTTIME_13MS);  // KTOWN: Was 14ms
      	break;
    	case TSL2561_INTEGRATIONTIME_101MS:
      	delay(TSL2561_DELAY_INTTIME_101MS); // KTOWN: Was 102ms
      	break;
    	default:
      	delay(TSL2561_DELAY_INTTIME_402MS); // KTOWN: Was 403ms
      	break;
 	 }
   i2c_read( &low, TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN0_LOW, TSL2561_ADDRESS );
   i2c_read_data( &high );
*broadband = (high<<8)|low;

i2c_read( &low, TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN1_LOW, TSL2561_ADDRESS ); 
i2c_read_data( &high );

*ir = (high<<8)|low;
disable();
}

uint32_t calculateLux(uint16_t broadband, uint16_t ir)
{
  unsigned long chScale;
  unsigned long channel1;
  unsigned long channel0;

  /* Make sure the sensor isn't saturated! */
  uint16_t clipThreshold;
  switch (tsl2561IntegrationTime)
  {
    case TSL2561_INTEGRATIONTIME_13MS:
      clipThreshold = TSL2561_CLIPPING_13MS;
      break;
    case TSL2561_INTEGRATIONTIME_101MS:
      clipThreshold = TSL2561_CLIPPING_101MS;
      break;
    default:
      clipThreshold = TSL2561_CLIPPING_402MS;
      break;
  }

  /* Return 65536 lux if the sensor is saturated */
  if ((broadband > clipThreshold) || (ir > clipThreshold))
  {
    return 65536;
  }

  /* Get the correct scale depending on the intergration time */
  switch (tsl2561IntegrationTime)
  {
    case TSL2561_INTEGRATIONTIME_13MS:
      chScale = TSL2561_LUX_CHSCALE_TINT0;
      break;
    case TSL2561_INTEGRATIONTIME_101MS:
      chScale = TSL2561_LUX_CHSCALE_TINT1;
      break;
    default: /* No scaling ... integration time = 402ms */
      chScale = (1 << TSL2561_LUX_CHSCALE);
      break;
  }

  /* Scale for gain (1x or 16x) */
  if (!tsl2561Gain) chScale = chScale << 4;

  /* Scale the channel values */
  channel0 = (broadband * chScale) >> TSL2561_LUX_CHSCALE;
  channel1 = (ir * chScale) >> TSL2561_LUX_CHSCALE;

  /* Find the ratio of the channel values (Channel1/Channel0) */
  unsigned long ratio1 = 0;
  if (channel0 != 0) ratio1 = (channel1 << (TSL2561_LUX_RATIOSCALE+1)) / channel0;

  /* round the ratio value */
  unsigned long ratio = (ratio1 + 1) >> 1;

  unsigned int b, m;

#ifdef TSL2561_PACKAGE_CS
  if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1C))
    {b=TSL2561_LUX_B1C; m=TSL2561_LUX_M1C;}
  else if (ratio <= TSL2561_LUX_K2C)
    {b=TSL2561_LUX_B2C; m=TSL2561_LUX_M2C;}
  else if (ratio <= TSL2561_LUX_K3C)
    {b=TSL2561_LUX_B3C; m=TSL2561_LUX_M3C;}
  else if (ratio <= TSL2561_LUX_K4C)
    {b=TSL2561_LUX_B4C; m=TSL2561_LUX_M4C;}
  else if (ratio <= TSL2561_LUX_K5C)
    {b=TSL2561_LUX_B5C; m=TSL2561_LUX_M5C;}
  else if (ratio <= TSL2561_LUX_K6C)
    {b=TSL2561_LUX_B6C; m=TSL2561_LUX_M6C;}
  else if (ratio <= TSL2561_LUX_K7C)
    {b=TSL2561_LUX_B7C; m=TSL2561_LUX_M7C;}
  else if (ratio > TSL2561_LUX_K8C)
    {b=TSL2561_LUX_B8C; m=TSL2561_LUX_M8C;}
#else
  if ((ratio >= 0) && (ratio <= TSL2561_LUX_K1T))
    {b=TSL2561_LUX_B1T; m=TSL2561_LUX_M1T;}
  else if (ratio <= TSL2561_LUX_K2T)
    {b=TSL2561_LUX_B2T; m=TSL2561_LUX_M2T;}
  else if (ratio <= TSL2561_LUX_K3T)
    {b=TSL2561_LUX_B3T; m=TSL2561_LUX_M3T;}
  else if (ratio <= TSL2561_LUX_K4T)
    {b=TSL2561_LUX_B4T; m=TSL2561_LUX_M4T;}
  else if (ratio <= TSL2561_LUX_K5T)
    {b=TSL2561_LUX_B5T; m=TSL2561_LUX_M5T;}
  else if (ratio <= TSL2561_LUX_K6T)
    {b=TSL2561_LUX_B6T; m=TSL2561_LUX_M6T;}
  else if (ratio <= TSL2561_LUX_K7T)
    {b=TSL2561_LUX_B7T; m=TSL2561_LUX_M7T;}
  else if (ratio > TSL2561_LUX_K8T)
    {b=TSL2561_LUX_B8T; m=TSL2561_LUX_M8T;}
#endif

  unsigned long temp;
  channel0 = channel0 * b;
  channel1 = channel1 * m;
  
  temp = 0;
  /* Do not allow negative lux value */
  if (channel0 > channel1) temp = channel0 - channel1;

  /* Round lsb (2^(LUX_SCALE-1)) */
  temp += (1 << (TSL2561_LUX_LUXSCALE-1));

  /* Strip off fractional portion */
  uint32_t lux = temp >> TSL2561_LUX_LUXSCALE;

  /* Signal I2C had no errors */
  return lux;
}

void enableAutoRange(bool enable)
{
   tsl2561AutoGain = enable;
}

void getLuminosity (uint16_t *broadband, uint16_t *ir)
{
  bool valid = false;

  /* If Auto gain disabled get a single reading and continue */
  if(!tsl2561AutoGain)
  {
    getData (broadband, ir);
    return;
  }

  /* Read data until we find a valid range */
  bool agcCheck = false;
  do
  {
    uint16_t b, ir;
    uint16_t hi, lo;
    tsl2561IntegrationTime_t it = tsl2561IntegrationTime;

    /* Get the hi/low threshold for the current integration time */
    switch(it)
    {
      case TSL2561_INTEGRATIONTIME_13MS:
        hi = TSL2561_AGC_THI_13MS;
        lo = TSL2561_AGC_TLO_13MS;
        break;
      case TSL2561_INTEGRATIONTIME_101MS:
        hi = TSL2561_AGC_THI_101MS;
        lo = TSL2561_AGC_TLO_101MS;
        break;
      default:
        hi = TSL2561_AGC_THI_402MS;
        lo = TSL2561_AGC_TLO_402MS;
        break;
    }

    getData(&_b, &_ir);

    /* Run an auto-gain check if we haven't already done so ... */
    if (!agcCheck)
    {
      if ((b < lo) && (tsl2561Gain == TSL2561_GAIN_1X))
      {
        /* Increase the gain and try again */
        setGain(TSL2561_GAIN_16X);
        /* Drop the previous conversion results */
        getData(&b, &ir);
        /* Set a flag to indicate we've adjusted the gain */
        agcCheck = true;
      }
      else if ((b > hi) && (tsl2561Gain == TSL2561_GAIN_16X))
      {
        /* Drop gain to 1x and try again */
        setGain(TSL2561_GAIN_1X);
        /* Drop the previous conversion results */
        getData(&b, &ir);
        /* Set a flag to indicate we've adjusted the gain */
        agcCheck = true;
      }
      else
    }
    else
    {
      /* If we've already adjusted the gain once, just return the new results.
         This avoids endless loops where a value is at one extreme pre-gain,
         and the the other extreme post-gain */
      *broadband = b;
      *ir = ir;
      valid = true;
    }
  } while (!valid);
}

#ifndef F_CPU
    #define F_CPU           16000000ul //16MHz
#endif

#define I2C_WRITE           0
#define I2C_READ            1

#define MASK_MODE           0b1
#define MASK_ADDRESS        0x7F   
#define MASK_STATUS_CODE    0xF8    
#define MASK_LENGHT_DATA    0xFF

# define Prescaler          1
# define F_SCL              100000 //100kHz



void i2c_init( void ) {

    // clear TWI status registe
    TWSR = 0x00;  
    // SCL_frequency = CPU_CLock_frequency / ( 16 + 2 * PrescalerValue )
    TWBR = ( ( ( ( F_CPU / F_SCL ) /  Prescaler ) - 16 ) / 2 );
}

uint8_t i2c_start( void ) {

    // send start condition
        // TWSTA must be written to one to transmit a START condition 
        // TWINT must be written to one to clear the TWINT flag
        // TWEN must be written to one to enable the 2-wire serial interface
    TWCR = ( 1 << TWINT ) | ( 1 << TWSTA ) | ( 1 << TWEN );
    
    // Wait for TWINT Flag set
        // Indicates that the START confition has been transmitted
    while ( !( TWCR & ( 1 << TWINT ) ) );

    // Status code in TWSR after START condition has been transmitred is TW_START
        // Check value of status code in TWSR
	if ( ( TWSR & MASK_STATUS_CODE ) != TW_START )
        return 0; // ERROR

    // else     
        // printf("Start condition has been transmitter\n");
    return 1; // SUCESS
}

uint8_t i2c_repeat_start( void ) {

    // Send the START bit    
    TWCR = ( 1 << TWINT ) | ( 1 << TWSTA ) | ( 1 << TWEN );

    // Wait for the Interrupt to be set, to confirm START has been transmitted
    while ( !( TWCR & ( 1 << TWINT ) ) );

    // Check if repeated start condition has been transmitted
    if ( ( TWSR & MASK_STATUS_CODE ) !=  TW_REP_START ) 
        return 0; // ERROR
    
    // else
        // printf("Repeat Start condition has been transmitter\n");
    return 1; // SUCESS

}

void i2c_stop( void ) {
    
    // Read Nack
    TWCR = ( 1 << TWINT )  | ( 1 << TWEN );
    while ( !( TWCR & ( 1 << TWINT ) ) );

    // Transmit STOP condition
	TWCR = ( 1 << TWINT ) | ( 1 << TWEN ) | ( 1 << TWSTO );
    while ( ( TWCR & ( 1 << TWSTO ) ) );

    //printf("Stop condition has been transmitter\n");

}

uint8_t i2c_write_address( uint8_t SLA_ADDR, uint8_t mode ) {

    // MR mode or MT mode, SLA_ADDR ( SLA_W/SLA_R ) must be transmitted
	    // load SLA_ADDR ( 7 bits ) into data register TWDR
        // load mode ( WRITE / READ ) into LSB
	TWDR =  ( ( SLA_ADDR & MASK_ADDRESS ) << 1 ) + ( mode & MASK_MODE );

    // Clear TWINT bit in TWCR to start transmission of address
	TWCR = ( 1 << TWINT ) | ( 1 << TWEN );

	// Wait for TWINT flag
        // Indicates SLA_R was been transmitedd and ACK/NACK has been received
	while ( !( TWCR & ( 1 << TWINT ) ) );

    // Status code in TWSR after SLA_R was been transmitedd and ACK has been received is TW_MT_SLA_ACK or TW_MR_SLA_ACK
        // Check value of status code in TWSR
	if ( ( ( TWSR & MASK_STATUS_CODE ) !=  TW_MT_SLA_ACK ) && ( mode == TW_WRITE ) ) 
        return 0; // ERROR
    else if ( ( ( TWSR & MASK_STATUS_CODE ) !=  TW_MR_SLA_ACK ) && ( mode == TW_READ ) ) 
        return 0; // ERROR

    // else
        // printf("Address has been transmitter and ACK has been receive\n");
    return 1; // SUCESS
    
}

uint8_t i2c_write_data( uint8_t data ) {
    
    // Load data into TWDR register
    TWDR = data & MASK_LENGHT_DATA;

    // Clear TWINT bit to start transmission 
    TWCR = ( 1 << TWINT ) | ( 1 << TWEN );

	// wait for TWINT flag
    // Indicates that the DATA has been transmitted, and ACK/NACK has been received.
    while ( !( TWCR & ( 1 << TWINT ) ) );

   // Status code in TWSR after data was been transmitedd and  ACK/NACK has been received iS T_DATA_ACK_STATUS_CODE
        // Check value of status code in TWSR
    if ( ( TWSR & MASK_STATUS_CODE )  !=  TW_MT_DATA_ACK ) 
        return 0; //ERROR

    // else
        // printf("Data has been transmitter and ACK has been receive\n");
   
    return 1; // SUCESS
    
}

int8_t i2c_read_data( uint8_t* data ) {

    // start TWI module and acknowledge data after reception
    TWCR = ( 1<<TWINT ) | ( 1<<TWEN ) | ( 1<<TWEA ); 

    // wait for TWINT flag
    while ( !( TWCR & ( 1 << TWINT ) ) );
    
    // Received data can be read from the TWDR
    *data = TWDR;

    // Status code in TWSR after data was been received and ACK has been returned iS TW_MR_DATA_ACK
        // Check value of status code in TWSR
    if ( ( TWSR & MASK_STATUS_CODE)   !=  TW_MR_DATA_ACK ) 
        return 0; //ERROR
    // else
        // printf("Data byte has been received and ACK has been returned\n");

    return 1; //  SUCESS
}


uint8_t i2c_read( uint8_t* data, uint8_t command, uint8_t sla_addr ) {

    if ( !i2c_start() )
        return 0; // ERROR

    else {
       
        if ( !i2c_write_address(sla_addr, TW_WRITE) )
            return 0; // ERROR
        
        else {

            if ( !i2c_write_data (command) ) 
                return 0; // ERROR

            else {

                if ( !i2c_repeat_start() )
                    return 0; // ERROR
                
                else {

                    if ( !i2c_write_address(sla_addr, TW_READ) )
                        return 0; // ERROR
                    
                    else {

                        if( !i2c_read_data(data) )
                                return 0; // ERROR
                    }
                          
                }
                    
            }
               
        }
        
    }
    
    return 1; // SUCESS

}

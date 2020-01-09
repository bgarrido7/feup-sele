
#include "TSL2561.h"

/**************************************************************************/
/*!
    @brief Constructor
    @param addr The I2C address this chip can be found on, 0x29, 0x39 or 0x49
    @param sensorID An optional ID that will be placed in sensor events to help
                    keep track if you have many sensors in use
*/
/**************************************************************************/
TSL2561::TSL2561(uint8_t addr, int32_t sensorID)
{
  _addr = addr;
  _tsl2561Initialised = false;
  _tsl2561AutoGain = false;
  _tsl2561IntegrationTime = TSL2561_INTEGRATIONTIME_13MS;
  _tsl2561Gain = TSL2561_GAIN_1X;
  _tsl2561SensorID = sensorID;
}


void TSL2561::begin()
{
    TWBR = (uint8_t)TWBR_val;
    PORTC &= (1<<PC4) || (1<<PC5);
    
}

boolean TSL2561::init()
{
  /* Make sure we're actually connected */
  uint8_t x = read8(TSL2561_REGISTER_ID);
  if (x & 0x05) { // ID code for TSL2561
    return false;
  }
  _tsl2561Initialised = true;

  /* Set default integration time and gain */
  setIntegrationTime(_tsl2561IntegrationTime);
  setGain(_tsl2561Gain);

  /* Note: by default, the device is in power down mode on bootup */
  disable();

  return true;
}

/**************************************************************************/
/*!
    @brief  Enables or disables the auto-gain settings when reading
            data from the sensor
    @param enable Set to true to enable, False to disable
*/
/**************************************************************************/
void TSL2561::enableAutoRange(bool enable)
{
   _tsl2561AutoGain = enable;
}

/**************************************************************************/
/*!
    @brief      Sets the integration time for the TSL2561. Higher time means
                more light captured (better for low light conditions) but will
		take longer to run readings.
    @param time The amount of time we'd like to add up values
*/
/**************************************************************************/
void TSL2561::setIntegrationTime(tsl2561IntegrationTime_t time)
{
  if (!_tsl2561Initialised) begin();

  /* Enable the device by setting the control bit to 0x03 */
  enable();

  /* Update the timing register */
  write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, time | _tsl2561Gain);

  /* Update value placeholders */
  _tsl2561IntegrationTime = time;

  /* Turn the device off to save power */
  disable();
}

/**************************************************************************/
/*!
    @brief  Adjusts the gain on the TSL2561 (adjusts the sensitivity to light)
    @param gain The value we'd like to set the gain to
*/
/**************************************************************************/
void TSL2561::setGain(tsl2561Gain_t gain)
{
  if (!_tsl2561Initialised) begin();

  /* Enable the device by setting the control bit to 0x03 */
  enable();

  /* Update the timing register */
  write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_TIMING, _tsl2561IntegrationTime | gain);

  /* Update value placeholders */
  _tsl2561Gain = gain;

  /* Turn the device off to save power */
  disable();
}

/**************************************************************************/
/*!
    @brief  Gets the broadband (mixed lighting) and IR only values from
            the TSL2561, adjusting gain if auto-gain is enabled
    @param  broadband Pointer to a uint16_t we will fill with a sensor
                      reading from the IR+visible light diode.
    @param  ir Pointer to a uint16_t we will fill with a sensor the
               IR-only light diode.
*/
/**************************************************************************/
void TSL2561::getLuminosity (uint16_t *broadband, uint16_t *ir)
{
  bool valid = false;

  if (!_tsl2561Initialised) begin();

  /* If Auto gain disabled get a single reading and continue */
  if(!_tsl2561AutoGain)
  {
    getData (broadband, ir);
    return;
  }

  /* Read data until we find a valid range */
  bool _agcCheck = false;
  do
  {
    uint16_t _b, _ir;
    uint16_t _hi, _lo;
    tsl2561IntegrationTime_t _it = _tsl2561IntegrationTime;

    /* Get the hi/low threshold for the current integration time */
    switch(_it)
    {
      case TSL2561_INTEGRATIONTIME_13MS:
        _hi = TSL2561_AGC_THI_13MS;
        _lo = TSL2561_AGC_TLO_13MS;
        break;
      case TSL2561_INTEGRATIONTIME_101MS:
        _hi = TSL2561_AGC_THI_101MS;
        _lo = TSL2561_AGC_TLO_101MS;
        break;
      default:
        _hi = TSL2561_AGC_THI_402MS;
        _lo = TSL2561_AGC_TLO_402MS;
        break;
    }

    getData(&_b, &_ir);

    /* Run an auto-gain check if we haven't already done so ... */
    if (!_agcCheck)
    {
      if ((_b < _lo) && (_tsl2561Gain == TSL2561_GAIN_1X))
      {
        /* Increase the gain and try again */
        setGain(TSL2561_GAIN_16X);
        /* Drop the previous conversion results */
        getData(&_b, &_ir);
        /* Set a flag to indicate we've adjusted the gain */
        _agcCheck = true;
      }
      else if ((_b > _hi) && (_tsl2561Gain == TSL2561_GAIN_16X))
      {
        /* Drop gain to 1x and try again */
        setGain(TSL2561_GAIN_1X);
        /* Drop the previous conversion results */
        getData(&_b, &_ir);
        /* Set a flag to indicate we've adjusted the gain */
        _agcCheck = true;
      }
      else
      {
        /* Nothing to look at here, keep moving ....
           Reading is either valid, or we're already at the chips limits */
        *broadband = _b;
        *ir = _ir;
        valid = true;
      }
    }
    else
    {
      /* If we've already adjusted the gain once, just return the new results.
         This avoids endless loops where a value is at one extreme pre-gain,
         and the the other extreme post-gain */
      *broadband = _b;
      *ir = _ir;
      valid = true;
    }
  } while (!valid);
}



/**************************************************************************/
/*!
    Enables the device
*/
/**************************************************************************/
void TSL2561::enable(void)
{
  /* Enable the device by setting the control bit to 0x03 */
  write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_CONTROL_POWERON);
}

/**************************************************************************/
/*!
    Disables the device (putting it in lower power sleep mode)
*/
/**************************************************************************/
void TSL2561::disable(void)
{
  /* Turn the device off to save power */
  write8(TSL2561_COMMAND_BIT | TSL2561_REGISTER_CONTROL, TSL2561_CONTROL_POWEROFF);
}

/**************************************************************************/
/*!
    Private function to read luminosity on both channels
*/
/**************************************************************************/
void TSL2561::getData (uint16_t *broadband, uint16_t *ir)
{
  /* Enable the device by setting the control bit to 0x03 */
  enable();

  /* Wait x ms for ADC to complete */
  switch (_tsl2561IntegrationTime)
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

  /* Reads a two byte value from channel 0 (visible + infrared) */
  *broadband = read16(TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN0_LOW);

  /* Reads a two byte value from channel 1 (infrared) */
  *ir = read16(TSL2561_COMMAND_BIT | TSL2561_WORD_BIT | TSL2561_REGISTER_CHAN1_LOW);

  /* Turn the device off to save power */
  disable();
}


/**************************************************************************/
/*!
    @brief  Converts the raw sensor values to the standard SI lux equivalent.
    @param  broadband The 16-bit sensor reading from the IR+visible light diode.
    @param  ir The 16-bit sensor reading from the IR-only light diode.
    @returns The integer Lux value we calcuated.
             Returns 0 if the sensor is saturated and the values are
             unreliable, or 65536 if the sensor is saturated.
*/
/**************************************************************************/
/**************************************************************************/
/*!

    Returns
*/
/**************************************************************************/
uint32_t TSL2561::calculateLux(uint16_t broadband, uint16_t ir)
{
  unsigned long chScale;
  unsigned long channel1;
  unsigned long channel0;

  /* Make sure the sensor isn't saturated! */
  uint16_t clipThreshold;
  switch (_tsl2561IntegrationTime)
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
  switch (_tsl2561IntegrationTime)
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
  if (!_tsl2561Gain) chScale = chScale << 4;

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

/**************************************************************************/
/*!
    @brief  Gets the most recent sensor event
    @param  event Pointer to a sensor_event_t type that will be filled
                  with the lux value, timestamp, data type and sensor ID.
    @returns True if sensor reading is between 0 and 65535 lux,
             false if sensor is saturated
*/
/**************************************************************************/
bool TSL2561::getEvent(sensors_event_t *event)
{
  uint16_t broadband, ir;

  /* Clear the event */
  memset(event, 0, sizeof(sensors_event_t));

  event->version   = sizeof(sensors_event_t);
  event->sensor_id = _tsl2561SensorID;
  event->type      = SENSOR_TYPE_LIGHT;
  event->timestamp = millis();

  /* Calculate the actual lux value */
  getLuminosity(&broadband, &ir);
  event->light = calculateLux(broadband, ir);

  if (event->light == 65536) {
    return false;
  }
  return true;
}

/**************************************************************************/
/*!
    @brief  Gets the sensor_t data
    @param  sensor A pointer to a sensor_t structure that we will fill with
                   details about the TSL2561 and its capabilities
*/
/**************************************************************************/
void TSL2561::getSensor(sensor_t *sensor)
{
  /* Clear the sensor_t object */
  memset(sensor, 0, sizeof(sensor_t));

  /* Insert the sensor name in the fixed length char array */
  strncpy (sensor->name, "TSL2561", sizeof(sensor->name) - 1);
  sensor->name[sizeof(sensor->name)- 1] = 0;
  sensor->version     = 1;
  sensor->sensor_id   = _tsl2561SensorID;
  sensor->type        = SENSOR_TYPE_LIGHT;
  sensor->min_delay   = 0;
  sensor->max_value   = 17000.0;  /* Based on trial and error ... confirm! */
  sensor->min_value   = 1.0;
  sensor->resolution  = 1.0;
}



/*========================================================================*/
/*                          PRIVATE FUNCTIONS                             */
/*========================================================================*/

/**************************************************************************/
/*!
    @brief  Writes a register and an 8 bit value over I2C
    @param  reg I2C register to write the value to
    @param  value The 8-bit value we're writing to the register
*/
/**************************************************************************/
void TSL2561::write8 (uint8_t reg, uint8_t value)
{
I2C_Start(_addr);
I2C_Write(reg);
I2C_Write(value);
I2C_Stop();
}

/**************************************************************************/
/*!
    @brief  Reads an 8 bit value over I2C
    @param  reg I2C register to read from
    @returns 8-bit value containing single byte data read
*/
/**************************************************************************/
uint8_t TSL2561::read8(uint8_t reg)
{

    I2C_Start(_addr);
    I2C_Write(reg);
    I2C_Stop();


    return I2C_Read_Nack();
}

/**************************************************************************/
/*!
    @brief  Reads a 16 bit values over I2C
    @param  reg I2C register to read from
    @returns 16-bit value containing 2-byte data read
*/
/**************************************************************************/
uint16_t TSL2561::read16(uint8_t reg)
{
  uint16_t x, t;

    I2C_Start(_addr);
  
    I2C_Write(reg);

    I2C_Stop();

    I2C_Start(_addr);
    
    t = I2C_Read_Ack();
    x = I2C_Read_Nack();

  x <<= 8;
  x |= t;
  return x;
}

uint8_t TSL2561::I2C_Start(charwrite_address)/* I2C start function */
{
    uint8_t status;		/* Declare variable */
    TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT); /* Enable TWI, generate START */
    while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
    status=TWSR&0xF8;		/* Read TWI status register */
    if(status!=0x08)		/* Check weather START transmitted or not? */
    return 0;			/* Return 0 to indicate start condition fail */
    TWDR=write_address;		/* Write SLA+W in TWI data register */
    TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI & clear interrupt flag */
    while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
    status=TWSR&0xF8;		/* Read TWI status register */	
    if(status==0x18)		/* Check for SLA+W transmitted &ack received */
    return 1;			/* Return 1 to indicate ack received */
    if(status==0x20)		/* Check for SLA+W transmitted &nack received */
    return 2;			/* Return 2 to indicate nack received */
    else
    return3;			/* Else return 3 to indicate SLA+W failed */
}


uint8_t TSL2561::I2C_Write(chardata)	/* I2C write function */
{
    uint8_tstatus;		/* Declare variable */
    TWDR=data;			/* Copy data in TWI data register */
    TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
    while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
    status=TWSR&0xF8;		/* Read TWI status register */
    if(status==0x28)		/* Check for data transmitted &ack received */
    return 0;			/* Return 0 to indicate ack received */
    if(status==0x30)		/* Check for data transmitted &nack received */
    return 1;			/* Return 1 to indicate nack received */
    else
    return 2;			/* Else return 2 for data transmission failure */
}


char TSL2561::I2C_Read_Ack()		/* I2C read ack function */
{
    TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA); /* Enable TWI, generation of ack */
    while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
    returnTWDR;			/* Return received data */
}

char TSL2561::I2C_Read_Nack()		/* I2C read nack function */
{
    TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
    while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
    return TWDR;		/* Return received data */
}

void TSL2561::I2C_Stop()			/* I2C stop function */
{
    TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);/* Enable TWI, generate stop */
    while(TWCR&(1<<TWSTO));	/* Wait until stop condition execution */
}
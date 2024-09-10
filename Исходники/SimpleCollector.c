void zb_ReceiveDataIndication( uint16 source, uint16 command, uint16 len, uint8 *pData  )
{
  uint8 buf[32];
  uint8 *pBuf;
  uint8 tmpLen;
  uint8 sensorReading;

  if (command == SENSOR_REPORT_CMD_ID)
  {
    // Received report from a sensor
    sensorReading = pData[1];

    // If tool available, write to serial port

    tmpLen = (uint8)osal_strlen( (char*)strDevice );
    pBuf = osal_memcpy( buf, strDevice, tmpLen );
    _ltoa( source, pBuf, 16 );
    pBuf += 4;
    *pBuf++ = ' ';

    if ( pData[0] == BATTERY_REPORT )
    {
      tmpLen = (uint8)osal_strlen( (char*)strBattery );
      pBuf = osal_memcpy( pBuf, strBattery, tmpLen );

      *pBuf++ = (sensorReading / 10 ) + '0';    // convent msb to ascii
      *pBuf++ = '.';                            // decimal point ( battery reading is in units of 0.1 V
      *pBuf++ = (sensorReading % 10 ) + '0';    // convert lsb to ascii
      *pBuf++ = ' ';
      *pBuf++ = 'V';
    }
    else
    {
      tmpLen = (uint8)osal_strlen( (char*)strTemp );
      pBuf = osal_memcpy( pBuf, strTemp, tmpLen );

      *pBuf++ = (sensorReading / 10 ) + '0';    // convent msb to ascii
      *pBuf++ = (sensorReading % 10 ) + '0';    // convert lsb to ascii
      *pBuf++ = ' ';
      *pBuf++ = 'C';
    }

    *pBuf++ = '\r';
    *pBuf++ = '\n';
    *pBuf = '\0';

#if defined( MT_TASK )
    debug_str( (uint8 *)buf );
#endif

    // can also write directly to uart

  }
}
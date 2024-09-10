/*********************************************************************
 * @fn      glucCollCentralPasscodeCB
 *
 * @brief   Passcode callback.
 *
 * @return  none
 */
static void glucCollCentralPasscodeCB( uint8 *deviceAddr, uint16 connectionHandle,
                                        uint8 uiInputs, uint8 uiOutputs )
{
#if (HAL_LCD == TRUE)

  uint32  passcode;
  uint8   str[7];

  // Is the callback to get the passcode from or display it to the user?
  if ( uiInputs != 0 )
  {
    // Passcode must be entered by the user but use the default passcode for now
    passcode = DEFAULT_PASSCODE;
  }
  else
  {
    // Create random passcode
    LL_Rand( ((uint8 *) &passcode), sizeof( uint32 ));
  }
  
  passcode %= 1000000;
  
  // Display passcode to user
  if ( uiOutputs != 0 )
  {
    LCD_WRITE_STRING( "Passcode:",  HAL_LCD_LINE_1 );
    LCD_WRITE_STRING( (char *) _ltoa(passcode, str, 10),  HAL_LCD_LINE_2 );
  }
  
  // Send passcode response
  GAPBondMgr_PasscodeRsp( connectionHandle, SUCCESS, passcode );
#endif
}
/**
* \brief         connects to the channels and initiates read thread.
* \param         void
* \return        S_OK for success, S_FALSE for failure
*/
HRESULT CDIL_CAN_MHS::CAN_StartHardware(void)
{
USES_CONVERSION;
HRESULT hResult;
char str[100];

//VALIDATE_VALUE_RETURN_VAL(sg_bCurrState, STATE_HW_INTERFACE_SELECTED, ERR_IMPROPER_STATE);
if (!str_has_char(sg_MhsCanCfg.CanSnrStr))
  sprintf(str, "Snr=%s", sg_MhsCanCfg.CanSnrStr);
else
  str[0]='\0';
if (!CanDeviceOpen(0, str))
  {
  (void)CanSetOptions("CanTxAckEnable=1");
  // **** CAN Bus Start
  if (CanSetMode(0, OP_CAN_START, CAN_CMD_FIFOS_ERROR_CLEAR) >= 0)
    hResult = S_OK;
  else
    {
    hResult = S_FALSE;
    sg_pIlog->vLogAMessage(A2T(__FILE__), __LINE__, _T("could not start the controller in running mode"));
    }
  sg_bCurrState = STATE_CONNECTED;
  }
else
  {
  //log the error for open port failure
  sg_pIlog->vLogAMessage(A2T(__FILE__), __LINE__, _T("error opening \"Tiny-CAN\" interface"));
  hResult = ERR_LOAD_HW_INTERFACE;
  }
return(hResult);
}
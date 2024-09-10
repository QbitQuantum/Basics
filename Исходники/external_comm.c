void buildTossimEvent(uint16_t moteID, uint16_t type, long long ftime, void *data,
                      unsigned char **msgp, int *lenp) {
  unsigned char *msg;
  int payload_size, total_size;
  
  // Determine payload size
  
  switch (type) {
  case AM_DEBUGMSGEVENT: 
    payload_size = sizeof(DebugMsgEvent);
    break;
  case AM_RADIOMSGSENTEVENT:
    payload_size = sizeof(RadioMsgSentEvent);
    break;
  case AM_UARTMSGSENTEVENT:
    payload_size = sizeof(RadioMsgSentEvent);
    break;
  case AM_ADCDATAREADYEVENT:
    payload_size = sizeof(ADCDataReadyEvent);
    break;
  case AM_TOSSIMINITEVENT:
    payload_size = sizeof(TossimInitEvent);
    break;
  case AM_VARIABLERESOLVERESPONSE:
    payload_size = sizeof(VariableResolveResponse);
    break;
  case AM_VARIABLEREQUESTRESPONSE:
    payload_size = sizeof(VariableRequestResponse);
    break;
  case AM_INTERRUPTEVENT:
    payload_size = sizeof(InterruptEvent);
    dbg(DBG_TEMP, "SIM: Sending InterruptEvent, payload is %i\n", (int)payload_size);
    break;
  case AM_LEDEVENT:
    payload_size = sizeof(LedEvent);
    break;
  default:
    EC_DEBUG(fprintf(stderr, "buildTossimEvent for invalid type: %d", type));
    return;
  }

  total_size = GUI_MSG_HEADER_LENGTH + payload_size;
  msg = (unsigned char *)malloc(total_size);

  *(unsigned short *)(&msg[0]) = htons(type);
  *(unsigned short *)(&msg[2]) = htons(moteID);
  *(long long *)(&msg[4]) = htonll(ftime);
  *(unsigned short *)(&msg[12]) = htons(payload_size);
  memcpy(((unsigned char *)msg)+GUI_MSG_HEADER_LENGTH, data, payload_size);

  EC_DEBUG(fprintf(stderr, "buildTossimEvent: msgType %d (0x%02x) moteID %d (0x%02x) payload size %d total size %d\n", type, type, moteID, moteID, payload_size, total_size));


  *msgp = msg;
  *lenp = total_size;
}
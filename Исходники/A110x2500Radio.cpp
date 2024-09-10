void A110x2500Radio::gdo0Isr()
{
  // Note: It is assumed that interrupts are disabled.
  
  // The GDO0 ISR will only look for the EOP edge. Therefore, if the radio
  // is not transmitting the EOP, it must be receiving an EOP signal.
  if (gDataTransmitting)
  {
    /**
     *  Note: GDO0 is issued prior to the transmitter being completely
     *  finished. The state machine will remain in TX_END until transmission
     *  completes. The following waits for TX_END to correct the hardware
     *  behavior.
     */ 
    while (CC1101GetMarcState(&gPhyInfo.cc1101) == eCC1101MarcStateTx_end);
    gDataTransmitting = false;
  }
  else
  {
    gDataReceived = true;
    readDataStream();
  }
  
  // Always go back to sleep.
  _sleep();
}
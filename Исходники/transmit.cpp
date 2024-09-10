/* Transmission Code */
void Transmit_Packet(void)
{   
    /* Create Xbee object */
    XBee xbee = XBee();

    /* Packet to be transmitted */
    uint8_t payload[MAX_SIZE];

    /* Obtain address of receiving end */
    XBeeAddress64 addr64 = XBeeAddress64(0x0, 0x0);
    ZBTxStatusResponse txStatus = ZBTxStatusResponse();

    /* Clear the payload */
    memset(payload, '\0', sizeof(payload));

    /* Debug Packet */
    //payload[0] = '1';
    //payload[1] = '5';

    /* Transfer information into payload */
    memcpy(payload, &G_packet, sizeof(payload));

    for(int i = 0; i < MAX_SIZE; i++)
    { Serial.write(payload[i]);}

    ZBTxRequest zbTx = ZBTxRequest(addr64, payload, sizeof(payload));
  
    /* Transfer the payload */
    xbee.send(zbTx); //!!Prints packet to serial monitor

    /* delay */
    delay(1000);
}
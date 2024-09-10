//-------------------------------------------------------------------
//  Description:
//     Send a break on the com port for "len" msec
//
//  portnum    - number 0 to MAX_PORTNUM-1.  This number is provided to
//                 indicate the symbolic port number.
//
void BreakCOM(int portnum)
{
   // start the reset pulse
   SetCommBreak(ComID[portnum]);

   // delay
   msDelay(2);

   // clear the reset pulse and return
   // PROGRAMMER'S NOTE: ClearCommBreak is returning 24:an undefined code
   ClearCommBreak(ComID[portnum]);

   // Win3.1 bug, close and then open port
   CloseCOM(portnum);
   OpenCOM(portnum,&port[0]);
}
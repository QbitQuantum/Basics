/*-------------------------------------------
| Name:comThread
| Description:
| Parameters:
| Return Type:
| Comments:
| See:
---------------------------------------------*/
DWORD comThread (LPVOID lpParameter)
{
   int i;

   printf("uart wait on %s...\n",USE_COM);
   while ( !bComStopped )
   {
      DWORD dwEvtMask = 0;

      WaitCommEvent( hCom, &dwEvtMask, NULL );
      if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
      {
         //printf("event\n");
         do
         {
            if (rcvLength  = _readCom( hCom, rcvBuffer, MAX_BUFFER  ))
            {

               for(i=0; i<rcvLength; i++)
               {
                  //printf("%c\n",rcvBuffer[i]);
                  Sleep(/*5*/ 0);
                  //WriteRS232ReceiveRegister(rcvBuffer[i]);
                  rcvData = rcvBuffer[i];
                  if(rcv_interrupt_enable) {
                     emuFireInterrupt(72);
                     //Synchro
                     WaitForSingleObject(hRS232PhysicalSimEvent,nRS232PhysicalSimTimeOut);
                  }

               }
            }
         } while ( rcvLength > 0 );
      }
      if ( (dwEvtMask & EV_TXEMPTY) == EV_TXEMPTY )
      {

      }
   }

   // get rid of event handle
   dwThreadID = 0;

   return 0;
}
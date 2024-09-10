VOID  APIENTRY PlayThread ( ULONG parm1 )
{

   ULONG    ulBytesRead;
   ULONG    ulBufferNum;
   ULONG    ulPostCount;
   ULONG    ulReturn;
   MCI_PLAY_PARMS        mciPlayParameters;



   mciPlayParameters.hwndCallback =  hwndDiag;

   /*
    * Send the Play Command to begin the playing of the memory playlist.
    */
   ulReturn = mciSendCommand(usWaveDeviceId,
                             MCI_PLAY,
                             MCI_NOTIFY,
                             (PVOID) &mciPlayParameters,
                             0);

   /*
    * Loop until the playlist is stopped.
    */
   while( !fEndPlay )
   {

      for( ulBufferNum = 0; ulBufferNum < MAXBUFF; ulBufferNum++ )
      {

         /*
          * Use DosWaitEventSem to pause util the playlist plays this
          * buffer. Then refill the buffer and post the semaphore.
          */
         ulReturn = DosWaitEventSem ( hevSem[ulBufferNum], 5000L );

         DosResetEventSem ( hevSem[ulBufferNum], &ulPostCount );

         if( fEndPlay ) break;

            /*
             * Read the Next MAXSIZE bytes of the wave file
             */
            ulBytesRead =
                   mmioRead(hmmioFileHandle,
                            (HPSTR) achDataBuffer[ulBufferNum],
                            MAXSIZE);


            /*
             * If we have reached the end of the wave file then set the file marker
             * to the begining of the file and start reading into the bufferno.
             * This causes the continuous filling and playing of the data buffer
             * again and again as long as the END push button is not pressed.
             * The wave file is going to keep on playing without any interruptions
             * util ther user selects the stop button.
             */
            if (ulBytesRead < MAXSIZE)
              {
               /* Seek to the starting of the wave file */
               mmioSeek(hmmioFileHandle, 0, SEEK_SET);

               /* Read the Next MAXSIZE bytes of the wave file */
               mmioRead(hmmioFileHandle,
                       (HPSTR) achDataBuffer[ulBufferNum],
                       MAXSIZE);


              }


      } /* End of for loop */


   } /* End of while loop */


}   /* End of function PlayThread */
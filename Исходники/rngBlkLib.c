/**************************************************************
*
* rngBlkPut - put element into a blocking ring buffer
*
*
*  This routine copies n elements from <buffer> into blocking ring buffer
*<rngd>. The specified number of elements will be put into the ring buffer.
*If there is insuffient room the calling task will BLOCK.
*
* RETURNS:
*  The number of elements actually put into ring buffer.
*
*	Author Greg Brissey 5/26/94
*/
int rngBlkPut(RINGBLK_ID rngd,register long* buffer,register int size)
/* RINGBLK_ID rngd;	blocking ring buffer to put data into */
/* long*      buffer;   buffer to get data from */
/* int	      size;     number of elements to put */
{
   register int fromP;
   int fbytes;
   register int result,i;

   DWORD winStatus;
   winStatus = WaitForSingleObject(rngd->hMutex, INFINITE);
   if (winStatus == WAIT_FAILED) {
      return -1;
   }   

   while( (fbytes = ( 
	       ( (result = ((rngd->pFromBuf - rngd->pToBuf) - 1)) < 0) ?
                  result + rngd->bufSize : result ) ) < size)
   {
      /*
      printf("rngBlkPut: semGive OK2Read., free bytes: %d \n",fbytes);
      */

      rngd->writeBlocked = TRUE;

      if (rngd->readBlocked) {                  /* if read blocked, */
         rngd->readBlocked = FALSE;
         SetEvent(rngd->hSyncOk2ReadEvent);
      } 


      while( rngd->writeBlocked) {
         SignalObjectAndWait(rngd->hMutex, rngd->hSyncOk2WriteEvent, INFINITE, FALSE);
         winStatus = WaitForSingleObject(rngd->hMutex, INFINITE);
         if (winStatus == WAIT_FAILED) {
            return -1;
         }
      } 

   }

   for (i = 0; i < size; i++)
   {
     /* this macro inlines the code for speed */
     RNG_LONG_PUT(rngd, (buffer[i]), fromP);
   }

   /* if I just wrote something into the ring buffer & read is block */
   /* release the reading because there is now room in the buffer */

   if ( (rngd->readBlocked) && ( rngBlkNElem(rngd) > rngd->blkTilNentries) )
   {
     /* printf("rngBlkGet: OK2Write given.\n"); */
      rngd->readBlocked = FALSE;
      SetEvent(rngd->hSyncOk2ReadEvent);
   }
   ReleaseMutex(rngd->hMutex);     
   return( size );
}
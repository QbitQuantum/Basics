void rayCrossed_isr()
{
   if(INPUT(PIN_B2)&& rayTwo!=1)
   {
      rayTwo = 1;
      if(rayOne == 1)
      {
         if(checkTimer() == 1)
         {
            noOfPeople++ ;
            number_changed = 1;
         }
         rayOne = 0;
         rayTwo = 0;
      }
      setTimer();
   }
  else  if(INPUT(PIN_B1)&& rayOne!=1)
   {
      rayOne = 1;
      if(rayTwo == 1)
      {
         if(checkTimer() == 1)
         {
            noOfPeople-- ;
            number_changed = 1;
         }
         rayOne = 0;
         rayTwo = 0;
      }
      setTimer();
   }
   delay_ms(MIN_DELAY_BETWEEN_TWO_INTERRUPTS/2);
   //OUTPUT_HIGH(PIN_B7);
   delay_ms(MIN_DELAY_BETWEEN_TWO_INTERRUPTS/2);
   //OUTPUT_LOW(PIN_B7);
 }
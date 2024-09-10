//---------- Begin of function Misc::format --------//
//
// Format a number to a float number to format string
// Note : the formated string is right justified
//
// <double> inNum = the number to be formated
//                  use <double> instead of <float> because
//                  fcvt() only accept <double>
//
// [int] formatType = 1 - 1,000,000  add thousand seperator
//                    2 - $1,000,000 add thousand seperator and dollar sign
//                    3 - 56% add percentage sign % at the end of the number
//
// return <char*> the pointer to the converted string, the string
//                is stored in static variable which will be overwritten
//                in next call.
//
char* Misc::format(double inNum, int formatType)
{
   enum { MONEY_DEC_PLACE = 2 };

   static char outBuf[35];
   char   *outPtr=outBuf;
   char   *floatStr;
   int    i, intDigit, sign;    // intDigit = no. of integer digits

   floatStr = fcvt( inNum, MONEY_DEC_PLACE, &intDigit, &sign );

   #ifdef DEBUG
      if( intDigit > 29 )            // integer digits can't exceed 29
         err.run( "Misc::format(), inNum : %e, formatType : %d", inNum, formatType );
   #endif

   //--------- negetive bracket ------------//

   if( inNum < 0 )
      *outPtr++ = '(';

   //--------- dollar sign ($) ------------//

   if( formatType == 2 )
      *outPtr++ = '$';

   //------- integer number -----------//

   for( i=intDigit ; i>0 ; i-- )
   {
      if( i%THOUSAND_SEPARATOR_COUNT == 0 && i < intDigit )
         *outPtr++ = THOUSAND_SEPARATOR;

      *outPtr++ = *floatStr++;
   }

   if( intDigit <= 0 )
      *outPtr++ = '0';

   //------- dec. place number -----------//

   if( inNum > -1000 && inNum < 1000 )    // if the number is less than 1000, add dec. places
   {                                      // if the number is greater than 1000, truncate any dec. places
      *outPtr++ = DECIMAL_SEPARATOR;

      if( *floatStr && intDigit >= 0 )    // e.g. 0.03 --> str:"3", intDight:-1
         *outPtr++ = *floatStr++;         // 1st dec. place
      else
         *outPtr++ = '0';                 // add a '0' when intDigit < 0

      if( *floatStr )                     // 2nd dec. place
         *outPtr++ = *floatStr++;
      else
         *outPtr++ = '0';
   }

   //--------- percent sign (%) ------------//

   if( formatType == 3 )
      *outPtr++ = '%';

   //--------- negetive bracket ------------//

   if( inNum < 0 )
      *outPtr++ = ')';

   *outPtr++ = '\0';

   return outBuf;
}
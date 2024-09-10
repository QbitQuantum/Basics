void UDA_Driver::PutFloat(float val, uint8_t nbDecimal)
{
   char tab[4];
   unsigned char i;
   
   for ( i = 0 ; i < nbDecimal ; i++ )
   {
      val = val * 10.0;
   }
   
   unsigned short val10 = (unsigned short)(val);
   memset(tab,0,sizeof(tab));
   sprintf(tab,"%02d",val10);
   unsigned char offset = 0;
   for ( i = 0 ; i < 3 ; i++ )
   {
      if ( i >= ( 3 - strlen(tab)))
      {         
         if ( (i == (2-nbDecimal)) && (nbDecimal != 0) )
            PutChar(i,tab[offset] | 0x80 );
         else
            PutChar(i,tab[offset] );
         offset++;
      }
      else
      {
         PutChar(i,' ');
      }
   }
   
}
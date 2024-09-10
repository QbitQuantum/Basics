/* Take a qbit off a character */
void remove_qbit( CHAR_DATA * ch, int number )
{
   BIT_DATA *bit;

   if( IS_NPC( ch ) )
      return;

   if( number < 0 || number > MAX_xBITS )
      return;

   if( !ch->pcdata->first_qbit )
      return;

   bit = ch->pcdata->first_qbit;
   while( bit )
   {
      BIT_DATA *tmp;

      if( bit->number == number )
      {
         tmp = bit;
         bit = bit->next;
         UNLINK( tmp, ch->pcdata->first_qbit, ch->pcdata->last_qbit, next, prev );
         DISPOSE( tmp );
      }
      else
         bit = bit->next;
   }
}
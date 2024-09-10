void do_remcontract( CHAR_DATA * ch, char *argument )
{
   CONTRACT_DATA *contract;
   CONTRACT_DATA *scontract = NULL;

   if( argument[0] == '\0' )
   {
      send_to_char( "&RSyntax: remcontract <target name>\n\r", ch );
      return;
   }

   for( contract = ch->first_contract; contract; contract = contract->next_in_contract )
   {
      if( !str_cmp( contract->target, argument ) )
      {
         scontract = contract;
         break;
      }
   }

   if( !scontract || scontract == NULL )
   {
      send_to_char( "No such target.\n\r", ch );
      return;
   }

   STRFREE( scontract->target );
   UNLINK( scontract, ch->first_contract, ch->last_contract, next_in_contract, prev_in_contract );
   DISPOSE( scontract );

   send_to_char( "Contract removed.\n\r", ch );
   return;

}
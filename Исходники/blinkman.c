/* Delete the specified blink manager entry.
 */
void FASTCALL DeleteBlinkManagerEntry( LPBLINKENTRY lpbe )
{
   /* First unlink this entry from
    * the list.
    */
   if( lpbe->lpbePrev )
      lpbe->lpbePrev->lpbeNext = lpbe->lpbeNext;
   else
      lpbeFirst = lpbe->lpbeNext;
   if( lpbe->lpbeNext )
      lpbe->lpbeNext->lpbePrev = lpbe->lpbePrev;

   /* Delete the associated command from the
    * command table. This will also remove any
    * toolbar button.
    */
   CTree_DeleteCommand( lpbe->iCommandID );

   /* Delete from the Blink menu.
    */
   DeleteMenu( hBlinkMenu, lpbe->iCommandID, MF_BYCOMMAND );

   /* Delete from the registry.
    */
   Amuser_WritePPString( szBlinkman, lpbe->szName, NULL );

   /* Free the allocated memory.
    */
   FreeMemory( &lpbe );
}
// GameServer constructor
GameServer::GameServer()
{
   // Set the function for bad new call
   set_new_handler(badNew);

   // Open the input slot
   hInputSlot = createSlot(-1);

   if ( hInputSlot == INVALID_HANDLE_VALUE )
      exit(0);

   // Initialize all nodes to NULL.
   for ( int n = 0; n < MAX_NODE; n++ )
      {
      gNode[n] = NULL;
      }

   // Initialize the game's CRITICAL_SECTION object.
   InitializeCriticalSection(&csCritical);
      
   nCriticalCount = 0;
   nPlayersInGame = 0;
}
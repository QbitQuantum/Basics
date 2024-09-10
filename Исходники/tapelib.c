BOOL GetTapeParms(
   DWORD *total_low,       // O - tape capacity lower 32 bits
   DWORD *total_high,      // O - tape capacity upper 32 bits
   DWORD *freespace_low,   // O - free space remaining lower 32 bits
   DWORD *freespace_high,  // O - free space remaining upper 32 bits
   DWORD *blk_size,        // O - block size
   DWORD *part,            // O - number of partitions
   BOOL  *write_protect    // O - write protect on/off
    )

{

   TAPE_GET_MEDIA_PARAMETERS parms ;
   DWORD status ;
   DWORD StructSize ;

   if( gb_Tape_Handle != NULL ) {

   sizeof( TAPE_GET_MEDIA_PARAMETERS ) ;

      status = GetTapeParameters( gb_Tape_Handle,
                                  GET_TAPE_MEDIA_INFORMATION,
                                  &StructSize,
                                  &parms ) ;
      // If call to GetTapeParameters is successful, copy data to return

      if( status == NO_ERROR ) {

         *total_low      = parms.Capacity.LowPart ;
         *total_high     = parms.Capacity.HighPart ;
         *freespace_low  = parms.Remaining.LowPart ;
         *freespace_high = parms.Remaining.HighPart ;
         *blk_size       = parms.BlockSize ;
         *part	         = parms.PartitionCount ;
         *write_protect  = parms.WriteProtected ;

      }

      else { DisplayDriverError( GetLastError( ) ) ;
                return TEST_ERROR ;
      }
   }

   return SUCCESS ;

}
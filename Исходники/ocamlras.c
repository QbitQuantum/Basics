value_t c_win32_get_connection_stat (
   value_t conn_lo,
   value_t conn_hi ) 
{
   RAS_STATS		ras_stats;
   CAMLparam2 ( conn_lo, conn_hi );
   CAMLlocal1 ( res );
   
   HRASCONN hRasConn =
      (HRASCONN) MAKELPARAM ( Int_val ( conn_lo ),
			      Int_val ( conn_hi ) );

   ras_stats.dwSize = sizeof ras_stats;
   
   RasGetConnectionStatistics ( hRasConn, &ras_stats );

   res = alloc_tuple ( 14 );

   Store_field ( res, dwBytesXmited, Val_int ( ras_stats.dwBytesXmited ) );
   Store_field ( res, dwBytesRcved, Val_int ( ras_stats.dwBytesRcved ) );
   Store_field ( res, dwFramesXmited, Val_int ( ras_stats.dwFramesXmited ) );
   Store_field ( res, dwFramesRcved, Val_int ( ras_stats.dwFramesRcved ) );
   Store_field ( res, dwCrcErr, Val_int ( ras_stats.dwCrcErr ) );
   Store_field ( res, dwTimeoutErr, Val_int ( ras_stats.dwTimeoutErr ) );
   Store_field ( res, dwAlignmentErr, Val_int ( ras_stats.dwAlignmentErr ) );
   Store_field ( res, dwHardwareOverrunErr, Val_int ( ras_stats.dwHardwareOverrunErr ) );
   Store_field ( res, dwFramingErr, Val_int ( ras_stats.dwFramingErr ) );
   Store_field ( res, dwBufferOverrunErr, Val_int ( ras_stats.dwBufferOverrunErr ) );
   Store_field ( res, dwCompressionRatioIn, Val_int ( ras_stats.dwCompressionRatioIn ) );
   Store_field ( res, dwCompressionRatioOut, Val_int ( ras_stats.dwCompressionRatioOut ) );
   Store_field ( res, dwBps, Val_int ( ras_stats.dwBps ) );
   Store_field ( res, dwConnectDuration, Val_int ( ras_stats.dwConnectDuration ) );
   
   CAMLreturn ( res );
   return 0; /* dummy, to shut down warning */
}
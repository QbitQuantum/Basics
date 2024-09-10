 ErrorCode set_last_error( const char* fmt, va_list args )
 {
   char text[1024];
   VSNPRINTF( text, sizeof(text), fmt, args );
   mLastError = text;
   return MB_SUCCESS;
 }
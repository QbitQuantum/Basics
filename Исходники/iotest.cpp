 virtual void dataerrln( const UnicodeString &message ) {
     char buffer[4000];
     message.extract(0, message.length(), buffer, sizeof(buffer));
     buffer[3999] = 0; /* NULL terminate */
     log_data_err(buffer);
 }
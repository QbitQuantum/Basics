void GrowAxis::format_text( char *text, char *fmt, double value) 
{
  if ( strcmp( fmt, "%1t") == 0) {
    // Hours, minutes and seconds, value in seconds
    int val = (int) nearbyint(value);
    int hours = val / 3600;
    int minutes = (val - hours * 3600) / 60; 
    int seconds = (val - hours * 3600 - minutes * 60); 
    sprintf( text, "%d:%02d:%02d", hours, minutes, seconds);
  }
  else if ( strcmp( fmt, "%2t") == 0) {
    // Hours and minutes, value in seconds
    int val = (int) nearbyint(value);
    int hours = val / 3600;
    int minutes = (val - hours * 3600) / 60; 
    sprintf( text, "%d:%02d", hours, minutes);
  }
  else if ( strcmp( fmt, "%3t") == 0) {
    // Days, hours and minues, value in seconds
    int val = (int) nearbyint(value);
    int days = val / (24 * 3600);
    int hours = (val - days * 24 * 3600) / 3600; 
    int minutes = (val - days * 24 * 3600 - hours * 3600) / 60; 
    sprintf( text, "%d %02d:%02d", days, hours, minutes);
  }
  else if ( strcmp( fmt, "%10t") == 0) {
    // Date
    char timstr[40];
    pwr_tTime t;
    t.tv_sec = (int) nearbyint(value);
    t.tv_nsec = 0;
    
    time_AtoAscii( &t, time_eFormat_NumDateAndTime, timstr, sizeof(timstr));
    timstr[19] = 0;
    strcpy( text, timstr);
  }
  else if ( strcmp( fmt, "%11t") == 0) {
    // Date, no seconds
    char timstr[40];
    pwr_tTime t;
    t.tv_sec = (int) nearbyint(value);
    t.tv_nsec = 0;
    
    time_AtoAscii( &t, time_eFormat_NumDateAndTime, timstr, sizeof(timstr));
    timstr[16] = 0;
    strcpy( text, timstr);
  }
  else {
    if ( fabs(value) < FLT_EPSILON)
      value = 0;
    sprintf( text, fmt, value);
  }
}
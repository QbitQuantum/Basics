String::String( const unsigned long value, const int base )
{
  char buf[33];   
  ultoa(value, buf, 10);
  getBuffer( _length = strlen(buf) );
  if ( _buffer != NULL )
    strcpy( _buffer, buf );
}
size_t Record::NumberOfFields() const
{
  unsigned int x = MsiRecordGetFieldCount( handle ) ;
  if ( x == 0xFFFFFFFF )
  {
    throw WindowsApiError( "MsiRecordGetFieldCount", x, "invalid handle" ) ;
  }
  return x ;
}
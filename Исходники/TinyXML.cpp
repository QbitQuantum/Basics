// <-- Strange class for a bug fix. Search for STL_STRING_BUG
TiXmlBase::StringToBuffer::StringToBuffer( const TIXML_STRING& str )
  : buffer(new char[str.length() + 1]) {
  if ( buffer ) {
    strcpy( buffer, str.c_str() );
  }
}
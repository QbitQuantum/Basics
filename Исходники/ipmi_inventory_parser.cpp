SaErrorT
cIpmiInventoryAreaBoard::ParseFruArea( const unsigned char *data, unsigned int size )
{
  cIpmiInventoryField *iif;
  SaErrorT rv;
  unsigned int area_size = *(data+1)*8;

  if ( area_size > size )
  {
       stdlog << "wrong board area length !\n";
       return SA_ERR_HPI_INVALID_DATA;
  }

  if ( IpmiChecksum( data, *(data+1)*8 ) )
     {
       stdlog << "wrong board area checksum !\n";
       return SA_ERR_HPI_INVALID_DATA;
     }

  data += 2;
  size -= 2;

  if ( size < 4 )
       return SA_ERR_HPI_INVALID_DATA;

  // Skip Language
  data++;
  size--;

  time_t mfg_time = (SaHpiTimeT)data[0] + (SaHpiTimeT)data[1] * 256 + (SaHpiTimeT)data[2] * 65536;

  size -= 3;
  data += 3;

  mfg_time *= 60;

  // create date offset
  struct tm tmt;

  tmt.tm_sec  = 0;
  tmt.tm_min  = 0;
  tmt.tm_hour = 0;
  tmt.tm_mday = 1;
  tmt.tm_mon  = 0;
  tmt.tm_year = 96;
  tmt.tm_isdst = 0;

  mfg_time += mktime( &tmt );

  char str[80];
  IpmiDateTimeToString( mfg_time, str );

  iif = new cIpmiInventoryField( m_area_header.AreaId, m_field_id++, SAHPI_IDR_FIELDTYPE_MFG_DATETIME);

  m_field_array.Add( iif );

  iif->SetAscii ( str, strlen( str ) + 1 );

  for ( unsigned int i = 0; i < sizeof(BoardInfoAreaFields)/sizeof(BoardInfoAreaFields[0]); i++ )
  {
      iif = new cIpmiInventoryField( m_area_header.AreaId, m_field_id++, BoardInfoAreaFields[i]);

      m_field_array.Add( iif );

      rv = iif->ReadTextBuffer( data, size );

      if ( rv != SA_OK )
          return rv;
  }

  while( true )
     {
       if ( size < 1 )
	    return SA_ERR_HPI_INVALID_DATA;

       if ( *data == 0xc1 )
	    break;

       iif = new cIpmiInventoryField( m_area_header.AreaId, m_field_id++, SAHPI_IDR_FIELDTYPE_CUSTOM);

       m_field_array.Add( iif );

       rv = iif->ReadTextBuffer( data, size );

       if ( rv != SA_OK )
        return rv;
     }

  m_area_header.NumFields = m_field_array.Num();

  return SA_OK;
}
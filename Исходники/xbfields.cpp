/*!
*/
xbShort xbDbf::PutField(const xbShort FieldNo, const char *buf) {
  xbShort len, i;
  char * startpos;
  char * tp;           /*  target pointer */
  const char * sp;        /*  source pointer */

  if( FieldNo < 0 || FieldNo >= NoOfFields )
    return XB_INVALID_FIELDNO;

  if( DbfStatus != XB_UPDATED ){
    DbfStatus = XB_UPDATED;
    memcpy( RecBuf2, RecBuf, RecordLen );
  }
  
  if( SchemaPtr[FieldNo].Type == 'L' && !ValidLogicalData( buf ))
    return XB_INVALID_DATA;

  else if(( SchemaPtr[FieldNo].Type == 'F' || SchemaPtr[FieldNo].Type == 'N' )
       && !ValidNumericData( buf )) 
    return XB_INVALID_DATA;

  else if( SchemaPtr[FieldNo].Type == 'D' ){
    xbDate d;
    if( !d.DateIsValid( buf ))
      return XB_INVALID_DATA;
  }

  if( SchemaPtr[FieldNo].Type == 'C' && SchemaPtr[FieldNo].NoOfDecs > 0 )
    memset( SchemaPtr[FieldNo].Address, 0x20, SchemaPtr[FieldNo].LongFieldLen );
  else
    memset( SchemaPtr[FieldNo].Address, 0x20, SchemaPtr[FieldNo].FieldLen );

  len = strlen( buf );

  if(( SchemaPtr[FieldNo].Type == 'N' || SchemaPtr[FieldNo].Type == 'F')
       && len > SchemaPtr[FieldNo].FieldLen )
    return XB_INVALID_DATA;
  else if( len > SchemaPtr[FieldNo].FieldLen )
    len = SchemaPtr[FieldNo].FieldLen;

  if( SchemaPtr[FieldNo].Type == 'F' || SchemaPtr[FieldNo].Type == 'N' 
      || SchemaPtr[FieldNo].Type == 'M') {

    const char *sdp = strchr( buf, '.' ); /*  source decimal point */
    len = 0;
    sp =buf;
    while( *sp && *sp != '.' ) { len++; sp++; }
    if( SchemaPtr[FieldNo].NoOfDecs > 0 ){
      /* do the right of decimal area */
      tp = SchemaPtr[FieldNo].Address;
      tp += SchemaPtr[FieldNo].FieldLen - SchemaPtr[FieldNo].NoOfDecs - 1;
      *tp++ = '.';
      sp = sdp;
      if( sp ) sp++;
      for( i = 0; i < SchemaPtr[FieldNo].NoOfDecs; i++ )
        if( sp && *sp ) *tp++ = *sp++; else *tp++ = '0'; 

      startpos= SchemaPtr[FieldNo].Address +
                SchemaPtr[FieldNo].FieldLen -
                SchemaPtr[FieldNo].NoOfDecs - len - 1; 
    }
    else
    {
      startpos=SchemaPtr[FieldNo].Address+SchemaPtr[FieldNo].FieldLen-len; 
    }
  }
  else
    startpos = SchemaPtr[FieldNo].Address;

  memcpy( startpos, buf, len );
  return 0;
}
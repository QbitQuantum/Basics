//
// MIB_odoms_lmset
//    Perform the necessary actions to set an entry in the Other Domain Table.
//
// Notes:
//
// Return Codes:
//
// Error Codes:
//    None.
//
UINT MIB_odoms_lmset(
        IN AsnObjectIdentifier *Index,
        IN UINT Field,
        IN AsnAny *Value
        )

{
LPBYTE bufptr = NULL;
WKSTA_USER_INFO_1101 ODom;
LPBYTE Temp;
UINT   Entry;
UINT   I;
UINT   ErrStat = SNMP_ERRORSTATUS_NOERROR;
#ifdef UNICODE
LPWSTR unitemp ;
#endif


   // Must make sure the table is in memory
   if ( SNMPAPI_ERROR == MIB_odoms_lmget() )
      {
      ErrStat = SNMP_ERRORSTATUS_GENERR;
      goto Exit;
      }

   // See if match in table
   if ( MIB_TBL_POS_FOUND == MIB_odoms_match(Index, &Entry) )
      {
      // If empty string then delete entry
      if ( Value->asnValue.string.length == 0 )
         {
         // Alloc memory for buffer
         bufptr = SnmpUtilMemAlloc( DNLEN * sizeof(char) *
                          (MIB_DomOtherDomainTable.Len-1) +
                          MIB_DomOtherDomainTable.Len-1 );

         // Create the other domain string
         Temp = bufptr;
         for ( I=0;I < MIB_DomOtherDomainTable.Len;I++ )
            {
            if ( I+1 != Entry )
               {
               memcpy( Temp,
                       MIB_DomOtherDomainTable.Table[I].domOtherName.stream,
                       MIB_DomOtherDomainTable.Table[I].domOtherName.length );
               Temp[MIB_DomOtherDomainTable.Table[I].domOtherName.length] = ' ';
               Temp += MIB_DomOtherDomainTable.Table[I].domOtherName.length + 1;
               }
            }
         *(Temp-1) = '\0';
         }
      else
         {
         // Cannot modify the domain entries, so bad value
         ErrStat = SNMP_ERRORSTATUS_BADVALUE;
         goto Exit;
         }
      }
   else
      {
      // Check for addition of NULL string, bad value
      if ( Value->asnValue.string.length == 0 )
         {
         ErrStat = SNMP_ERRORSTATUS_BADVALUE;
         goto Exit;
         }

      //
      // Entry doesn't exist so add it to the list
      //

      // Alloc memory for buffer
      bufptr = SnmpUtilMemAlloc( DNLEN * sizeof(char) *
                       (MIB_DomOtherDomainTable.Len+1) +
                       MIB_DomOtherDomainTable.Len+1 );

      // Create the other domain string
      Temp = bufptr;
      for ( I=0;I < MIB_DomOtherDomainTable.Len;I++ )
         {
         memcpy( Temp, MIB_DomOtherDomainTable.Table[I].domOtherName.stream,
                 MIB_DomOtherDomainTable.Table[I].domOtherName.length );
         Temp[MIB_DomOtherDomainTable.Table[I].domOtherName.length] = ' ';
         Temp += MIB_DomOtherDomainTable.Table[I].domOtherName.length + 1;
         }

      // Add new entry
      memcpy( Temp, Value->asnValue.string.stream,
                    Value->asnValue.string.length );

      // Add NULL terminator
      Temp[Value->asnValue.string.length] = '\0';
      }

   // Set table and check return codes
   #ifdef UNICODE
   SnmpUtilAnsiToUnicode(         &unitemp,
                                bufptr,
                                TRUE );
   ODom.wkui1101_oth_domains = unitemp;
   #else
   ODom.wkui1101_oth_domains = bufptr;
   #endif
#if 0
   if ( NERR_Success == NetWkstaUserSetInfo(NULL, 1101, (LPBYTE)&ODom, NULL) )
      {
      // Make cache be reloaded next time
      cache_table[C_ODOM_TABLE].bufptr = NULL;
      }
   else
      {
      ErrStat = SNMP_ERRORSTATUS_GENERR;
      }
#else
   ErrStat = SNMP_ERRORSTATUS_GENERR;
#endif

Exit:
   SnmpUtilMemFree( bufptr );

   return ErrStat;
} // MIB_odoms_lmset
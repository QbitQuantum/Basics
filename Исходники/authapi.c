//
// SnmpSvcEncodeMessage
//    Encodes the specified message and message type (RFC 1157 or Mgmt Com)
//    into a buffer.
//
// Notes:
//    If an error occurs, the buffer is freed and set to NULL.
//
//    The buffer information will be initialized by this routine.
//
//    It will be the responsibility of the calling routine to free the buffer
//    if the encoding is successful.
//
// Return Codes:
//    SNMPAPI_NOERROR
//    SNMPAPI_ERROR
//
// Error Codes:
//    SNMP_AUTHAPI_INVALID_MSG_TYPE
//
SNMPAPI 
SNMP_FUNC_TYPE
SnmpSvcEncodeMessage(
           IN UINT snmpAuthType,        // Type of message to encode
           IN SnmpMgmtCom *snmpMgmtCom, // Message to encode
           IN OUT BYTE **pBuffer,       // Buffer to accept encoded message
           IN OUT UINT *nLength         // Length of buffer
           )

{
RFC1157Message message;
SNMPAPI        nResult;


   // Initialize buffer information
   *pBuffer = NULL;
   *nLength = 0;

   // Encode for particular message type
   switch ( snmpAuthType )
      {
      case ASN_RFCxxxx_SNMPMGMTCOM:
         // Encode SnmpMgmtCom's parts
         if ( SNMPAPI_ERROR ==
	      (nResult = SnmpEncodeMgmtCom(snmpMgmtCom, pBuffer, nLength)) )
            {
            goto Exit;
            }

         // Encode SnmpAuthMsg parts
         if ( SNMPAPI_ERROR ==
	      (nResult = SnmpEncodeAuthMsg(&snmpMgmtCom->srcParty,
	                                   pBuffer, nLength)) )
            {
            goto Exit;
            }

         // Encode Priv Msg parts
         if ( SNMPAPI_ERROR ==
              (nResult = SnmpEncodePrivMsg(&snmpMgmtCom->dstParty,
	                                   pBuffer, nLength)) )
            {
            goto Exit;
            }

	 // Reverse the buffer
	 SnmpSvcBufRevInPlace( *pBuffer, *nLength );
         break;

      case ASN_SEQUENCE:
         // convert RFC 1157 Message to a RFC xxxx SnmpMgmtCom
         if ( SNMPAPI_ERROR ==
              (nResult = SnmpMgmtComToRFC1157Message(&message, snmpMgmtCom)) )
            {
            goto Exit;
            }

         // Encode RFC 1157 Message
	 nResult = SnmpEncodeRFC1157Message( &message, pBuffer, nLength );
         break;

      default:
         // Message type unknown - error
	 nResult = SNMPAPI_ERROR;

	 SetLastError( SNMP_AUTHAPI_INVALID_MSG_TYPE );
      }

Exit:
   if ( nResult == SNMPAPI_ERROR )
      {
      SnmpUtilMemFree( *pBuffer );

      *pBuffer = NULL;
      *nLength = 0;
      }

   return nResult;
} // SnmpSvcEncodeMessage
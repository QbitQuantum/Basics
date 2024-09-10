//
// MIB_sess_copyfromtable
//    Copy requested data from table structure into Var Bind.
//
// Notes:
//
// Return Codes:
//    None.
//
// Error Codes:
//    None.
//
UINT MIB_sess_copyfromtable(
        IN UINT Entry,
        IN UINT Field,
        OUT RFC1157VarBind *VarBind
        )

{
UINT ErrStat;


   // Get the requested field and save in var bind
   switch( Field )
      {
      case SESS_CLIENT_FIELD:
         // Alloc space for string
         VarBind->value.asnValue.string.stream = SnmpUtilMemAlloc( sizeof(char)
                       * MIB_SessionTable.Table[Entry].svSesClientName.length );
         if ( VarBind->value.asnValue.string.stream == NULL )
            {
            ErrStat = SNMP_ERRORSTATUS_GENERR;
            goto Exit;
            }

         // Copy string into return position
         memcpy( VarBind->value.asnValue.string.stream,
                       MIB_SessionTable.Table[Entry].svSesClientName.stream,
                       MIB_SessionTable.Table[Entry].svSesClientName.length );

         // Set string length
         VarBind->value.asnValue.string.length =
                          MIB_SessionTable.Table[Entry].svSesClientName.length;
         VarBind->value.asnValue.string.dynamic = TRUE;

         // Set type of var bind
         VarBind->value.asnType = ASN_RFC1213_DISPSTRING;
         break;

      case SESS_USER_FIELD:
         // Alloc space for string
         VarBind->value.asnValue.string.stream = SnmpUtilMemAlloc( sizeof(char)
                       * MIB_SessionTable.Table[Entry].svSesUserName.length );
         if ( VarBind->value.asnValue.string.stream == NULL )
            {
            ErrStat = SNMP_ERRORSTATUS_GENERR;
            goto Exit;
            }

         // Copy string into return position
         memcpy( VarBind->value.asnValue.string.stream,
                       MIB_SessionTable.Table[Entry].svSesUserName.stream,
                       MIB_SessionTable.Table[Entry].svSesUserName.length );

         // Set string length
         VarBind->value.asnValue.string.length =
                          MIB_SessionTable.Table[Entry].svSesUserName.length;
         VarBind->value.asnValue.string.dynamic = TRUE;

         // Set type of var bind
         VarBind->value.asnType = ASN_RFC1213_DISPSTRING;
         break;

      case SESS_NUMCONS_FIELD:
         VarBind->value.asnValue.number =
                               MIB_SessionTable.Table[Entry].svSesNumConns;
         VarBind->value.asnType = ASN_INTEGER;
         break;

      case SESS_NUMOPENS_FIELD:
         VarBind->value.asnValue.number =
                               MIB_SessionTable.Table[Entry].svSesNumOpens;
         VarBind->value.asnType = ASN_INTEGER;
         break;

      case SESS_TIME_FIELD:
         VarBind->value.asnValue.number =
                               MIB_SessionTable.Table[Entry].svSesTime;
         VarBind->value.asnType = ASN_RFC1155_COUNTER;
         break;

      case SESS_IDLETIME_FIELD:
         VarBind->value.asnValue.number =
                               MIB_SessionTable.Table[Entry].svSesIdleTime;
         VarBind->value.asnType = ASN_RFC1155_COUNTER;
         break;

      case SESS_CLIENTTYPE_FIELD:
         VarBind->value.asnValue.number =
                               MIB_SessionTable.Table[Entry].svSesClientType;
         VarBind->value.asnType = ASN_INTEGER;
         break;

      case SESS_STATE_FIELD:
         VarBind->value.asnValue.number =
                               MIB_SessionTable.Table[Entry].svSesState;
         VarBind->value.asnType = ASN_INTEGER;
         break;

      default:
         SNMPDBG(( SNMP_LOG_TRACE, "LMMIB2: Internal Error Session Table\n" ));
         ErrStat = SNMP_ERRORSTATUS_GENERR;

         goto Exit;
      }

   ErrStat = SNMP_ERRORSTATUS_NOERROR;

Exit:
   return ErrStat;
} // MIB_sess_copyfromtable
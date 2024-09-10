//
// MIB_dlog_lmget
//    Retrieve dlogion table information from Lan Manager.
//    If not cached, sort it and then
//    cache it.
//
// Notes:
//
// Return Codes:
//    SNMPAPI_NOERROR
//    SNMPAPI_ERROR
//
// Error Codes:
//    None.
//
SNMPAPI MIB_dlogons_lmget(
	   )

{
SNMPAPI nResult = SNMPAPI_NOERROR;
#if 0
DWORD entriesread;
DWORD totalentries;
LPBYTE bufptr;
unsigned lmCode;
unsigned i;
SHARE_INFO_2 *DataTable;
DOM_LOGON_ENTRY *MIB_DomLogonTableElement ;
int First_of_this_block;
DWORD resumehandle=0;

   //
   //
   // If cached, return piece of info.
   //
   //

   //
   //
   // Do network call to gather information and put it in a nice array
   //
   //

   // free the old table  LOOK OUT!!
   	
   // init the length
   MIB_DomLogonTable.Len = 0;
   First_of_this_block = 0;
   	
   do {  //  as long as there is more data to process

	lmCode =
    	NetShareEnum(NULL,          // local server
                2,                  // level 2,
                &bufptr,            // data structure to return
                MAX_PREFERRED_LENGTH,
                &entriesread,
                &totalentries,
                &resumehandle       //  resume handle
                );

        //
        // Filter out all the Admin shares (name ending with $).
        //
        AdminFilter(2,&entriesread,bufptr);


    DataTable = (SHARE_INFO_2 *) bufptr ;

    if((NERR_Success == lmCode) || (ERROR_MORE_DATA == lmCode))
    	{  // valid so process it, otherwise error
   	
   	if(0 == MIB_DomLogonTable.Len) {  // 1st time, alloc the whole table
   		// alloc the table space
                MIB_DomLogonTable.Table = SnmpUtilMemAlloc(totalentries *
   						sizeof(DOM_LOGON_ENTRY) );
   	}
	
	MIB_DomLogonTableElement = MIB_DomLogonTable.Table + First_of_this_block ;
	
   	for(i=0; i<entriesread; i++) {  // once for each entry in the buffer
   		// increment the entry number
   		
   		MIB_DomLogonTable.Len ++;
   		
   		// Stuff the data into each item in the table
   		
   		// dloge name
                MIB_DomLogonTableElement->svShareName.stream = SnmpUtilMemAlloc (
   				strlen( DataTable->shi2_netname ) ) ;
   		MIB_DomLogonTableElement->svShareName.length =
   				strlen( DataTable->shi2_netname ) ;
		MIB_DomLogonTableElement->svShareName.dynamic = TRUE;
   		memcpy(	MIB_DomLogonTableElement->svShareName.stream,
   			DataTable->shi2_netname,
   			strlen( DataTable->shi2_netname ) ) ;
   		
   		// Share Path
                MIB_DomLogonTableElement->svSharePath.stream = SnmpUtilMemAlloc (
   				strlen( DataTable->shi2_path ) ) ;
   		MIB_DomLogonTableElement->svSharePath.length =
   				strlen( DataTable->shi2_path ) ;
		MIB_DomLogonTableElement->svSharePath.dynamic = TRUE;
   		memcpy(	MIB_DomLogonTableElement->svSharePath.stream,
   			DataTable->shi2_path,
   			strlen( DataTable->shi2_path ) ) ;
   		
   		
   		// Share Comment/Remark
                MIB_DomLogonTableElement->svShareComment.stream = SnmpUtilMemAlloc (
   				strlen( DataTable->shi2_remark ) ) ;
   		MIB_DomLogonTableElement->svShareComment.length =
   				strlen( DataTable->shi2_remark ) ;
		MIB_DomLogonTableElement->svShareComment.dynamic = TRUE;
   		memcpy(	MIB_DomLogonTableElement->svShareComment.stream,
   			DataTable->shi2_remark,
   			strlen( DataTable->shi2_remark ) ) ;
   		
   		
   		DataTable ++ ;  // advance pointer to next dlog entry in buffer
		MIB_DomLogonTableElement ++ ;  // and table entry
		
   	} // for each entry in the data table
   	
   	// indicate where to start adding on next pass, if any
   	First_of_this_block = i ;
   	
       	} // if data is valid to process
    else
       {
       // Signal error
       nResult = SNMPAPI_ERROR;
       goto Exit;
       }

    } while (ERROR_MORE_DATA == lmCode) ;

    // iterate over the table populating the Oid field
    build_dlog_entry_oids();

   // Sort the table information using MSC QuickSort routine
   qsort( &MIB_DomLogonTable.Table[0], MIB_DomLogonTable.Len,
          sizeof(DOM_LOGON_ENTRY), dlog_entry_cmp );

   //
   //
   // Cache table
   //
   //

   //
   //
   // Return piece of information requested
   //
   //

Exit:
#endif
   return nResult;

} // MIB_dlog_get
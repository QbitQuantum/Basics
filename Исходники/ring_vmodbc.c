void ring_vm_odbc_drivers ( void *pPointer )
{
	ring_odbc *pODBC  ;
	SQLCHAR driver[256]  ;
	SQLCHAR attr[256]  ;
	SQLSMALLINT driver_ret  ;
	SQLSMALLINT attr_ret  ;
	SQLUSMALLINT direction  ;
	List *pList  ;
	String *pString  ;
	if ( RING_API_PARACOUNT != 1 ) {
		RING_API_ERROR(RING_API_MISS1PARA);
		return ;
	}
	if ( RING_API_ISPOINTER(1) ) {
		pODBC = (ring_odbc *) RING_API_GETCPOINTER(1,RING_VM_POINTER_ODBC) ;
		if ( pODBC == NULL ) {
			return ;
		}
		pList = RING_API_NEWLIST ;
		direction = SQL_FETCH_FIRST ;
		while ( SQL_SUCCEEDED(SQLDrivers(pODBC->env, direction, driver, sizeof(driver), &driver_ret,attr, sizeof(attr), &attr_ret)) ) {
			direction = SQL_FETCH_NEXT ;
			pString = ring_string_new((char *) driver);
			ring_string_add(pString," - ");
			ring_string_add(pString, (char *) attr);
			ring_list_addstring(pList,ring_string_get(pString));
			ring_string_delete(pString);
		}
		RING_API_RETLIST(pList);
	} else {
		RING_API_ERROR(RING_API_BADPARATYPE);
	}
}
//Protocol chain is list of integers "0".."n", with network protocol named "p"
INT_PTR Proto_CallContactService(WPARAM wParam,LPARAM lParam)
//note that this is ChainSend() too, due to a quirk of function definitions
{
	CCSDATA *ccs=(CCSDATA*)lParam;
	int i;
	char str[10];
	DBVARIANT dbv;
	INT_PTR ret;
	PROTOACCOUNT* pa;

	if ( wParam == (WPARAM)(-1))
		return 1;

	for ( i = wParam;; i++ ) {
		_itoa( i, str, 10 );
		if ( DBGetContactSettingString( ccs->hContact, "_Filter", str, &dbv ))
			break;

		if (( ret = CallProtoService( dbv.pszVal, ccs->szProtoService, i+1, lParam )) != CALLSERVICE_NOTFOUND ) {
			//chain was started, exit
			mir_free( dbv.pszVal );
			return ret;
		}
		mir_free( dbv.pszVal );
	}
	if ( DBGetContactSettingString( ccs->hContact, "Protocol", "p", &dbv ))
		return 1;

	pa = Proto_GetAccount( dbv.pszVal );
	if ( pa == NULL || pa->ppro == NULL )
		ret = 1;
	else {
		if ( pa->bOldProto )
			ret = CallProtoServiceInt( ccs->hContact, dbv.pszVal, ccs->szProtoService, (WPARAM)(-1), ( LPARAM)ccs );
		else
			ret = CallProtoServiceInt( ccs->hContact, dbv.pszVal, ccs->szProtoService, ccs->wParam, ccs->lParam );
		if ( ret == CALLSERVICE_NOTFOUND )
			ret = 1;
	}

	mir_free(dbv.pszVal);
	return ret;
}
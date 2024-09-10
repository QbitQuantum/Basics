INT unit_useMenu(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
	CDebug cDbg("unit useMenu");

	myUnit* lpUnit = (myUnit*)JS_GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	if(argc < 1 || !JSVAL_IS_INT(argv[0]))
		return JS_TRUE;

	if(!lpUnit || IsBadReadPtr(lpUnit, sizeof(myUnit)) || lpUnit->_dwPrivateType != PRIVATE_UNIT)
		return JS_TRUE;

	UnitAny* pUnit = D2CLIENT_FindUnit(lpUnit->dwUnitId, lpUnit->dwType);

	if(!pUnit)
		return JS_TRUE;

	*rval = BOOLEAN_TO_JSVAL(ClickNPCMenu(pUnit->dwTxtFileNo, JSVAL_TO_INT(argv[0])));

	return JS_TRUE;
}
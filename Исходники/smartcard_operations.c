static UINT32 smartcard_GetAttrib_Call(SMARTCARD_DEVICE* smartcard, SMARTCARD_OPERATION* operation, GetAttrib_Call* call)
{
	LONG status;
	DWORD cbAttrLen;
	GetAttrib_Return ret;
	IRP* irp = operation->irp;

	ret.pbAttr = NULL;

	if (call->fpbAttrIsNULL)
		call->cbAttrLen = 0;

	if (call->cbAttrLen)
		ret.pbAttr = (BYTE*) malloc(call->cbAttrLen);

	cbAttrLen = call->cbAttrLen;

	status = ret.ReturnCode = SCardGetAttrib(operation->hCard, call->dwAttrId, ret.pbAttr, &cbAttrLen);

	ret.cbAttrLen = cbAttrLen;

	smartcard_trace_get_attrib_return(smartcard, &ret, call->dwAttrId);

	if (ret.ReturnCode)
	{
		WLog_Print(smartcard->log, WLOG_WARN,
				"SCardGetAttrib: %s (0x%08X) cbAttrLen: %d\n",
				SCardGetAttributeString(call->dwAttrId), call->dwAttrId, call->cbAttrLen);

		Stream_Zero(irp->output, 256);
		return ret.ReturnCode;
	}

	status = smartcard_pack_get_attrib_return(smartcard, irp->output, &ret);

	if (status != SCARD_S_SUCCESS)
		return status;

	free(ret.pbAttr);

	return ret.ReturnCode;
}
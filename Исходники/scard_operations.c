static uint32 handle_GetAttrib(IRP* irp)
{
	LONG rv;
	SCARDHANDLE hCard;
	DWORD dwAttrId = 0, dwAttrLen = 0;
	DWORD attrLen = 0;
	uint8* pbAttr = NULL;

	stream_seek(irp->input, 0x20);
	stream_read_uint32(irp->input, dwAttrId);
	stream_seek(irp->input, 0x4);
	stream_read_uint32(irp->input, dwAttrLen);
	stream_seek(irp->input, 0xC);
	stream_read_uint32(irp->input, hCard);

	DEBUG_SCARD("hcard: 0x%08x, attrib: 0x%08x (%d bytes)\n",
		(unsigned) hCard, (unsigned) dwAttrId, (int) dwAttrLen);

#ifdef SCARD_AUTOALLOCATE
	if(dwAttrLen == 0)
	{
		attrLen = 0;
	}
	else
	{
		attrLen = SCARD_AUTOALLOCATE;
	}
#endif

	rv = SCardGetAttrib(hCard, dwAttrId, attrLen == 0 ? NULL : (uint8*) &pbAttr, &attrLen);
	if( rv != SCARD_S_SUCCESS ) {
#ifdef SCARD_AUTOALLOCATE
		if(dwAttrLen == 0)
		{
			attrLen = 0;
		}
		else
		{
			attrLen = SCARD_AUTOALLOCATE;
		}
#endif
	}

	if(dwAttrId == SCARD_ATTR_DEVICE_FRIENDLY_NAME_A && rv == SCARD_E_UNSUPPORTED_FEATURE)
	{
		rv = SCardGetAttrib(hCard, SCARD_ATTR_DEVICE_FRIENDLY_NAME_W,
			attrLen == 0 ? NULL : (uint8*) &pbAttr, &attrLen);
		if( rv != SCARD_S_SUCCESS ) {
#ifdef SCARD_AUTOALLOCATE
			if(dwAttrLen == 0)
			{
				attrLen = 0;
			}
			else
			{
				attrLen = SCARD_AUTOALLOCATE;
			}
#endif
		}
	}
	if(dwAttrId == SCARD_ATTR_DEVICE_FRIENDLY_NAME_W && rv == SCARD_E_UNSUPPORTED_FEATURE)
	{
		rv = SCardGetAttrib(hCard, SCARD_ATTR_DEVICE_FRIENDLY_NAME_A,
			attrLen == 0 ? NULL : (uint8*) &pbAttr, &attrLen);
		if( rv != SCARD_S_SUCCESS ) {
#ifdef SCARD_AUTOALLOCATE
			if(dwAttrLen == 0)
			{
				attrLen = 0;
			}
			else
			{
				attrLen = SCARD_AUTOALLOCATE;
			}
#endif
		}
	}
	if(attrLen > dwAttrLen && pbAttr != NULL)
	{
		rv = SCARD_E_INSUFFICIENT_BUFFER;
	}
	dwAttrLen = attrLen;

	if (rv != SCARD_S_SUCCESS)
	{
		DEBUG_SCARD("Failure: %s (0x%08x)", pcsc_stringify_error(rv), (unsigned int) rv);
		free(pbAttr);
		return sc_output_return(irp, rv);
	}
	else
	{
		DEBUG_SCARD("Success (%d bytes)", (int) dwAttrLen);

		stream_write_uint32(irp->output, dwAttrLen);
		stream_write_uint32(irp->output, 0x00000200);
		stream_write_uint32(irp->output, dwAttrLen);

		if (!pbAttr)
		{
			stream_write_zero(irp->output, dwAttrLen);
		}
		else
		{
			stream_write(irp->output, pbAttr, dwAttrLen);
		}
		sc_output_repos(irp, dwAttrLen);
		/* align to multiple of 4 */
		stream_write_uint32(irp->output, 0);
	}
	sc_output_alignment(irp, 8);

	xfree(pbAttr);

	return rv;
}
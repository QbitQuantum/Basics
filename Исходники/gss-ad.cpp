OM_uint32  gss_accept_sec_context (
        OM_uint32 *minor_status,
        gss_ctx_id_t *context_handle,
        gss_cred_id_t verifier_cred_handle,
        gss_buffer_t input_token,
        gss_channel_bindings_t input_chan_bindings,
        gss_name_t *src_name,
        gss_OID *actual_mech_type,
        gss_buffer_t output_token,
        OM_uint32 *ret_flags,
        OM_uint32 *time_rec,
        gss_cred_id_t *delegated_cred_handle)
{
	gss_cred_id_t credhandle={0};
	gss_ctx_id_t *pctx;
	DWORD cbmaxtoken;
	PVOID pbuf;

	// Get max token size
	PSecPkgInfo pspi = NULL;
	QuerySecurityPackageInfoA("Kerberos", &pspi);
	cbmaxtoken = pspi->cbMaxToken;
	FreeContextBuffer(pspi);

	pbuf = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (cbmaxtoken<12000)?12000:cbmaxtoken);
	SecBuffer InputBuf[1] = {input_token->length,SECBUFFER_TOKEN,input_token->value};
	SecBuffer OutputBuf[1] = {cbmaxtoken,SECBUFFER_TOKEN,pbuf};
	SecBufferDesc InBuffer[1] = {SECBUFFER_VERSION, 1, InputBuf};
	SecBufferDesc OutBuffer[1] = {SECBUFFER_VERSION, 1, OutputBuf};
	OM_uint32 ret;
	TimeStamp tr;
	unsigned long rf;

	if(context_handle->dwLower==0 && context_handle->dwUpper==0)
		pctx = NULL;
	else
		pctx = context_handle;

	ret = AcceptSecurityContext(&verifier_cred_handle, pctx, InBuffer, ASC_REQ_MUTUAL_AUTH,
				SECURITY_NETWORK_DREP, context_handle, OutBuffer, &rf, &tr);
	output_token->length = OutputBuf[0].cbBuffer;
	output_token->value = malloc((OutputBuf[0].cbBuffer)+100);
	if (output_token->value!=NULL)
		memcpy(output_token->value,OutputBuf[0].pvBuffer,OutputBuf[0].cbBuffer);
	HeapFree(GetProcessHeap(), 0, pbuf);

	if(!ret)
	{
		SecPkgContext_NamesA names = {0};
		QueryContextAttributes(context_handle, SECPKG_ATTR_NAMES, &names);
		*src_name = strdup(names.sUserName);
		FreeContextBuffer(&names);
	}

	*minor_status = 0;
	if(time_rec)
		*time_rec=tr.LowPart;
	if(ret_flags)
		*ret_flags=rf;
	return ret;
}
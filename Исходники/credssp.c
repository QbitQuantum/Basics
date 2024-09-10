int credssp_client_authenticate(rdpCredssp* credssp)
{
	uint32 cbMaxLen;
	uint32 fContextReq;
	uint32 pfContextAttr;
	SECURITY_STATUS status;
	CRED_HANDLE credentials;
	SEC_TIMESTAMP expiration;
	SEC_PKG_INFO* pPackageInfo;
	SEC_AUTH_IDENTITY identity;
	SEC_BUFFER* p_sec_buffer;
	SEC_BUFFER input_sec_buffer;
	SEC_BUFFER output_sec_buffer;
	SEC_BUFFER_DESC input_sec_buffer_desc;
	SEC_BUFFER_DESC output_sec_buffer_desc;
	boolean have_context;
	boolean have_input_buffer;
	boolean have_pub_key_auth;
	rdpSettings* settings = credssp->settings;

	sspi_GlobalInit();

	if (credssp_ntlmssp_client_init(credssp) == 0)
		return 0;

	credssp->table = InitSecurityInterface();

	status = QuerySecurityPackageInfo(NTLM_PACKAGE_NAME, &pPackageInfo);

	if (status != SEC_E_OK)
	{
		printf("QuerySecurityPackageInfo status: 0x%08X\n", status);
		return 0;
	}

	cbMaxLen = pPackageInfo->cbMaxToken;

	identity.User = (uint16*) xstrdup(settings->username);
	identity.UserLength = strlen(settings->username);

	if (settings->domain)
	{
		identity.Domain = (uint16*) xstrdup(settings->domain);
		identity.DomainLength = strlen(settings->domain);
	}
	else
	{
		identity.Domain = (uint16*) NULL;
		identity.DomainLength = 0;
	}

	identity.Password = (uint16*) xstrdup(settings->password);
	identity.PasswordLength = strlen(settings->password);

	identity.Flags = SEC_AUTH_IDENTITY_ANSI;

	status = credssp->table->AcquireCredentialsHandle(NULL, NTLM_PACKAGE_NAME,
			SECPKG_CRED_OUTBOUND, NULL, &identity, NULL, NULL, &credentials, &expiration);

	if (status != SEC_E_OK)
	{
		printf("AcquireCredentialsHandle status: 0x%08X\n", status);
		return 0;
	}

	have_context = false;
	have_input_buffer = false;
	have_pub_key_auth = false;
	memset(&input_sec_buffer, 0, sizeof(SEC_BUFFER));
	memset(&output_sec_buffer, 0, sizeof(SEC_BUFFER));
	memset(&credssp->ContextSizes, 0, sizeof(SEC_PKG_CONTEXT_SIZES));

	fContextReq = ISC_REQ_REPLAY_DETECT | ISC_REQ_SEQUENCE_DETECT |
			ISC_REQ_CONFIDENTIALITY | ISC_REQ_DELEGATE;

	while (true)
	{
		output_sec_buffer_desc.ulVersion = SECBUFFER_VERSION;
		output_sec_buffer_desc.cBuffers = 1;
		output_sec_buffer_desc.pBuffers = &output_sec_buffer;
		output_sec_buffer.BufferType = SECBUFFER_TOKEN;
		output_sec_buffer.cbBuffer = cbMaxLen;
		output_sec_buffer.pvBuffer = xmalloc(output_sec_buffer.cbBuffer);

		status = credssp->table->InitializeSecurityContext(&credentials,
				(have_context) ? &credssp->context : NULL,
				NULL, fContextReq, 0, SECURITY_NATIVE_DREP,
				(have_input_buffer) ? &input_sec_buffer_desc : NULL,
				0, &credssp->context, &output_sec_buffer_desc, &pfContextAttr, &expiration);

		if (input_sec_buffer.pvBuffer != NULL)
		{
			xfree(input_sec_buffer.pvBuffer);
			input_sec_buffer.pvBuffer = NULL;
		}

		if ((status == SEC_I_COMPLETE_AND_CONTINUE) || (status == SEC_I_COMPLETE_NEEDED))
		{
			if (credssp->table->CompleteAuthToken != NULL)
				credssp->table->CompleteAuthToken(&credssp->context, &output_sec_buffer_desc);

			have_pub_key_auth = true;

			if (credssp->table->QueryContextAttributes(&credssp->context, SECPKG_ATTR_SIZES, &credssp->ContextSizes) != SEC_E_OK)
			{
				printf("QueryContextAttributes SECPKG_ATTR_SIZES failure\n");
				return 0;
			}

			if (have_pub_key_auth)
			{
				uint8* p;
				SEC_BUFFER Buffers[2];
				SEC_BUFFER_DESC Message;

				Buffers[0].BufferType = SECBUFFER_DATA; /* TLS Public Key */
				Buffers[1].BufferType = SECBUFFER_PADDING; /* Signature */

				Buffers[0].cbBuffer = credssp->PublicKey.cbBuffer;
				Buffers[0].pvBuffer = xmalloc(Buffers[0].cbBuffer);
				memcpy(Buffers[0].pvBuffer, credssp->PublicKey.pvBuffer, Buffers[0].cbBuffer);

				Buffers[1].cbBuffer = credssp->ContextSizes.cbMaxSignature;
				Buffers[1].pvBuffer = xzalloc(Buffers[1].cbBuffer);

				Message.cBuffers = 2;
				Message.ulVersion = SECBUFFER_VERSION;
				Message.pBuffers = (SEC_BUFFER*) &Buffers;

				sspi_SecBufferAlloc(&credssp->pubKeyAuth, Buffers[0].cbBuffer + Buffers[1].cbBuffer);

				credssp->table->EncryptMessage(&credssp->context, 0, &Message, 0);

				p = (uint8*) credssp->pubKeyAuth.pvBuffer;
				memcpy(p, Buffers[1].pvBuffer, Buffers[1].cbBuffer); /* Message Signature */
				memcpy(&p[Buffers[1].cbBuffer], Buffers[0].pvBuffer, Buffers[0].cbBuffer); /* Encrypted Public Key */
			}

			if (status == SEC_I_COMPLETE_NEEDED)
				status = SEC_E_OK;
			else if (status == SEC_I_COMPLETE_AND_CONTINUE)
				status = SEC_I_CONTINUE_NEEDED;
		}

		/* send authentication token to server */

		if (output_sec_buffer.cbBuffer > 0)
		{
			p_sec_buffer = &output_sec_buffer_desc.pBuffers[0];

			credssp->negoToken.pvBuffer = p_sec_buffer->pvBuffer;
			credssp->negoToken.cbBuffer = p_sec_buffer->cbBuffer;

#ifdef WITH_DEBUG_CREDSSP
			printf("Sending Authentication Token\n");
			freerdp_hexdump(credssp->negoToken.data, credssp->negoToken.length);
#endif

			credssp_send(credssp, &credssp->negoToken, NULL,
					(have_pub_key_auth) ? &credssp->pubKeyAuth : NULL);

			if (have_pub_key_auth)
			{
				have_pub_key_auth = false;
				sspi_SecBufferFree(&credssp->pubKeyAuth);
			}

			xfree(output_sec_buffer.pvBuffer);
			output_sec_buffer.pvBuffer = NULL;
		}

		if (status != SEC_I_CONTINUE_NEEDED)
			break;

		/* receive server response and place in input buffer */

		input_sec_buffer_desc.ulVersion = SECBUFFER_VERSION;
		input_sec_buffer_desc.cBuffers = 1;
		input_sec_buffer_desc.pBuffers = &input_sec_buffer;
		input_sec_buffer.BufferType = SECBUFFER_TOKEN;

		if (credssp_recv(credssp, &credssp->negoToken, NULL, NULL) < 0)
			return -1;

#ifdef WITH_DEBUG_CREDSSP
		printf("Receiving Authentication Token\n");
		freerdp_hexdump(credssp->negoToken.data, credssp->negoToken.length);
#endif

		p_sec_buffer = &input_sec_buffer_desc.pBuffers[0];
		p_sec_buffer->pvBuffer = credssp->negoToken.pvBuffer;
		p_sec_buffer->cbBuffer = credssp->negoToken.cbBuffer;

		have_input_buffer = true;
		have_context = true;
	}

	/* Encrypted Public Key +1 */
	if (credssp_recv(credssp, &credssp->negoToken, NULL, &credssp->pubKeyAuth) < 0)
		return -1;

	/* Verify Server Public Key Echo */

	status = credssp_verify_public_key_echo(credssp);

	if (status != SEC_E_OK)
		return 0;

	/* Send encrypted credentials */

	status = credssp_encrypt_ts_credentials(credssp);

	if (status != SEC_E_OK)
		return 0;

	credssp_send(credssp, NULL, &credssp->authInfo, NULL);

	/* Free resources */

	//sspi_SecBufferFree(&credssp->negoToken);
	sspi_SecBufferFree(&credssp->authInfo);

	FreeCredentialsHandle(&credentials);
	FreeContextBuffer(pPackageInfo);

	return 1;
}
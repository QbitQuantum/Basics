BOOL shadow_client_context_new(freerdp_peer* peer, rdpShadowClient* client)
{
	rdpSettings* settings;
	rdpShadowServer* server;
	const wObject cb = { NULL, NULL, NULL, shadow_client_free_queued_message, NULL };

	server = (rdpShadowServer*) peer->ContextExtra;
	client->server = server;
	client->subsystem = server->subsystem;

	settings = peer->settings;

	settings->ColorDepth = 32;
	settings->NSCodec = TRUE;
	settings->RemoteFxCodec = TRUE;
	settings->BitmapCacheV3Enabled = TRUE;
	settings->FrameMarkerCommandEnabled = TRUE;
	settings->SurfaceFrameMarkerEnabled = TRUE;
	settings->SupportGraphicsPipeline = FALSE;

	settings->DrawAllowSkipAlpha = TRUE;
	settings->DrawAllowColorSubsampling = TRUE;
	settings->DrawAllowDynamicColorFidelity = TRUE;

	settings->CompressionLevel = PACKET_COMPR_TYPE_RDP6;

	settings->RdpSecurity = TRUE;
	settings->TlsSecurity = TRUE;
	settings->NlaSecurity = FALSE;

	if (!(settings->CertificateFile = _strdup(server->CertificateFile)))
		goto fail_cert_file;
	if (!(settings->PrivateKeyFile = _strdup(server->PrivateKeyFile)))
		goto fail_privkey_file;
	if (!(settings->RdpKeyFile = _strdup(settings->PrivateKeyFile)))
		goto fail_rdpkey_file;


	if (server->ipcSocket)
	{
		settings->LyncRdpMode = TRUE;
		settings->CompressionEnabled = FALSE;
	}

	client->inLobby = TRUE;
	client->mayView = server->mayView;
	client->mayInteract = server->mayInteract;

	if (!InitializeCriticalSectionAndSpinCount(&(client->lock), 4000))
		goto fail_client_lock;

	region16_init(&(client->invalidRegion));

	client->vcm = WTSOpenServerA((LPSTR) peer->context);
	if (!client->vcm || client->vcm == INVALID_HANDLE_VALUE)
		goto fail_open_server;

	if (!(client->MsgQueue = MessageQueue_New(&cb)))
		goto fail_message_queue;

	if (!(client->encoder = shadow_encoder_new(client)))
		goto fail_encoder_new;

	if (ArrayList_Add(server->clients, (void*) client) >= 0)
		return TRUE;

	shadow_encoder_free(client->encoder);
	client->encoder = NULL;
fail_encoder_new:
	MessageQueue_Free(client->MsgQueue);
	client->MsgQueue = NULL;
fail_message_queue:
	WTSCloseServer((HANDLE) client->vcm);
	client->vcm = NULL;
fail_open_server:
	DeleteCriticalSection(&(client->lock));
fail_client_lock:
	free(settings->RdpKeyFile);
	settings->RdpKeyFile = NULL;
fail_rdpkey_file:
	free(settings->PrivateKeyFile);
	settings->PrivateKeyFile = NULL;
fail_privkey_file:
	free(settings->CertificateFile);
	settings->CertificateFile = NULL;
fail_cert_file:

	return FALSE;
}
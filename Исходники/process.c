void freerds_peer_context_free(freerdp_peer* client, rdsConnection* context)
{
	freerds_connection_uninit(context);
	WTSCloseServer((HANDLE) context->vcm);
}
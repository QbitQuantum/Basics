BOOL wf_peer_context_new(freerdp_peer* client, wfPeerContext* context)
{
	if (!(context->info = wf_info_get_instance()))
		return FALSE;

	context->vcm = WTSOpenServerA((LPSTR) client->context);

	if (!context->vcm || context->vcm == INVALID_HANDLE_VALUE)
		return FALSE;

	if (!wf_info_peer_register(context->info, context))
	{
		WTSCloseServer(context->vcm);
		context->vcm = NULL;
		return FALSE;
	}

	return TRUE;
}
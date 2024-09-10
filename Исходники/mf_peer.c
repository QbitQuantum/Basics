/* Called after a peer disconnects */
void mf_peer_context_free(freerdp_peer* client, mfPeerContext* context)
{
	if (context)
	{
		mf_info_peer_unregister(context->info, context);
		
		dispatch_suspend(info_timer);
		
		Stream_Free(context->s, TRUE);
		
		rfx_context_free(context->rfx_context);
		//nsc_context_free(context->nsc_context);
		
#ifdef CHANNEL_AUDIN_SERVER
		if (context->audin)
			audin_server_context_free(context->audin);
#endif
		
		//#ifdef CHANNEL_RDPSND_SERVER
		mf_peer_rdpsnd_stop();
		if (context->rdpsnd)
			rdpsnd_server_context_free(context->rdpsnd);
		//#endif
		
		WTSCloseServer(context->vcm);
	}
}
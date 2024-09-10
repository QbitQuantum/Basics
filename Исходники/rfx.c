void rfx_context_free(RFX_CONTEXT* context)
{
	free(context->quants);

	Queue_Free(context->priv->TilePool);
	Queue_Free(context->priv->TileQueue);

	rfx_profiler_print(context);
	rfx_profiler_free(context);

	if (context->priv->UseThreads)
	{
		CloseThreadpool(context->priv->ThreadPool);
		DestroyThreadpoolEnvironment(&context->priv->ThreadPoolEnv);
#ifdef WITH_PROFILER
		fprintf(stderr, "\nWARNING: Profiling results probably unusable with multithreaded RemoteFX codec!\n");
#endif
	}

	BufferPool_Free(context->priv->BufferPool);

	free(context->priv);
	free(context);
}
GalliumContext::~GalliumContext()
{
	CALLED();

	// Destroy our contexts
	Lock();
	for (context_id i = 0; i < CONTEXT_MAX; i++)
		DestroyContext(i);
	Unlock();

	pipe_mutex_destroy(fMutex);

	// TODO: Destroy fScreen
}
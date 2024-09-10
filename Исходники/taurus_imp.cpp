inline int setup_coroutine(cothread_ctx* tctx, coroutine* c, size_t ssize)
{
	c->ctx = CreateFiber(ssize, &FiberFunc, tctx);
	if (c->ctx == NULL)
	{
	}
	c->stk_size = ssize;
	return (c->ctx==NULL) ? -1 : 0;
}
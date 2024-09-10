static int systimer_create(systimer_t* id, unsigned int period, int oneshot, systimer_proc callback, void* cbparam)
{
	UINT fuEvent;
	timer_context_t* ctx;

	if(oneshot && g_ctx.tc.wPeriodMin > period && period > g_ctx.tc.wPeriodMax)
		return -EINVAL;

	ctx = (timer_context_t*)malloc(sizeof(timer_context_t));
	if(!ctx)
		return -ENOMEM;

	memset(ctx, 0, sizeof(timer_context_t));
	ctx->callback = callback;
	ctx->cbparam = cbparam;
	ctx->period = period;
	ctx->count = 0;

	// check period value
	period = (period > g_ctx.tc.wPeriodMax) ?  TIMER_PERIOD : period;
	fuEvent = (oneshot?TIME_ONESHOT:TIME_PERIODIC)|TIME_CALLBACK_FUNCTION;
	ctx->timerId = timeSetEvent(period, 10, timer_schd_worker, (DWORD_PTR)ctx, fuEvent);
	if(0 == ctx->timerId)
	{
		free(ctx);
		return -EINVAL;
	}

	*id = (systimer_t)ctx;
	return 0;
}
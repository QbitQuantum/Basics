static void timer_free(void *timer)
{
	struct timer *t = (struct timer *)timer;
	HANDLE completion;

	completion = CreateEvent(NULL, FALSE, FALSE, NULL);
	DeleteTimerQueueEx(t->queue, completion);
	WaitForSingleObject(completion, INFINITE);
	free(t);
}
wCountdownEvent* CountdownEvent_New(DWORD initialCount)
{
	wCountdownEvent* countdown = NULL;

	if (!(countdown = (wCountdownEvent*) calloc(1, sizeof(wCountdownEvent))))
		return NULL;

	countdown->count = initialCount;
	countdown->initialCount = initialCount;

	if (!InitializeCriticalSectionAndSpinCount(&countdown->lock, 4000))
		goto fail_critical_section;

	if (!(countdown->event = CreateEvent(NULL, TRUE, FALSE, NULL)))
		goto fail_create_event;

	if (countdown->count == 0)
		if (!SetEvent(countdown->event))
			goto fail_set_event;

	return countdown;

fail_set_event:
	CloseHandle(countdown->event);
fail_create_event:
	DeleteCriticalSection(&countdown->lock);
fail_critical_section:
	free(countdown);

	return NULL;
}
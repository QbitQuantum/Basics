wMessageQueue* MessageQueue_New(const wObject *callback)
{
	wMessageQueue* queue = NULL;

	queue = (wMessageQueue*) malloc(sizeof(wMessageQueue));

	if (queue)
	{
		queue->head = 0;
		queue->tail = 0;
		queue->size = 0;

		queue->capacity = 32;
		queue->array = (wMessage*) malloc(sizeof(wMessage) * queue->capacity);
		ZeroMemory(queue->array, sizeof(wMessage) * queue->capacity);

		InitializeCriticalSectionAndSpinCount(&queue->lock, 4000);
		queue->event = CreateEvent(NULL, TRUE, FALSE, NULL);

		if (callback)
			queue->object = *callback;
		else
			ZeroMemory(&queue->object, sizeof(queue->object));
	}

	return queue;
}
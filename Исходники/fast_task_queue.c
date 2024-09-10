static struct mpool_node *malloc_mpool(const int total_alloc_size)
{
	struct fast_task_info *pTask;
	char *p;
	char *pCharEnd;
	struct mpool_node *mpool;

	mpool = (struct mpool_node *)malloc(sizeof(struct mpool_node));
	if (mpool == NULL)
	{
		logError("file: "__FILE__", line: %d, " \
			"malloc %d bytes fail, " \
			"errno: %d, error info: %s", \
			__LINE__, (int)sizeof(struct mpool_node), \
			errno, STRERROR(errno));
		return NULL;
	}

	mpool->next = NULL;
	mpool->blocks = (struct fast_task_info *)malloc(total_alloc_size);
	if (mpool->blocks == NULL)
	{
		logError("file: "__FILE__", line: %d, " \
			"malloc %d bytes fail, " \
			"errno: %d, error info: %s", \
			__LINE__, total_alloc_size, \
			errno, STRERROR(errno));
		free(mpool);
		return NULL;
	}
	memset(mpool->blocks, 0, total_alloc_size);

	pCharEnd = ((char *)mpool->blocks) + total_alloc_size;
	for (p=(char *)mpool->blocks; p<pCharEnd; p += g_free_queue.block_size)
	{
		pTask = (struct fast_task_info *)p;
		pTask->size = g_free_queue.min_buff_size;

		pTask->arg = p + ALIGNED_TASK_INFO_SIZE;
		if (g_free_queue.malloc_whole_block)
		{
			pTask->data = (char *)pTask->arg + \
					g_free_queue.arg_size;
		}
		else
		{
			pTask->data = (char *)malloc(pTask->size);
			if (pTask->data == NULL)
			{
				char *pt;

				logError("file: "__FILE__", line: %d, " \
					"malloc %d bytes fail, " \
					"errno: %d, error info: %s", \
					__LINE__, pTask->size, \
					errno, STRERROR(errno));

				for (pt=(char *)mpool->blocks; pt < p; \
					pt += g_free_queue.block_size)
				{
					free(((struct fast_task_info *)pt)->data);
				}

				free(mpool->blocks);
				free(mpool);
				return NULL;
			}
		}
	}

	mpool->last_block = (struct fast_task_info *)(pCharEnd - g_free_queue.block_size);
	for (p=(char *)mpool->blocks; p<(char *)mpool->last_block; p += g_free_queue.block_size)
	{
		pTask = (struct fast_task_info *)p;
		pTask->next = (struct fast_task_info *)(p + g_free_queue.block_size);
	}
	mpool->last_block->next = NULL;

	return mpool;
}
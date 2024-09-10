/*
 * scamper_task_alloc
 *
 * allocate and initialise a task object.
 */
scamper_task_t *scamper_task_alloc(void *data, scamper_task_funcs_t *funcs)
{
  scamper_task_t *task;

  assert(data  != NULL);
  assert(funcs != NULL);

  if((task = malloc_zero(sizeof(scamper_task_t))) == NULL)
    {
      printerror(errno, strerror, __func__, "could not malloc task");
      goto err;
    }

  if((task->queue = scamper_queue_alloc(task)) == NULL)
    goto err;

  if((task->siglist = slist_alloc()) == NULL)
    goto err;

  task->funcs = funcs;
  task->data = data;

  return task;

 err:
  scamper_task_free(task);
  return NULL;
}
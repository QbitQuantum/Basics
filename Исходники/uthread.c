/**
* Creates a ThreadBlock structure from @func, and its @argument.
* @stacksize is passed to CreateContext call.
**/
static ThreadBlock * CreateThread(void (*func) (void *),void * argument,long stackSize) {

  ucontext_t * linkedContext = CreateContext(ExitRunningThread,NULL,stackSize,0,NULL);
  ucontext_t * threadContext = CreateContext((void (*) (void))func,linkedContext,stackSize,1,argument);
  ThreadBlock * threadBlock = (ThreadBlock *) malloc(sizeof(ThreadBlock));
  threadBlock->context = threadContext;
  threadBlock->status = STATUS_READY;
  threadBlock->numberOfChildren = 0;
  threadBlock->previous = threadBlock->next = threadBlock->parent = NULL;
  threadBlock->id = uThreadContext->currentID++;

  return threadBlock;
}
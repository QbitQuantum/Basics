/*
 * eval_mm_util - Evaluate the space utilization of the student's package
 *   The idea is to remember the high water mark "hwm" of the heap for
 *   an optimal allocator, i.e., no gaps and no internal fragmentation.
 *   Utilization is the ratio hwm/heapsize, where heapsize is the
 *   size of the heap in bytes after running the student's malloc
 *   package on the trace.
 *
 */
static double eval_mm_util(trace_t *trace, int tracenum) {
  int i;
  int index;
  int size, newsize, oldsize;
  int max_total_size = 0;
  int total_size = 0;
  size_t heap_size = 0 ;
  char *p;
  char *newp, *oldp;

  /* initialize the heap and the mm malloc package */
  mem_reset_brk();
  if (my_impl.init() < 0) {
    app_error("init failed in eval_mm_util");
  }

  for (i = 0; i < trace->num_ops; i++) {
    switch (trace->ops[i].type) {

      case ALLOC: /* alloc */
        index = trace->ops[i].index;
        size = trace->ops[i].size;

        if ((p = (char *) my_impl.malloc(size)) == NULL) {
          app_error("malloc failed in eval_mm_util");
        }

        /* Remember region and size */
        trace->blocks[index] = p;
        trace->block_sizes[index] = size;

        /* Keep track of current total size
         * of all allocated blocks */
        total_size += size;

        /* Update statistics */
        max_total_size = (total_size > max_total_size) ?
            total_size : max_total_size;
        break;

      case REALLOC: /* realloc */
        index = trace->ops[i].index;
        newsize = trace->ops[i].size;
        oldsize = trace->block_sizes[index];

        oldp = trace->blocks[index];
        if ((newp = (char *) my_impl.realloc(oldp,newsize)) == NULL)
          app_error("realloc failed in eval_mm_util");

        /* Remember region and size */
        trace->blocks[index] = newp;
        trace->block_sizes[index] = newsize;

        /* Keep track of current total size
         * of all allocated blocks */
        total_size += (newsize - oldsize);

        /* Update statistics */
        max_total_size = (total_size > max_total_size) ?
            total_size : max_total_size;
        break;

      case FREE: /* free */
        index = trace->ops[i].index;
        size = trace->block_sizes[index];
        p = trace->blocks[index];

        my_impl.free(p);

        /* Keep track of current total size
         * of all allocated blocks */
        total_size -= size;

        break;

      default:
        app_error("Nonexistent request type in eval_mm_util");
    }
  }
  max_total_size = (max_total_size > MEM_ALLOWANCE) ?
    max_total_size : MEM_ALLOWANCE ;
  heap_size = mem_heapsize() ;
  heap_size = (heap_size > MEM_ALLOWANCE) ?
    heap_size : MEM_ALLOWANCE ;
  return ((double)max_total_size / (double)heap_size);
}
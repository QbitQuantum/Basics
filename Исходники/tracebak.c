int
__gnat_backtrace (void **array,
                  int size,
                  void *exclude_min,
                  void *exclude_max,
                  int skip_frames)
{
  CONTEXT context;
  UNWIND_HISTORY_TABLE history;
  int i;

  /* Get the context.  */
  RtlCaptureContext (&context);

  /* Setup unwind history table (a cached to speed-up unwinding).  */
  memset (&history, 0, sizeof (history));

  i = 0;
  while (1)
    {
      PRUNTIME_FUNCTION RuntimeFunction;
      KNONVOLATILE_CONTEXT_POINTERS NvContext;
      ULONG64 ImageBase;
      VOID *HandlerData;
      ULONG64 EstablisherFrame;

      /* Get function metadata.  */
      RuntimeFunction = RtlLookupFunctionEntry
	(context.Rip, &ImageBase, &history);

      if (!RuntimeFunction)
	{
	  /* In case of failure, assume this is a leaf function.  */
	  context.Rip = *(ULONG64 *) context.Rsp;
	  context.Rsp += 8;
	}
      else
	{
	  /* Unwind.  */
	  memset (&NvContext, 0, sizeof (KNONVOLATILE_CONTEXT_POINTERS));
	  RtlVirtualUnwind (0, ImageBase, context.Rip, RuntimeFunction,
			    &context, &HandlerData, &EstablisherFrame,
			    &NvContext);
	}

      /* 0 means bottom of the stack.  */
      if (context.Rip == 0)
	break;

      /* Skip frames.  */
      if (skip_frames > 1)
	{
	  skip_frames--;
	  continue;
	}
      /* Excluded frames.  */
      if ((void *)context.Rip >= exclude_min
	  && (void *)context.Rip <= exclude_max)
	continue;

      array[i++] = (void *)(context.Rip - 2);
      if (i >= size)
	break;
    }
  return i;
}
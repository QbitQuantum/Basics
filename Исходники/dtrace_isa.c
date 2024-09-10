int
dtrace_getstackdepth(int aframes)
{
	int depth = 0;
	struct frame *frame;
	uintptr_t ebp;
	uintptr_t callpc;
	thread_t *td = curthread;
#if defined(windows)
	int pcstack_limit = 100;
	uint64_t pcstack[100];
#endif
	ebp = td->ebp;
	frame = (struct frame *)ebp;
	depth++;
	
#ifdef __amd64
	depth += RtlCaptureStackBackTrace(0, pcstack_limit, (PVOID) pcstack, NULL);
#else
	for(;;) {
		if ((uintptr_t)frame < td->klimit || 
		    (uintptr_t) ((char *) frame - sizeof(struct frame)) >= td->kbase)
			break;
		depth++;
		callpc = frame->f_retaddr;
		
		if (!INKERNEL(callpc))
			break;

		frame = frame->f_frame;
	}
#endif
	if (depth < aframes)
		return 0;
	else
		return depth - aframes;
}
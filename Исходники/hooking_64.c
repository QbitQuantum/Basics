static unsigned int our_stackwalk(ULONG_PTR retaddr, ULONG_PTR sp, PVOID *backtrace, unsigned int count)
{
	/* derived from http://www.nynaeve.net/Code/StackWalk64.cpp */
	CONTEXT ctx;
	DWORD64 imgbase;
	PRUNTIME_FUNCTION runfunc;
	KNONVOLATILE_CONTEXT_POINTERS nvctx;
	PVOID handlerdata;
	ULONG_PTR establisherframe;
	unsigned int frame;

	RtlCaptureContext(&ctx);

	for (frame = 0; frame < count; frame++) {

		backtrace[frame] = (PVOID)ctx.Rip;
		runfunc = RtlLookupFunctionEntry(ctx.Rip, &imgbase, NULL);
		memset(&nvctx, 0, sizeof(nvctx));
		if (runfunc == NULL) {
			ctx.Rip = (ULONG_PTR)(*(ULONG_PTR *)ctx.Rsp);
			ctx.Rsp += 8;
		}
		else {
			RtlVirtualUnwind(UNW_FLAG_NHANDLER, imgbase, ctx.Rip, runfunc, &ctx, &handlerdata, &establisherframe, &nvctx);
		}
		if (!ctx.Rip)
			break;
	}

	return frame + 1;
}
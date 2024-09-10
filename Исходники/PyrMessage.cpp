HOT void returnFromMethod(VMGlobals *g)
{
	PyrFrame *returnFrame, *curframe, *homeContext;
	PyrMethod *meth;
	PyrMethodRaw *methraw;
	curframe = g->frame;

	//assert(slotRawFrame(&curframe->context) == NULL);

	/*if (gTraceInterpreter) {
		post("returnFromMethod %s:%s\n", slotRawClass(&g->method->ownerclass)->name.us->name, g->slotRawSymbol(&method->name)->name);
		post("tailcall %d\n", g->tailCall);
	}*/
#ifdef GC_SANITYCHECK
	g->gc->SanityCheck();
#endif
	homeContext = slotRawFrame(&slotRawFrame(&curframe->context)->homeContext);
	if (homeContext == NULL) {
		null_return:
#if TAILCALLOPTIMIZE
		if (g->tailCall) return; // do nothing.
#endif

	/*
		static bool once = true;
		if (once || gTraceInterpreter)
		{
			once = false;
			post("return all the way out. sd %d\n", g->sp - g->gc->Stack()->slots);
			postfl("%s:%s\n",
				slotRawClass(&g->method->ownerclass)->name.us->name, g->slotRawSymbol(&method->name)->name
			);
			post("tailcall %d\n", g->tailCall);
			post("homeContext %p\n", homeContext);
			post("returnFrame %p\n", returnFrame);
			dumpObjectSlot(&homeContext->caller);
			DumpStack(g, g->sp);
			DumpBackTrace(g);
		}
		gTraceInterpreter = false;
	*/
		//if (IsNil(&homeContext->caller)) return; // do nothing.

		// return all the way out.
		PyrSlot *bottom = g->gc->Stack()->slots;
		slotCopy(bottom, g->sp);
		g->sp = bottom; // ??!! pop everybody
		g->method = NULL;
		g->block = NULL;
		g->frame = NULL;
		longjmp(g->escapeInterpreter, 2);
	} else {
		returnFrame = slotRawFrame(&homeContext->caller);

		if (returnFrame == NULL) goto null_return;
		// make sure returnFrame is a caller and find earliest stack frame
		{
			PyrFrame *tempFrame = curframe;
			while (tempFrame != returnFrame) {
				tempFrame = slotRawFrame(&tempFrame->caller);
				if (!tempFrame) {
					if (isKindOf((PyrObject*)g->thread, class_routine) && NotNil(&g->thread->parent)) {
						// not found, so yield to parent thread and continue searching.
						PyrSlot value;
						slotCopy(&value, g->sp);

						int numArgsPushed = 1;
						switchToThread(g, slotRawThread(&g->thread->parent), tSuspended, &numArgsPushed);

						// on the other side of the looking glass, put the yielded value on the stack as the result..
						g->sp -= numArgsPushed - 1;
						slotCopy(g->sp, &value);

						curframe = tempFrame = g->frame;
					} else {
						slotCopy(&g->sp[2], &g->sp[0]);
						slotCopy(g->sp, &g->receiver);
						g->sp++; SetObject(g->sp, g->method);
						g->sp++;
						sendMessage(g, getsym("outOfContextReturn"), 3);
						return;
					}
				}
			}
		}

		{
			PyrFrame *tempFrame = curframe;
			while (tempFrame != returnFrame) {
				meth = slotRawMethod(&tempFrame->method);
				methraw = METHRAW(meth);
				PyrFrame *nextFrame = slotRawFrame(&tempFrame->caller);
				if (!methraw->needsHeapContext) {
					SetInt(&tempFrame->caller, 0);
				} else {
					if (tempFrame != homeContext)
						SetInt(&tempFrame->caller, 0);
				}
				tempFrame = nextFrame;
			}
		}

		// return to it
		g->ip = (unsigned char *)slotRawPtr(&returnFrame->ip);
		g->frame = returnFrame;
		g->block = slotRawBlock(&returnFrame->method);

		homeContext = slotRawFrame(&returnFrame->homeContext);
		meth = slotRawMethod(&homeContext->method);
		methraw = METHRAW(meth);

#if DEBUGMETHODS
if (gTraceInterpreter) {
	postfl("%s:%s <- %s:%s\n",
		slotRawSymbol(&slotRawClass(&meth->ownerclass)->name)->name, slotRawSymbol(&meth->name)->name,
		slotRawSymbol(&slotRawClass(&g->method->ownerclass)->name)->name, slotRawSymbol(&g->method->name)->name
	);
}
#endif

		g->method = meth;
		slotCopy(&g->receiver, &homeContext->vars[0]);

	}
#ifdef GC_SANITYCHECK
	g->gc->SanityCheck();
#endif
}
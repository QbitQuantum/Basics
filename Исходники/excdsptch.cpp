bool DispatchException( SExceptionRecord *ExceptionRecord, SContext *Context ) {

	SDispatcherContext		DispatcherContext;
	SContext				LocContext;

	EExceptionDisposition	Disposition;

	PExceptionRoutine	Handler;
	void				*HandlerData;

	uint64_t			FunctionFrame;
	SRuntimeFunction	*FunctionEntry;

	void				*Base;

	uint64_t			NestedFrame;

	uint32_t			ExceptionFlags;
	uint32_t			ScopeIndex;

	uintptr_t			StackLowLimit;
	uintptr_t			StackHighLimit;

	uint64_t			Rip;

	uint32_t			Status;

	// get stack limits
	g_GetStackLimitsFunc( &StackLowLimit, &StackHighLimit );

	// copy and initialize starting context
	memset( &DispatcherContext, 0, sizeof(DispatcherContext) );
	memcpy( &LocContext, Context, sizeof(SContext) );
	ExceptionFlags = ExceptionRecord->ExceptionFlags & EXCEPTION_NONCONTINUABLE;
	NestedFrame = 0;

	for ( ;; ) {

		// update current rip
		Rip = LocContext.Rip;

		// get module base
		Base = g_GetImageBaseFunc( (void*)Rip );
		if ( !Base ) {

			// no module containing this address
			// possibly this is a calling of function is at
			// invalid address, or this is just leaf function

			LocContext.Rip = *((uint64_t*)LocContext.Rsp);
			LocContext.Rsp += 8;

		} else {

			// unwind current stack frame
			Status = PeVirtualUnwind(
				Base,
				PE_IMAGE_UNW_FLAG_EHANDLER,
				(void**)&Handler,
				&HandlerData,
				&FunctionFrame,
				&FunctionEntry,
				&LocContext
			);
			if ( Status != ERR_SUCCESS ) {
				ASSERT( false );
			}

			// check frame alignment and check it is within stack limits
			if ( (FunctionFrame != 0) &&
				 ((FunctionFrame & 0x7) || (FunctionFrame < StackLowLimit) || (FunctionFrame >= StackHighLimit)) ) {

				ExceptionFlags |= EXCEPTION_STACK_INVALID;
				break;

			}

			// if there is a handler
			if ( Handler ) {

				// prepare context
				ScopeIndex = 0;
				for ( ;; ) {

					ExceptionRecord->ExceptionFlags = ExceptionFlags;

					DispatcherContext.ControlPc = Rip;
					DispatcherContext.ImageBase = (uint64_t)Base;
					DispatcherContext.FunctionEntry = FunctionEntry;
					DispatcherContext.EstablisherFrame = FunctionFrame;
					DispatcherContext.ContextRecord = &LocContext;
					DispatcherContext.LanguageHandler = Handler;
					DispatcherContext.HandlerData = HandlerData;
					DispatcherContext.HistoryTable = NULL;
					DispatcherContext.ScopeIndex = ScopeIndex;

					// and execute handler
					Disposition = ExecuteHandlerForException(
						ExceptionRecord,
						(void*)FunctionFrame,
						Context,
						&DispatcherContext
					);

					// propogate noncontinuable exception flag
					ExceptionFlags |= (ExceptionRecord->ExceptionFlags & EXCEPTION_NONCONTINUABLE);

					// reset nested flag if we have reached nested context end
					if ( NestedFrame == FunctionFrame ) {
						ExceptionFlags &= ~EXCEPTION_NESTED_CALL;
						NestedFrame = 0;
					}

					if ( Disposition == ExceptionContinueExecution ) {

						// disposition is to continue execution

						if ( ExceptionFlags & EXCEPTION_NONCONTINUABLE ) {
							ASSERT( false );
						}
						return true;

					} else if ( Disposition == ExceptionNestedException ) {

						// disposition is nested exception, set nested flag

						ExceptionFlags |= EXCEPTION_NESTED_CALL;
						if ( DispatcherContext.EstablisherFrame > NestedFrame ) {
							NestedFrame = DispatcherContext.EstablisherFrame;
						}

					} else if ( Disposition == ExceptionCollidedUnwind ) {

						// disposition is collided unwind, copy the context and continue
						// exception handler lookup from frame where first exception occurred

						CopyContext( &LocContext, DispatcherContext.ContextRecord );

						Rip = DispatcherContext.ControlPc;
						FunctionEntry = DispatcherContext.FunctionEntry;
						FunctionFrame = DispatcherContext.EstablisherFrame;
						Handler = DispatcherContext.LanguageHandler;
						HandlerData = DispatcherContext.HandlerData;
						ScopeIndex = DispatcherContext.ScopeIndex;

						LocContext.Rip = Rip;

						continue;

					} else if ( Disposition != ExceptionContinueSearch ) {

						// disposition is invalid

						ASSERT( false );

					}

					break;

				}

			}

		}

		// check stack alignment and check its limits
		if ( (LocContext.Rsp & 0x7) || (LocContext.Rsp < StackLowLimit) || (LocContext.Rsp >= StackHighLimit) ) {
			break;
		}

	}

	// exception is not handled, set final exception flags
	ExceptionRecord->ExceptionFlags = ExceptionFlags;

	return false;

}
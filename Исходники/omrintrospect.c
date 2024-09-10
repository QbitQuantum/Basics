/*
 * Sets up the native thread structures including the backtrace. If a context is specified it is used instead of grabbing
 * the context for the thread pointed to by state->current_thread.
 *
 * @param state - state variable for controlling the thread walk
 * @param sigContext - context to use in place of live thread context
 *
 * @return - 0 on success, non-zero otherwise.
 */
static int
setupNativeThread(J9ThreadWalkState *state, thread_context *sigContext)
{
	PlatformWalkData *data = (PlatformWalkData *)state->platform_data;
	int size = sizeof(thread_context);
	int rc = 0;

	if (size < sizeof(ucontext_t)) {
		size = sizeof(ucontext_t);
	}

	/* Allocate the thread container. */
	state->current_thread = (J9PlatformThread *)state->portLibrary->heap_allocate(state->portLibrary, state->heap, sizeof(J9PlatformThread));
	if (NULL == state->current_thread) {
		rc = -1;
	}
	if (0 == rc) {
		memset(state->current_thread, 0, sizeof(J9PlatformThread));

		/* Allocate space for the copy of the context. */
		state->current_thread->context = (thread_context *)state->portLibrary->heap_allocate(state->portLibrary, state->heap, size);
		if (NULL == state->current_thread->context) {
			rc = -1;
		}
	}

	if (0 == rc) {
		state->current_thread->thread_id = data->threadList[data->threadIndex];
		state->current_thread->process_id = getpid();

		if (NULL == sigContext) {
			/* Generate the context by installing a signal handler and raising a signal. None was provided. */
			if (0 == getThreadContext(state)) {
				memcpy(state->current_thread->context, signalHandlerContext, size);
			} else {
				rc = -1;
			}
		} else {
			/* Copy the context. We're using the provided context instead of generating it. */
			memcpy(state->current_thread->context, ((OMRUnixSignalInfo *)sigContext)->platformSignalInfo.context, size);
		}
	}

	if (0 == rc) {
		/* Populate backtraces if not present. */
		if (NULL == state->current_thread->callstack) {
			/* Don't pass sigContext in here as we should have fixed up the thread already. It confuses heap/not heap allocations if we
			 * pass it here.
			 */
			SPECULATE_ERROR(state, FAULT_DURING_BACKTRACE, 2);
			state->portLibrary->introspect_backtrace_thread(state->portLibrary, state->current_thread, state->heap, NULL);
			CLEAR_ERROR(state);
		}

		if ((NULL != state->current_thread->callstack) && (NULL == state->current_thread->callstack->symbol)) {
			SPECULATE_ERROR(state, FAULT_DURING_BACKTRACE, 3);
			state->portLibrary->introspect_backtrace_symbols(state->portLibrary, state->current_thread, state->heap);
			CLEAR_ERROR(state);
		}

		if (0 != state->current_thread->error) {
			RECORD_ERROR(state, state->current_thread->error, 1);
		}
	}

	return rc;
}
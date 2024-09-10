/**
 * Initialize a thread's priority.
 *
 * Here the threading library priority value is converted to the appropriate
 * OS-specific value.
 *
 * @param[in] thread a thread
 * @return none
 *
 */
void
initialize_thread_priority(omrthread_t thread)
{
	int priority;

	thread->priority = J9THREAD_PRIORITY_NORMAL;

	if (priority_map[J9THREAD_PRIORITY_MIN] == priority_map[J9THREAD_PRIORITY_MAX]) {
		return;
	}

	priority = GetThreadPriority(thread->handle);

	thread->priority = omrthread_map_native_priority(priority);
}
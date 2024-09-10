/*
 * __wt_library_init --
 *	Some things to do, before we do anything else.
 */
int
__wt_once(void(*init_routine)(void))
{
	INIT_ONCE once_control = INIT_ONCE_STATIC_INIT;
	PVOID lpContext = NULL;

	return !InitOnceExecuteOnce(&once_control, &_wt_init_once_callback,
	    init_routine, lpContext);
}
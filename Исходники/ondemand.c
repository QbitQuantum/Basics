/* the thread function called by the thread pool, in case of threaded scan */
static void scan_entry_thread_fun(gpointer data, gpointer user_data)
{
	struct a6o_on_demand *on_demand = (struct a6o_on_demand *)user_data;
	char *path = (char *)data;

#ifdef _WIN32
	void * OldValue = NULL;
	if (Wow64DisableWow64FsRedirection(&OldValue) == FALSE) {
		return;
	}
#endif
	if(!cancel)
	   scan_file(on_demand, path);

	/* path was strdup'ed, so free it */
	free(path);

#ifdef _WIN32
	if (Wow64RevertWow64FsRedirection(OldValue) == FALSE ){
		return;
	}
#endif
}
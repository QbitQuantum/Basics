static void ITTAPI ITT_VERSIONIZE(ITT_JOIN(_N_(thread_set_nameW),_init))(const wchar_t* name)
{
    TIDT tid = __itt_thread_id();
    __itt_thread_info *h_tail, *h;

    if (!__itt_ittapi_global.api_initialized && __itt_ittapi_global.thread_list->tid == 0)
    {
        __itt_init_ittlib_name(NULL, __itt_group_all);
        if (ITTNOTIFY_NAME(thread_set_nameW) && ITTNOTIFY_NAME(thread_set_nameW) != ITT_VERSIONIZE(ITT_JOIN(_N_(thread_set_nameW),_init)))
        {
            ITTNOTIFY_NAME(thread_set_nameW)(name);
            return;
        }
    }

    __itt_mutex_lock(&__itt_ittapi_global.mutex);
    for (h_tail = NULL, h = __itt_ittapi_global.thread_list; h != NULL; h_tail = h, h = h->next)
        if (h->tid == tid)
            break;
    if (h == NULL) {
        NEW_THREAD_INFO_W(&__itt_ittapi_global, h, h_tail, tid, __itt_thread_normal, name);
    }
    else
    {
        h->nameW = name ? _wcsdup(name) : NULL;
    }
    __itt_mutex_unlock(&__itt_ittapi_global.mutex);
}
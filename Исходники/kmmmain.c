KHMEXP void KHMAPI kmm_exit(void)
{
    kmm_module_i * m;
    kmm_plugin_i * p;

    EnterCriticalSection(&cs_kmm);

    p = kmm_listed_plugins;
    while(p) {
        kmm_plugin_i * pn;

        pn = LNEXT(p);
        /* plugins that were never resolved should be kicked off the
           list.  Flipping the refcount will do that if no other
           references exist for the plugin.  The plugins that were
           waiting for unresolved dependencies will automatically get
           freed when the placeholders and other plugins get freed. */
        if(p->state == KMM_PLUGIN_STATE_PLACEHOLDER) {
            kmm_hold_plugin(kmm_handle_from_plugin(p));
            kmm_release_plugin(kmm_handle_from_plugin(p));
        }

        p = pn;
    }

    m = kmm_all_modules;
    while(m) {
        kmm_unload_module(kmm_handle_from_module(m));
        m = LNEXT(m);
    }

    LeaveCriticalSection(&cs_kmm);
    WaitForSingleObject(evt_exit, INFINITE);
    EnterCriticalSection(&cs_kmm);

    kmq_post_thread_quit_message(tid_registrar, 0, NULL);

    hash_del_hashtable(hash_plugins);
    hash_del_hashtable(hash_modules);

    LeaveCriticalSection(&cs_kmm);

    TlsFree(tls_kmm);

    tls_kmm = 0;
}
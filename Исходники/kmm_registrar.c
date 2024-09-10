/*! \internal
  \brief Uninitializes a module

  \note Should only be called from the context of the registrar
  thread */
void kmmint_exit_module(kmm_module_i * m) {
    kmm_plugin_i * p;

    /*  Exiting a module happens in two stages.  

        If the module state is running (there are active plugins) then
        those plugins must be exited.  This has to be done from the
        plugin threads.  The signal for the plugins to exit must be
        issued from the registrar.  Therefore, we post messages to the
        registrar for each plugin we want to remove and exit
        kmmint_exit_module().

        When the last plugin is exited, the plugin management code
        automatically signalls the registrar to remove the module.
        kmmint_exit_module() gets called again.  This is the second
        stage, where we call exit_module() for the module and start
        unloading everything.
    */

    EnterCriticalSection(&cs_kmm);

    /* get rid of any dangling uninitialized plugins */
    LPOP(&(m->plugins), &p);
    while(p) {
        p->flags &= ~KMM_PLUGIN_FLAG_IN_MODLIST;
        kmmint_exit_plugin(p);

        /* release hold from kmm_provide_plugin() */
        kmm_release_plugin(kmm_handle_from_plugin(p));

        LPOP(&(m->plugins), &p);
    }

    if(m->state == KMM_MODULE_STATE_RUNNING) {
        int np = 0;

        m->state = KMM_MODULE_STATE_EXITPLUG;

        p = kmm_listed_plugins;

        while(p) {
            if(p->module == m &&
               (p->flags & KMM_PLUGIN_FLAG_IN_MODCOUNT)) {

                kmm_hold_plugin(kmm_handle_from_plugin(p));
                kmq_post_message(KMSG_KMM, KMSG_KMM_I_REG, 
                                 KMM_REG_EXIT_PLUGIN, (void *) p);
                np++;

            }

            p = LNEXT(p);
        }

#ifdef DEBUG
        assert(np == m->plugin_count);
#endif

        if(np > 0) {
            /*  we have to go back and wait for the plugins to exit.
                when the last plugin exits, it automatically posts
                EXIT_MODULE. We can pick up from there when this
                happens. */
            LeaveCriticalSection(&cs_kmm);
            return;
        }

    } else {

#ifdef DEBUG
        assert(m->plugin_count == 0 ||
               m->state == KMM_MODULE_STATE_EXITPLUG);
#endif

        /* if there are still plug-ins waiting to be unloaded, then we
           have to go back and wait for them to finish.  Once they are
           done, kmmint_exit_module() will get called again. */
        if (m->plugin_count > 0) {
            LeaveCriticalSection(&cs_kmm);
            return;
        }
    }

    if(m->flags & KMM_MODULE_FLAG_INITP) {
        exit_module_t p_exit_module;

        if(m->state > 0)
            m->state = KMM_MODULE_STATE_EXIT;

        p_exit_module = 
            (exit_module_t) GetProcAddress(m->h_module, 
                                           EXP_EXIT_MODULE);
        if(p_exit_module) {
            LeaveCriticalSection(&cs_kmm);
            (*p_exit_module)(kmm_handle_from_module(m));
            EnterCriticalSection(&cs_kmm);
        }
    }

    if(m->state > 0)
        m->state = KMM_MODULE_STATE_EXITED;

    LeaveCriticalSection(&cs_kmm);

    if(!(m->flags & KMM_MODULE_FLAG_NOUNLOAD) &&
       m->h_module) {
        FreeLibrary(m->h_module);
    }

    if(!(m->flags & KMM_MODULE_FLAG_NOUNLOAD) &&
       m->h_resource && (m->h_resource != m->h_module)) {
        FreeLibrary(m->h_resource);
    }

    m->h_module = NULL;
    m->h_resource = NULL;

    if (m->flags & KMM_MODULE_FLAG_LOADED) {
#ifdef DEBUG
        assert(kmm_active_modules > 0);
#endif
        kmm_active_modules--;
    }

    m->flags = 0;

    /* release the hold obtained in kmmint_init_module() */
    kmm_release_module(kmm_handle_from_module(m));

    /* Last but not least, now see if there are any modules left that
       are running. If not, we can safely signal an exit. */
    if (kmm_active_modules == 0) {
        SetEvent(evt_exit);
    }
}
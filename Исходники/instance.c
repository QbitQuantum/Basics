void* RunInstance(void* arg)
{
    FcitxInstance* instance = (FcitxInstance*) arg;
    FcitxAddonsInit(&instance->addons);
    FcitxInstanceInitIM(instance);
    FcitxInstanceInitNoPreeditApps(instance);
    FcitxFrontendsInit(&instance->frontends);
    InitFcitxModules(&instance->modules);
    InitFcitxModules(&instance->eventmodules);
    utarray_init(&instance->uistats, &stat_icd);
    utarray_init(&instance->uicompstats, &compstat_icd);
    utarray_init(&instance->uimenus, fcitx_ptr_icd);
    utarray_init(&instance->timeout, &timeout_icd);
    utarray_init(&instance->icdata, &icdata_icd);
    instance->input = FcitxInputStateCreate();
    instance->config = fcitx_utils_malloc0(sizeof(FcitxGlobalConfig));
    instance->profile = fcitx_utils_malloc0(sizeof(FcitxProfile));
    instance->globalIMName = strdup("");
    if (instance->fd >= 0) {
        fcntl(instance->fd, F_SETFL, O_NONBLOCK);
    } else {
        instance->fd = -1;
    }

    if (!FcitxGlobalConfigLoad(instance->config))
        goto error_exit;

    FcitxCandidateWordSetPageSize(instance->input->candList, instance->config->iMaxCandWord);

    int overrideDelay = instance->overrideDelay;

    if (overrideDelay < 0)
        overrideDelay = instance->config->iDelayStart;

    if (overrideDelay > 0)
        sleep(overrideDelay);

    instance->timeStart = time(NULL);
    instance->globalState = instance->config->defaultIMState;
    instance->totaltime = 0;

    FcitxInitThread(instance);
    if (!FcitxProfileLoad(instance->profile, instance))
        goto error_exit;
    if (FcitxAddonGetConfigDesc() == NULL)
        goto error_exit;
    if (GetIMConfigDesc() == NULL)
        goto error_exit;

    FcitxAddonsLoad(&instance->addons);
    FcitxInstanceFillAddonOwner(instance, NULL);
    FcitxInstanceResolveAddonDependency(instance);
    FcitxInstanceInitBuiltInHotkey(instance);
    FcitxInstanceInitBuiltContext(instance);
    FcitxModuleLoad(instance);
    if (instance->loadingFatalError)
        return NULL;
    if (!FcitxInstanceLoadAllIM(instance)) {
        goto error_exit;
    }

    FcitxInstanceInitIMMenu(instance);
    FcitxUIRegisterMenu(instance, &instance->imMenu);
    FcitxUIRegisterStatus(instance, instance, "remind",
                           instance->profile->bUseRemind ? _("Use remind") :  _("No remind"),
                          _("Toggle Remind"), ToggleRemindState, GetRemindEnabled);
    FcitxUISetStatusVisable(instance, "remind",  false);

    FcitxUILoad(instance);

    instance->iIMIndex = FcitxInstanceGetIMIndexByName(instance, instance->profile->imName);
    if (instance->iIMIndex < 0) {
        instance->iIMIndex = 0;
    }

    FcitxInstanceSwitchIMByIndex(instance, instance->iIMIndex);

    if (!FcitxInstanceLoadFrontend(instance)) {
        goto error_exit;
    }

    /* fcitx is running in a standalone thread or not */
    if (instance->sem) {
        sem_post(&instance->notifySem);
        sem_wait(&instance->startUpSem);
    } else {
        instance->initialized = true;
    }

    uint64_t curtime = 0;
    while (1) {
        FcitxAddon** pmodule;
        uint8_t signo = 0;
        if (instance->fd >= 0) {
            while (read(instance->fd, &signo, sizeof(char)) > 0) {
                if (signo == SIGINT || signo == SIGTERM || signo == SIGQUIT || signo == SIGXCPU)
                    FcitxInstanceEnd(instance);
                else if (signo == SIGHUP)
                    FcitxInstanceRestart(instance);
                else if (signo == SIGUSR1)
                    FcitxInstanceReloadConfig(instance);
            }
        }
        do {
            instance->eventflag &= (~FEF_PROCESS_EVENT_MASK);
            for (pmodule = (FcitxAddon**) utarray_front(&instance->eventmodules);
                  pmodule != NULL;
                  pmodule = (FcitxAddon**) utarray_next(&instance->eventmodules, pmodule)) {
                FcitxModule* module = (*pmodule)->module;
                module->ProcessEvent((*pmodule)->addonInstance);
            }
            struct timeval current_time;
            gettimeofday(&current_time, NULL);
            curtime = (current_time.tv_sec * 1000LL) + (current_time.tv_usec / 1000LL);

            unsigned int idx = 0;
            while(idx < utarray_len(&instance->timeout))
            {
                TimeoutItem* ti = (TimeoutItem*) utarray_eltptr(&instance->timeout, idx);
                uint64_t id = ti->idx;
                if (ti->time + ti->milli <= curtime) {
                    ti->callback(ti->arg);
                    ti = (TimeoutItem*) utarray_eltptr(&instance->timeout, idx);
                    /* faster remove */
                    if (ti && ti->idx == id)
                        utarray_remove_quick(&instance->timeout, idx);
                    else {
                        FcitxInstanceRemoveTimeoutById(instance, id);
                        idx = 0;
                    }
                }
                else {
                    idx++;
                }
            }

            if (instance->eventflag & FEF_UI_MOVE)
                FcitxUIMoveInputWindowReal(instance);

            if (instance->eventflag & FEF_UI_UPDATE)
                FcitxUIUpdateInputWindowReal(instance);
        } while ((instance->eventflag & FEF_PROCESS_EVENT_MASK) != FEF_NONE);

        setjmp(FcitxRecover);

        if (instance->destroy || instance->restart) {
            FcitxInstanceRealEnd(instance);
            break;
        }
        
        if (instance->eventflag & FEF_RELOAD_ADDON) {
            instance->eventflag &= ~(FEF_RELOAD_ADDON);
            FcitxInstanceReloadAddon(instance);
        }

        FD_ZERO(&instance->rfds);
        FD_ZERO(&instance->wfds);
        FD_ZERO(&instance->efds);

        instance->maxfd = 0;
        if (instance->fd > 0) {
            instance->maxfd = instance->fd;
            FD_SET(instance->fd, &instance->rfds);
        }
        for (pmodule = (FcitxAddon**) utarray_front(&instance->eventmodules);
              pmodule != NULL;
              pmodule = (FcitxAddon**) utarray_next(&instance->eventmodules, pmodule)) {
            FcitxModule* module = (*pmodule)->module;
            module->SetFD((*pmodule)->addonInstance);
        }
        if (instance->maxfd == 0)
            break;
        struct timeval tval;
        struct timeval* ptval = NULL;
        if (utarray_len(&instance->timeout) != 0) {
            unsigned long int min_time = LONG_MAX;
            TimeoutItem* ti;
            for (ti = (TimeoutItem*)utarray_front(&instance->timeout);ti;
                 ti = (TimeoutItem*)utarray_next(&instance->timeout, ti)) {
                if (ti->time + ti->milli - curtime < min_time) {
                    min_time = ti->time + ti->milli - curtime;
                }
            }
            tval.tv_usec = (min_time % 1000) * 1000;
            tval.tv_sec = min_time / 1000;
            ptval = &tval;
        }
        select(instance->maxfd + 1, &instance->rfds, &instance->wfds,
               &instance->efds, ptval);
    }
    if (instance->restart) {
        fcitx_utils_restart_in_place();
    }

    return NULL;

error_exit:
    sem_post(&instance->startUpSem);
    FcitxInstanceEnd(instance);
    return NULL;
}
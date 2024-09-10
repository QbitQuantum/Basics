static void periodic_task()
{
    nrk_sig_mask_t wait_mask, func_wait_mask;
    nrk_time_t next_event, func_next_event;
    periodic_func_t **funcp;
    periodic_func_t *func;
    nrk_time_t now, sleep_time;
    int8_t rc;

    funcp = &functions[0];
    while (*funcp) {
        func = *funcp;
        LOG("init: "); LOGF(func->name); LOGNL();
        if (func->init)
            func->init();
        funcp++;
    }

    rc = nrk_signal_register(func_signal);
    if (rc == NRK_ERROR)
        ABORT("reg sig: func\r\n");

    while (1) {

        LOG("awake\r\n");

        TIME_CLEAR(next_event);

        wait_mask = SIG(func_signal);

        funcp = &functions[0];
        while (*funcp) {
            func = *funcp;

            TIME_CLEAR(func_next_event);
            func_wait_mask = 0;

            if (func->enabled ||
                func->enabled != func->last_enabled) {

                LOG("proc: "); LOGF(func->name); LOGNL();
                ASSERT(func->proc);

                func->proc(func->enabled,
                           &func_next_event, &func_wait_mask);
            }
            func->last_enabled = func->enabled;

            wait_mask |= func_wait_mask;
            if (IS_VALID_TIME(func_next_event) &&
                (!IS_VALID_TIME(next_event) ||
                 time_cmp(&func_next_event, &next_event) < 0)) {
                next_event = func_next_event;
            }

            funcp++;
        }

        if (IS_VALID_TIME(next_event)) {
            nrk_time_get(&now);
            rc = nrk_time_sub(&sleep_time, next_event, now);
            if (rc != NRK_OK) {
                LOG("next event in the past\r\n");
                continue;
            }
            LOG("sleeping for: ");
            LOGP("%lu ms\r\n", TIME_TO_MS(sleep_time));
            nrk_set_next_wakeup(sleep_time);
            wait_mask |= SIG(nrk_wakeup_signal);
        }
        LOG("waiting\r\n");
        nrk_event_wait( wait_mask );
    }

    ABORT("periodic task exited\r\n");
}
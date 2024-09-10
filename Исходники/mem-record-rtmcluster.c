void mem_write(tid_t tid, uint32_t *addr, uint32_t val) {
    version_t version;
    objid_t objid = calc_objid(addr);
    struct objinfo *info = &g_objinfo[objid];

    if ((g_sim_bbcnt % RTM_BATCH_N) == 0) {
        assert(!_xtest());
        int ret = _xbegin();
        (void)ret;
#ifdef RTM_STAT
        if (ret != _XBEGIN_STARTED) {
            fprintf(stderr, "T%d W%ld aborted %x, %d\n", g_tid, memop, ret,
                    _XABORT_CODE(ret));
            g_rtm_abort_cnt++;
        }
#endif
    }

    int in_rtm = _xtest();
    if (in_rtm) {
        version = info->version;
        // XXX To ensure exclusion of write tx and fallback. Same as in read
        // transaction.
        if (info->write_lock) {
            _xabort(3);
        }
        barrier();
        *addr = val;
        barrier();
        info->version += 2;
        // XXX The barrier is necessary, because there are reordering inside a
        // transaction.  The reason is the same as in seqlock implementation.
        __sync_synchronize();
    } else {
        spin_lock(&info->write_lock);

        version = info->version;
        barrier();

        // Odd version means that there's writer trying to update value.
        info->version++;
        barrier();
        *addr = val;
        // This barrier disallows read to happen before the write.
        // The explicit barrier here may also make the compiler unnecessary here.
        __sync_synchronize();
        info->version++;

        spin_unlock(&info->write_lock);
    }

    if (in_rtm && (g_sim_bbcnt % RTM_BATCH_N == RTM_BATCH_N - 1))  {
        // XXX Update: since we have checked lock in tx region, we
        // will abort for parallel execution of write tx and write fallback.
        // So no need to check for lock here.
        /*
         *if (info->write_lock) {
         *    _xabort(4);
         *}
         */
        _xend();
        // Avoid taking log inside transaction.
        batch_write_log(objid, version);
        batch_process_log();
    } else {
        batch_write_log(objid, version);
    }

    g_sim_bbcnt++;
}
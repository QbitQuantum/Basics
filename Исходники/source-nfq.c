            /* no error on timeout */
            if (flag)
                NFQVerdictCacheFlush(t);
        } else {
#ifdef COUNTERS
            NFQMutexLock(t);
            t->errs++;
            NFQMutexUnlock(t);
#endif /* COUNTERS */
        }
    } else if(rv == 0) {
        SCLogWarning(SC_ERR_NFQ_RECV, "recv got returncode 0");
    } else {
#ifdef DBG_PERF
        if (rv > t->dbg_maxreadsize)
            t->dbg_maxreadsize = rv;
#endif /* DBG_PERF */

        //printf("NFQRecvPkt: t %p, rv = %" PRId32 "\n", t, rv);

        NFQMutexLock(t);
        if (t->qh != NULL) {
            ret = nfq_handle_packet(t->h, tv->data, rv);
        } else {
            SCLogWarning(SC_ERR_NFQ_HANDLE_PKT, "NFQ handle has been destroyed");
            ret = -1;
        }
        NFQMutexUnlock(t);

        if (ret != 0) {
            SCLogWarning(SC_ERR_NFQ_HANDLE_PKT, "nfq_handle_packet error %" PRId32 "", ret);
        }
    }
}
#else /* WIN32 version of NFQRecvPkt */
void NFQRecvPkt(NFQQueueVars *t, NFQThreadVars *tv) {
    int rv, ret;
    static int timeouted = 0;

    if (timeouted) {
        if (WaitForSingleObject(t->ovr.hEvent, 1000) == WAIT_TIMEOUT) {
            rv = -1;
            errno = EINTR;
            goto process_rv;
        }
        timeouted = 0;
    }

read_packet_again:

    if (!ReadFile(t->fd, tv->buf, sizeof(tv->buf), (DWORD*)&rv, &t->ovr)) {
        if (GetLastError() != ERROR_IO_PENDING) {
            rv = -1;
            errno = EIO;
        } else {
            if (WaitForSingleObject(t->ovr.hEvent, 1000) == WAIT_TIMEOUT) {
                rv = -1;
                errno = EINTR;
                timeouted = 1;
            } else {
                /* We needn't to call GetOverlappedResult() because it always
                 * fail with our error code ERROR_MORE_DATA. */
                goto read_packet_again;
            }
        }
    }

process_rv:

    if (rv < 0) {
        if (errno == EINTR) {
            /* no error on timeout */
        } else {
#ifdef COUNTERS
            t->errs++;
#endif /* COUNTERS */
        }
    } else if(rv == 0) {
        SCLogWarning(SC_ERR_NFQ_RECV, "recv got returncode 0");
    } else {
#ifdef DBG_PERF
        if (rv > t->dbg_maxreadsize)
            t->dbg_maxreadsize = rv;
#endif /* DBG_PERF */

        //printf("NFQRecvPkt: t %p, rv = %" PRId32 "\n", t, rv);

        NFQMutexLock(t);
        if (t->qh) {
            ret = nfq_handle_packet(t->h, buf, rv);
        } else {
            SCLogWarning(SC_ERR_NFQ_HANDLE_PKT, "NFQ handle has been destroyed");
            ret = -1;
        }
        NFQMutexUnlock(t);

        if (ret != 0) {
            SCLogWarning(SC_ERR_NFQ_HANDLE_PKT, "nfq_handle_packet error %" PRId32 "", ret);
        }
    }
}
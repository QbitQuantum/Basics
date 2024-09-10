int pthread_cond_timedwait(FAR pthread_cond_t *cond, FAR pthread_mutex_t *mutex,
                           FAR const struct timespec *abstime)
{
    FAR struct tcb_s *rtcb = (FAR struct tcb_s *)g_readytorun.head;
    int ticks;
    int mypid = (int)getpid();
    irqstate_t int_state;
    int ret = OK;
    int status;

    sdbg("cond=0x%p mutex=0x%p abstime=0x%p\n", cond, mutex, abstime);

    DEBUGASSERT(rtcb->waitdog == NULL);

    /* Make sure that non-NULL references were provided. */

    if (!cond || !mutex)
    {
        ret = EINVAL;
    }

    /* Make sure that the caller holds the mutex */

    else if (mutex->pid != mypid)
    {
        ret = EPERM;
    }

    /* If no wait time is provided, this function degenerates to
     * the same behavior as pthread_cond_wait().
     */

    else if (!abstime)
    {
        ret = pthread_cond_wait(cond, mutex);
    }

    else
    {
        /* Create a watchdog */

        rtcb->waitdog = wd_create();
        if (!rtcb->waitdog)
        {
            ret = EINVAL;
        }
        else
        {
            sdbg("Give up mutex...\n");

            /* We must disable pre-emption and interrupts here so that
             * the time stays valid until the wait begins.   This adds
             * complexity because we assure that interrupts and
             * pre-emption are re-enabled correctly.
             */

            sched_lock();
            int_state = irqsave();

            /* Convert the timespec to clock ticks.  We must disable pre-emption
             * here so that this time stays valid until the wait begins.
             */

            ret = clock_abstime2ticks(CLOCK_REALTIME, abstime, &ticks);
            if (ret)
            {
                /* Restore interrupts  (pre-emption will be enabled when
                 * we fall through the if/then/else
                 */

                irqrestore(int_state);
            }
            else
            {
                /* Check the absolute time to wait.  If it is now or in the past, then
                 * just return with the timedout condition.
                 */

                if (ticks <= 0)
                {
                    /* Restore interrupts and indicate that we have already timed out.
                     * (pre-emption will be enabled when we fall through the
                     * if/then/else
                     */

                    irqrestore(int_state);
                    ret = ETIMEDOUT;
                }
                else
                {
                    /* Give up the mutex */

                    mutex->pid = 0;
                    ret = pthread_givesemaphore((sem_t*)&mutex->sem);
                    if (ret)
                    {
                        /* Restore interrupts  (pre-emption will be enabled when
                         * we fall through the if/then/else)
                         */

                        irqrestore(int_state);
                    }
                    else
                    {
                        /* Start the watchdog */

                        wd_start(rtcb->waitdog, ticks, (wdentry_t)pthread_condtimedout,
                                 2, (uint32_t)mypid, (uint32_t)SIGCONDTIMEDOUT);

                        /* Take the condition semaphore.  Do not restore interrupts
                         * until we return from the wait.  This is necessary to
                         * make sure that the watchdog timer and the condition wait
                         * are started atomically.
                         */

                        status = sem_wait((sem_t*)&cond->sem);

                        /* Did we get the condition semaphore. */

                        if (status != OK)
                        {
                            /* NO.. Handle the special case where the semaphore wait was
                             * awakened by the receipt of a signal -- presumably the
                             * signal posted by pthread_condtimedout().
                             */

                            if (get_errno() == EINTR)
                            {
                                sdbg("Timedout!\n");
                                ret = ETIMEDOUT;
                            }
                            else
                            {
                                ret = EINVAL;
                            }
                        }

                        /* The interrupts stay disabled until after we sample the errno.
                         * This is because when debug is enabled and the console is used
                         * for debug output, then the errno can be altered by interrupt
                         * handling! (bad)
                         */

                        irqrestore(int_state);
                    }

                    /* Reacquire the mutex (retaining the ret). */

                    sdbg("Re-locking...\n");
                    status = pthread_takesemaphore((sem_t*)&mutex->sem);
                    if (!status)
                    {
                        mutex->pid = mypid;
                    }
                    else if (!ret)
                    {
                        ret = status;
                    }
                }

                /* Re-enable pre-emption (It is expected that interrupts
                 * have already been re-enabled in the above logic)
                 */

                sched_unlock();
            }

            /* We no longer need the watchdog */

            wd_delete(rtcb->waitdog);
            rtcb->waitdog = NULL;
        }
    }

    sdbg("Returning %d\n", ret);
    return ret;
}
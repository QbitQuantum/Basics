int psock_tcp_accept(FAR struct socket *psock, FAR struct sockaddr *addr,
                     FAR socklen_t *addrlen, FAR void **newconn)
{
    FAR struct tcp_conn_s *conn;
    struct accept_s state;
    int ret;

    DEBUGASSERT(psock && newconn);

    /* Check the backlog to see if there is a connection already pending for
     * this listener.
     */

    conn = (FAR struct tcp_conn_s *)psock->s_conn;

#ifdef CONFIG_NET_TCPBACKLOG
    state.acpt_newconn = tcp_backlogremove(conn);
    if (state.acpt_newconn)
    {
        /* Yes... get the address of the connected client */

        nvdbg("Pending conn=%p\n", state.acpt_newconn);
        accept_tcpsender(psock, state.acpt_newconn, addr, addrlen);
    }

    /* In general, this uIP-based implementation will not support non-blocking
     * socket operations... except in a few cases:  Here for TCP accept with
     * backlog enabled.  If this socket is configured as non-blocking then
     * return EAGAIN if there is no pending connection in the backlog.
     */

    else if (_SS_ISNONBLOCK(psock->s_flags))
    {
        return -EAGAIN;
    }
    else
#endif
    {
        /* Set the socket state to accepting */

        psock->s_flags = _SS_SETSTATE(psock->s_flags, _SF_ACCEPT);

        /* Perform the TCP accept operation */

        /* Initialize the state structure.  This is done with interrupts
         * disabled because we don't want anything to happen until we
         * are ready.
         */

        state.acpt_sock       = psock;
        state.acpt_addr       = addr;
        state.acpt_addrlen    = addrlen;
        state.acpt_newconn    = NULL;
        state.acpt_result     = OK;
        sem_init(&state.acpt_sem, 0, 0);

        /* Set up the callback in the connection */

        conn->accept_private  = (FAR void *)&state;
        conn->accept          = accept_interrupt;

        /* Wait for the send to complete or an error to occur:  NOTES: (1)
         * net_lockedwait will also terminate if a signal is received, (2)
         * interrupts may be disabled!  They will be re-enabled while the
         * task sleeps and automatically re-enabled when the task restarts.
         */

        ret = net_lockedwait(&state.acpt_sem);
        if (ret < 0)
        {
            /* The value returned by net_lockedwait() the same as the value
             * returned by sem_wait():  Zero (OK) is returned on success; -1
             * (ERROR) is returned on a failure with the errno value set
             * appropriately.
             *
             * We have to preserve the errno value here because it may be
             * altered by intervening operations.
             */

            ret = -get_errno();
            DEBUGASSERT(ret < 0);
        }

        /* Make sure that no further interrupts are processed */

        conn->accept_private = NULL;
        conn->accept         = NULL;

        sem_destroy(&state. acpt_sem);

        /* Set the socket state to idle */

        psock->s_flags = _SS_SETSTATE(psock->s_flags, _SF_IDLE);

        /* Check for a errors.  Errors are signalled by negative errno values
         * for the send length.
         */

        if (state.acpt_result != 0)
        {
            DEBUGASSERT(state.acpt_result > 0);
            return -state.acpt_result;
        }

        /* If net_lockedwait failed, then we were probably reawakened by a
         * signal. In this case, logic above will have set 'ret' to the
         * errno value returned by net_lockedwait().
         */

        if (ret < 0)
        {
            return ret;
        }
    }

    *newconn = (FAR void *)state.acpt_newconn;
    return OK;
}
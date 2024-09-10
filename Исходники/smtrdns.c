int smtrdns_init (void)
{
    AGENT  *agent;                      /*  Handle for our agent             */
    THREAD *thread;                     /*  Handle to various threads        */

#   include "smtrdns.i"                 /*  Include dialog interpreter       */

    /*  Shutdown event comes from Kernel                                     */
    declare_smtlib_shutdown   (shutdown_event,     SMT_PRIORITY_MAX);

    /*  Reply events from socket agent                                       */
    declare_smtsock_ok         (ok_event,           0);
    declare_smtsock_connect_ok (ok_event,           0);
    declare_smtsock_closed     (sock_closed_event,  0);
    declare_smtsock_error      (sock_error_event,   0);
    declare_smtsock_timeout    (sock_timeout_event, 0);

    /*  Public methods supported by this agent                               */
    declare_smtrdns_get_host_name (get_host_event,     0);
    declare_smtrdns_get_host_ip   (get_ip_event,       0);

    /*  Reply events from timer agent                                        */
    declare_smttime_reply     (timer_event,      SMT_PRIORITY_LOW);

    /*  Private methods used to pass initial thread events                   */
    method_declare (agent, "_MASTER",        master_event,    0);
    method_declare (agent, "_CLIENT",        client_event,    0);

    /*  Ensure that operator console is running, else start it up            */
    smtoper_init ();
    if ((thread = thread_lookup (SMT_OPERATOR, "")) != NULL)
        operq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that socket i/o agent is running, else start it up            */
    smtsock_init ();
    if ((thread = thread_lookup (SMT_SOCKET, "")) != NULL)
        sockq = thread-> queue-> qid;
    else
        return (-1);

    /*  Ensure that timer agent is running, else start it up                 */
    if (smttime_init ())
        return (-1);

    /*  Create initial thread to manage master port                          */
    if ((thread = thread_create (AGENT_NAME, "")) != NULL)
      {
        SEND (&thread-> queue-> qid, "_MASTER", "");
        ((TCB *) thread-> tcb)-> thread_type = master_event;
      }
    else
        return (-1);

    /*  Signal okay to caller that we initialised okay                       */
    return (0);
}
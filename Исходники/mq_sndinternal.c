int mq_waitsend(mqd_t mqdes)
{
  FAR struct tcb_s *rtcb;
  FAR struct mqueue_inode_s *msgq;

  /* Get a pointer to the message queue */

  msgq = mqdes->msgq;

  /* Verify that the queue is indeed full as the caller thinks */

  if (msgq->nmsgs >= msgq->maxmsgs)
    {
      /* Should we block until there is sufficient space in the
       * message queue?
       */

      if ((mqdes->oflags & O_NONBLOCK) != 0)
        {
          /* No... We will return an error to the caller. */

          set_errno(EAGAIN);
          return ERROR;
        }

      /* Yes... We will not return control until the message queue is
       * available or we receive a signal or at timout occurs.
       */

      else
        {
          /* Loop until there are fewer than max allowable messages in the
           * receiving message queue
           */

          while (msgq->nmsgs >= msgq->maxmsgs)
            {
              /* Block until the message queue is no longer full.
               * When we are unblocked, we will try again
               */

              rtcb = (FAR struct tcb_s *)g_readytorun.head;
              rtcb->msgwaitq = msgq;
              msgq->nwaitnotfull++;

              set_errno(OK);
              up_block_task(rtcb, TSTATE_WAIT_MQNOTFULL);

              /* When we resume at this point, either (1) the message queue
               * is no longer empty, or (2) the wait has been interrupted by
               * a signal.  We can detect the latter case be examining the
               * errno value (should be EINTR or ETIMEOUT).
               */

              if (get_errno() != OK)
                {
                  return ERROR;
                }
            }
        }
    }

  return OK;
}
/*!
 * Send message to queue or signal to thread
 */
int sys__msg_post ( int dest_type, void *dest, msg_t *msg, uint flags )
{
	thread_t *thr;
	kthread_t *kthr, *new_kthr;
	kthrmsg_qs *thrmsg;
	kgmsg_q *kgmsgq;
	kmsg_q *kmsgq;
	msg_q *msgq;
	kmsg_t *kmsg;
	msg_t *cmsg;

	ASSERT_ERRNO_AND_EXIT ( dest && msg, E_INVALID_HANDLE );

	if ( dest_type == MSG_THREAD || dest_type == MSG_SIGNAL )
	{
		thr = dest;
		kthr = k_get_kthread ( thr );
		ASSERT_ERRNO_AND_EXIT ( kthr, E_DONT_EXIST );
		thrmsg = k_get_thrmsg ( kthr );
		kmsgq = &thrmsg->msgq;
	}
	else if ( dest_type == MSG_QUEUE )
	{
		msgq = dest;
		kgmsgq = msgq->handle;
		ASSERT_ERRNO_AND_EXIT ( kgmsgq && kgmsgq->id == msgq->id,
					E_INVALID_HANDLE );
		kmsgq = &kgmsgq->mq;
	}
	else {
		EXIT ( E_INVALID_TYPE );
	}

	if ( dest_type == MSG_THREAD || dest_type == MSG_QUEUE )
	{
		/* send message to queue */
		if ( kmsgq->min_prio <= msg->type ) /* msg has required prio. */
		{
			kmsg = kmalloc ( sizeof (kmsg_t) + msg->size );
			ASSERT_ERRNO_AND_EXIT ( kmsg, E_NO_MEMORY );

			kmsg->msg.type = msg->type;
			kmsg->msg.size = msg->size;
			memcpy ( kmsg->msg.data, msg->data, msg->size );

			list_append ( &kmsgq->msgs, kmsg, &kmsg->list );

			/* is thread waiting for message? */
			if ( k_release_thread ( &kmsgq->thrq ) )
				k_schedule_threads ();

			EXIT ( SUCCESS );
		}
		else { /* ignore message */
			EXIT ( E_IGNORED );
		}
	}

	/* must be MSG_SIGNAL */
	if ( thrmsg->sig_prio <= msg->type )
	{
		/* create thread that will service this signal */

		cmsg = k_create_thread_private_storage ( kthr,
				sizeof (msg_t) + msg->size );
		cmsg->type = msg->type;
		cmsg->size = msg->size;
		memcpy ( cmsg->data, msg->data, msg->size );

		new_kthr = k_create_thread (
			thrmsg->signal_handler, cmsg, pi.exit,
			k_get_thread_prio ( kthr ) + 1, NULL, 0, 1
		);
		ASSERT_ERRNO_AND_EXIT ( new_kthr, k_get_errno() );

		k_set_thread_private_storage ( new_kthr, cmsg );

		SET_ERRNO ( SUCCESS );

		k_schedule_threads ();

		RETURN ( SUCCESS );
	}
	else { /* ignore signal */
		EXIT ( E_IGNORED );
	}
}
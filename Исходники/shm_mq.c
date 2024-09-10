/*
 * Receive a message from a shared message queue.
 *
 * We set *nbytes to the message length and *data to point to the message
 * payload.  If the entire message exists in the queue as a single,
 * contiguous chunk, *data will point directly into shared memory; otherwise,
 * it will point to a temporary buffer.  This mostly avoids data copying in
 * the hoped-for case where messages are short compared to the buffer size,
 * while still allowing longer messages.  In either case, the return value
 * remains valid until the next receive operation is perfomed on the queue.
 *
 * When nowait = false, we'll wait on our process latch when the ring buffer
 * is empty and we have not yet received a full message.  The sender will
 * set our process latch after more data has been written, and we'll resume
 * processing.  Each call will therefore return a complete message
 * (unless the sender detaches the queue).
 *
 * When nowait = true, we do not manipulate the state of the process latch;
 * instead, whenever the buffer is empty and we need to read from it, we
 * return SHM_MQ_WOULD_BLOCK.  In this case, the caller should call this
 * function again after the process latch has been set.
 */
shm_mq_result
shm_mq_receive(shm_mq_handle *mqh, Size *nbytesp, void **datap, bool nowait)
{
	shm_mq	   *mq = mqh->mqh_queue;
	shm_mq_result res;
	Size		rb = 0;
	Size		nbytes;
	void	   *rawdata;

	Assert(mq->mq_receiver == MyProc);

	/* We can't receive data until the sender has attached. */
	if (!mqh->mqh_counterparty_attached)
	{
		if (nowait)
		{
			if (shm_mq_get_sender(mq) == NULL)
				return SHM_MQ_WOULD_BLOCK;
		}
		else if (!shm_mq_wait_internal(mq, &mq->mq_sender, mqh->mqh_handle)
				 && shm_mq_get_sender(mq) == NULL)
		{
			mq->mq_detached = true;
			return SHM_MQ_DETACHED;
		}
		mqh->mqh_counterparty_attached = true;
	}

	/* Consume any zero-copy data from previous receive operation. */
	if (mqh->mqh_consume_pending > 0)
	{
		shm_mq_inc_bytes_read(mq, mqh->mqh_consume_pending);
		mqh->mqh_consume_pending = 0;
	}

	/* Try to read, or finish reading, the length word from the buffer. */
	while (!mqh->mqh_length_word_complete)
	{
		/* Try to receive the message length word. */
		Assert(mqh->mqh_partial_bytes < sizeof(Size));
		res = shm_mq_receive_bytes(mq, sizeof(Size) - mqh->mqh_partial_bytes,
								   nowait, &rb, &rawdata);
		if (res != SHM_MQ_SUCCESS)
			return res;

		/*
		 * Hopefully, we'll receive the entire message length word at once.
		 * But if sizeof(Size) > MAXIMUM_ALIGNOF, then it might be split over
		 * multiple reads.
		 */
		if (mqh->mqh_partial_bytes == 0 && rb >= sizeof(Size))
		{
			Size		needed;

			nbytes = *(Size *) rawdata;

			/* If we've already got the whole message, we're done. */
			needed = MAXALIGN(sizeof(Size)) + MAXALIGN(nbytes);
			if (rb >= needed)
			{
				/*
				 * Technically, we could consume the message length
				 * information at this point, but the extra write to shared
				 * memory wouldn't be free and in most cases we would reap no
				 * benefit.
				 */
				mqh->mqh_consume_pending = needed;
				*nbytesp = nbytes;
				*datap = ((char *) rawdata) + MAXALIGN(sizeof(Size));
				return SHM_MQ_SUCCESS;
			}

			/*
			 * We don't have the whole message, but we at least have the whole
			 * length word.
			 */
			mqh->mqh_expected_bytes = nbytes;
			mqh->mqh_length_word_complete = true;
			shm_mq_inc_bytes_read(mq, MAXALIGN(sizeof(Size)));
			rb -= MAXALIGN(sizeof(Size));
		}
		else
		{
			Size		lengthbytes;

			/* Can't be split unless bigger than required alignment. */
			Assert(sizeof(Size) > MAXIMUM_ALIGNOF);

			/* Message word is split; need buffer to reassemble. */
			if (mqh->mqh_buffer == NULL)
			{
				mqh->mqh_buffer = MemoryContextAlloc(mqh->mqh_context,
													 MQH_INITIAL_BUFSIZE);
				mqh->mqh_buflen = MQH_INITIAL_BUFSIZE;
			}
			Assert(mqh->mqh_buflen >= sizeof(Size));

			/* Copy and consume partial length word. */
			if (mqh->mqh_partial_bytes + rb > sizeof(Size))
				lengthbytes = sizeof(Size) - mqh->mqh_partial_bytes;
			else
				lengthbytes = rb;
			memcpy(&mqh->mqh_buffer[mqh->mqh_partial_bytes], rawdata,
				   lengthbytes);
			mqh->mqh_partial_bytes += lengthbytes;
			shm_mq_inc_bytes_read(mq, MAXALIGN(lengthbytes));
			rb -= lengthbytes;

			/* If we now have the whole word, we're ready to read payload. */
			if (mqh->mqh_partial_bytes >= sizeof(Size))
			{
				Assert(mqh->mqh_partial_bytes == sizeof(Size));
				mqh->mqh_expected_bytes = *(Size *) mqh->mqh_buffer;
				mqh->mqh_length_word_complete = true;
				mqh->mqh_partial_bytes = 0;
			}
		}
	}
	nbytes = mqh->mqh_expected_bytes;

	if (mqh->mqh_partial_bytes == 0)
	{
		/*
		 * Try to obtain the whole message in a single chunk.  If this works,
		 * we need not copy the data and can return a pointer directly into
		 * shared memory.
		 */
		res = shm_mq_receive_bytes(mq, nbytes, nowait, &rb, &rawdata);
		if (res != SHM_MQ_SUCCESS)
			return res;
		if (rb >= nbytes)
		{
			mqh->mqh_length_word_complete = false;
			mqh->mqh_consume_pending = MAXALIGN(nbytes);
			*nbytesp = nbytes;
			*datap = rawdata;
			return SHM_MQ_SUCCESS;
		}

		/*
		 * The message has wrapped the buffer.  We'll need to copy it in order
		 * to return it to the client in one chunk.  First, make sure we have
		 * a large enough buffer available.
		 */
		if (mqh->mqh_buflen < nbytes)
		{
			Size		newbuflen = Max(mqh->mqh_buflen, MQH_INITIAL_BUFSIZE);

			while (newbuflen < nbytes)
				newbuflen *= 2;

			if (mqh->mqh_buffer != NULL)
			{
				pfree(mqh->mqh_buffer);
				mqh->mqh_buffer = NULL;
				mqh->mqh_buflen = 0;
			}
			mqh->mqh_buffer = MemoryContextAlloc(mqh->mqh_context, newbuflen);
			mqh->mqh_buflen = newbuflen;
		}
	}

	/* Loop until we've copied the entire message. */
	for (;;)
	{
		Size		still_needed;

		/* Copy as much as we can. */
		Assert(mqh->mqh_partial_bytes + rb <= nbytes);
		memcpy(&mqh->mqh_buffer[mqh->mqh_partial_bytes], rawdata, rb);
		mqh->mqh_partial_bytes += rb;

		/*
		 * Update count of bytes read, with alignment padding.  Note that this
		 * will never actually insert any padding except at the end of a
		 * message, because the buffer size is a multiple of MAXIMUM_ALIGNOF,
		 * and each read and write is as well.
		 */
		Assert(mqh->mqh_partial_bytes == nbytes || rb == MAXALIGN(rb));
		shm_mq_inc_bytes_read(mq, MAXALIGN(rb));

		/* If we got all the data, exit the loop. */
		if (mqh->mqh_partial_bytes >= nbytes)
			break;

		/* Wait for some more data. */
		still_needed = nbytes - mqh->mqh_partial_bytes;
		res = shm_mq_receive_bytes(mq, still_needed, nowait, &rb, &rawdata);
		if (res != SHM_MQ_SUCCESS)
			return res;
		if (rb > still_needed)
			rb = still_needed;
	}

	/* Return the complete message, and reset for next message. */
	*nbytesp = nbytes;
	*datap = mqh->mqh_buffer;
	mqh->mqh_length_word_complete = false;
	mqh->mqh_partial_bytes = 0;
	return SHM_MQ_SUCCESS;
}
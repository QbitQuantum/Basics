/* This is a bit skanky.  If we're transmitting, and we need to block
   because the ring's full, we first pull all of the *incoming*
   messages off of the ring into local buffers.  This unblocks the
   remote, which helps to avoid deadlocks. */
static void
v2v_pull_incoming_messages(struct v2v_stream *stream)
{
    struct queued_message *qm;
    const volatile void *payload;
    size_t size;
    unsigned type;
    unsigned flags;

    /* If we're processing an in-ring message, copy it out of the ring
       and into the local queue. */
    if (stream->recv_state.current_message ==
        &stream->recv_state.in_ring_message) {       
		qm = ExAllocatePoolWithTag((stream->nonpaged ? NonPagedPool : PagedPool),
								   sizeof(*qm) + stream->recv_state.in_ring_message.size,
								   V2V_TAG);
        *qm = stream->recv_state.in_ring_message;
        qm->payload = qm + 1;
        _ReadWriteBarrier();
        RtlCopyMemory(qm->payload,
                      stream->recv_state.in_ring_message.payload,
                      qm->size);
        _ReadWriteBarrier();
        stream->recv_state.current_message = qm;

        v2v_nc2_finish_message(stream->channel);

        stream->recv_state.current_message = qm;
    }
    /* Pull all of the messages out of the ring and into the local
       queue. */
    while (v2v_nc2_get_message(stream->channel, &payload, &size,
                               &type, &flags) == STATUS_SUCCESS) {
		qm = ExAllocatePoolWithTag((stream->nonpaged ? NonPagedPool : PagedPool),
								   sizeof(*qm) + size,
								   V2V_TAG);
        qm->next = NULL;
        qm->size = size;
        qm->type = type;
        qm->flags = flags;
        qm->bytes_already_used = 0;
        qm->payload = qm + 1;
        _ReadWriteBarrier();
        RtlCopyMemory(qm->payload, (const void *)payload, size);
        _ReadWriteBarrier();
        v2v_nc2_finish_message(stream->channel);

        *stream->recv_state.queue.tail = qm;
        stream->recv_state.queue.tail = &qm->next;
    }
}
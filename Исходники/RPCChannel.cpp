void
RPCChannel::OnMessageReceivedFromLink(const Message& msg)
{
    AssertLinkThread();
    mMonitor->AssertCurrentThreadOwns();

    if (MaybeInterceptSpecialIOMessage(msg))
        return;

    // regardless of the RPC stack, if we're awaiting a sync reply, we
    // know that it needs to be immediately handled to unblock us.
    if (AwaitingSyncReply() && msg.is_sync()) {
        // wake up worker thread waiting at SyncChannel::Send
        mRecvd = msg;
        NotifyWorkerThread();
        return;
    }

    MessageQueue *queue = (msg.priority() == IPC::Message::PRIORITY_HIGH)
                          ? &mUrgent
                          : &mPending;

    bool compressMessage = (msg.compress() && !queue->empty() &&
                            queue->back().type() == msg.type() &&
                            queue->back().routing_id() == msg.routing_id());
    if (compressMessage) {
        // This message type has compression enabled, and the back of
        // the queue was the same message type and routed to the same
        // destination.  Replace it with the newer message.
        MOZ_ASSERT(queue->back().compress());
        queue->pop_back();
    }

    queue->push_back(msg);

    // There are three cases we're concerned about, relating to the state of
    // the main thread:
    //
    // (1) We are waiting on a sync reply - main thread is blocked on the IPC monitor.
    //   - If the message is high priority, we wake up the main thread to
    //     deliver the message. Otherwise, we leave it in the mPending queue,
    //     posting a task to the main event loop, where it will be processed
    //     once the synchronous reply has been received.
    //
    // (2) We are waiting on an RPC reply - main thread is blocked on the IPC monitor.
    //   - Always wake up the main thread to deliver the message.
    //
    // (3) We are not waiting on a reply.
    //   - We post a task to the main event loop.
    //
    bool waiting_rpc = (0 != StackDepth());
    bool urgent = (msg.priority() == IPC::Message::PRIORITY_HIGH);

    if (waiting_rpc || (AwaitingSyncReply() && urgent)) {
        // Always wake up our RPC waiter, and wake up sync waiters for urgent
        // messages.
        NotifyWorkerThread();
    } else {
        // Worker thread is either not blocked on a reply, or this is an
        // incoming RPC that raced with outgoing sync and needs to be deferred
        // to a later event-loop iteration.
        if (!compressMessage) {
            // If we compressed away the previous message, we'll reuse
            // its pending task.
            mWorkerLoop->PostTask(FROM_HERE, new DequeueTask(mDequeueOneTask));
        }
    }
}
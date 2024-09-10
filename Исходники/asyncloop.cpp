void AsyncLoopSocket(boost::function<TaskState()> doWork, boost::asio::ip::tcp::socket& sock, bool isRead)
{
    if (sock.get_io_service().stopped())
    {
        return;
    }

    TaskState st = doWork();

    if (st == TASK_WORKING)
    {
        if (isRead)
        {
            sock.async_read_some(boost::asio::null_buffers(), bind(AsyncLoopSocket, doWork, boost::ref(sock),
                isRead));
        }
        else
        {
            sock.async_write_some(boost::asio::null_buffers(), bind(AsyncLoopSocket, doWork, boost::ref(sock),
                isRead));
        }

        return;
    }

    // Work is over. stop any outstanding events.
    // NOTE: this isn't 100% reliable, and there may be events that linger in the queue.
    // The next time we reset() and run() the io_service, these events will be processed,
    // and io_service::stopped() will return false, because we've just done reset() and run().
    // The state management (SSHSession::State) is our first step in controlling this, and we
    // may need to implement our own cancel mechanism
    //
    // this io_service feature poses an additional problem - by spreading the implementation
    // responsibility across multiple classes, we create scenarios where io_service's queue
    // may contain outstanding events referring to objects that were, in the meantime, destroyed.
    // this is why we're favouring, for now, the use of AsyncLoopTimer, where we can use an
    // io_service for each timer, and destroy it right after being used. this makes sure we
    // process no "zombie" outstanding events.
    sock.get_io_service().stop();
}
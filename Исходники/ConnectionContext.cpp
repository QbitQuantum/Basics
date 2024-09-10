void ConnectionContext::send(boost::shared_ptr<SenderContext> snd, const qpid::messaging::Message& message, bool sync)
{
    qpid::sys::ScopedLock<qpid::sys::Monitor> l(lock);
    SenderContext::Delivery* delivery(0);
    while (!(delivery = snd->send(message))) {
        QPID_LOG(debug, "Waiting for capacity...");
        wait();//wait for capacity
    }
    wakeupDriver();
    if (sync) {
        while (!delivery->accepted()) {
            QPID_LOG(debug, "Waiting for confirmation...");
            wait();//wait until message has been confirmed
        }
    }
}
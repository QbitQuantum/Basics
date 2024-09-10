ECode ThreadPoolExecutor::Purge()
{
    AutoPtr<IBlockingQueue> q = mWorkQueue;
    // try {
    AutoPtr<IIterator> it;
    IIterable::Probe(q)->GetIterator((IIterator**)&it);
    Boolean hasNext;
    while (it->HasNext(&hasNext), hasNext) {
        AutoPtr<IInterface> obj;
        it->GetNext((IInterface**)&obj);
        IRunnable* r = IRunnable::Probe(obj);
        Boolean isCancelled;
        if (IFuture::Probe(r) &&
                (IFuture::Probe(r)->IsCancelled(&isCancelled), isCancelled)) {
            it->Remove();
        }
    }
    // } catch (ConcurrentModificationException fallThrough) {
    //     // Take slow path if we encounter interference during traversal.
    //     // Make copy for traversal and call remove for cancelled entries.
    //     // The slow path is more likely to be O(N*N).
    //     for (Object r : q.toArray())
    //         if (r instanceof Future<?> && ((Future<?>)r).isCancelled())
    //             q.remove(r);
    // }

    TryTerminate(); // In case SHUTDOWN and now empty
    return NOERROR;
}
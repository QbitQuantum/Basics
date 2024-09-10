void BitcoinP2P::connectToNode(bool async)
{
   unique_lock<mutex> lock(connectMutex_, defer_lock);

   if (!lock.try_lock()) //return if another thread is already here
      throw SocketError("another connect attempt is underway");

   connectedPromise_ = unique_ptr<promise<bool>>(new promise<bool>());
   auto connectedFuture = connectedPromise_->get_future();

   auto connectLambda = [this](void)->void
   {
      this->connectLoop();
   };

   thread connectthread(connectLambda);
   if (connectthread.joinable())
      connectthread.detach();

   if (async)
      return;

   connectedFuture.get();

   if (select_except_ != nullptr)
      rethrow_exception(select_except_);

   if (process_except_ != nullptr)
      rethrow_exception(process_except_);
}
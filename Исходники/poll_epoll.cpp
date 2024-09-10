  // We check table_ to make sure the Event is still listening to the
  // event, so it is safe to remove Event's while in working.
  //
  // TODO: Do we want to guarantee if the Event has been removed from
  // some event but not closed, it won't call that event? Think so...
  void PollEPoll::Perform() {
    for (epoll_event *itr = events_, *last = events_ + waiting_events_; itr != last; ++itr) {
      Event* event = static_cast<Event*>(itr->data.ptr);

      // Each branch must check for data.ptr != 0 to allow the socket
      // to remove itself between the calls.
      //
      // TODO: Make it so that it checks that read/write is wanted, that
      // it wasn't removed from one of them but not closed.

      if (itr->events & EPOLLERR && event && !event->IsInactive() && EventMask_(event) & EPOLLERR) {
        event->EventError();
      }

      if (itr->events & EPOLLIN && event && !event->IsInactive() && EventMask_(event) & EPOLLIN) {
        event->EventRead();
      }

      if (itr->events & EPOLLOUT && event && !event->IsInactive() && EventMask_(event) & EPOLLOUT) {
        event->EventWrite();
      }
    }

    waiting_events_ = 0;
  }
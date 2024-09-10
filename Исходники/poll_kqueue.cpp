  void PollKQueue::Perform() {
    for (struct kevent *itr = events_, *last = events_ + waiting_events_; itr != last; ++itr) {
      Event* event = static_cast<Event*>(itr->udata);

      // Error messages that can happen, when a delete fails.
      //   EBADF happens when the file discriptor has been closed,
      //   ENOENT when the file discriptor was closed and then reopened.
      //   EINVAL for some reasons not understood; EINVAL should not be returned ever, but sometimes does.
      // An error is also indicated when a callback deletes an event we are still processing.
      // In that case the data field is set to ENOENT.

      if (itr->flags == EV_ERROR) {
        int err = itr->data;
        if (err == EBADF || err == EINVAL || err == ENOENT) {
          continue;
        }

        base_throw(IOException, "kqueue error for descriptor " + base::ToString(event->Descriptor()) + " : "
                   + base::ToString(err) + " - " + ::strerror(err));
      }

      // Also check current mask.
      if (itr->filter == EVFILT_READ && event && !event->IsInactive() && EventMask_(event) & flag_read) {
        event->EventRead();
      }

      if (itr->filter == EVFILT_WRITE && event && !event->IsInactive() && EventMask_(event) & flag_write) {
        event->EventWrite();
      }
    }

    waiting_events_ = 0;
  }
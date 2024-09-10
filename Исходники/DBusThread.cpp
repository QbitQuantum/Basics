bool
DBusWatcher::Poll()
{
  int res = TEMP_FAILURE_RETRY(poll(mPollData.Elements(),
                                    mPollData.Length(), -1));
  NS_ENSURE_TRUE(res > 0, false);

  bool continueThread = true;

  nsTArray<pollfd>::size_type i = 0;

  while (i < mPollData.Length()) {
    if (mPollData[i].revents == POLLIN) {
      if (mPollData[i].fd == mControlFdR.get()) {
        char data;
        res = TEMP_FAILURE_RETRY(read(mControlFdR.get(), &data, sizeof(data)));
        NS_ENSURE_TRUE(res > 0, false);

        switch (data) {
          case DBUS_EVENT_LOOP_EXIT:
            continueThread = false;
            break;
          case DBUS_EVENT_LOOP_ADD:
            HandleWatchAdd();
            break;
          case DBUS_EVENT_LOOP_REMOVE:
            HandleWatchRemove();
            // don't increment i, or we'll skip one element
            continue;
          case DBUS_EVENT_LOOP_WAKEUP:
            NS_ProcessPendingEvents(NS_GetCurrentThread(),
                                    PR_INTERVAL_NO_TIMEOUT);
            break;
          default:
#if DEBUG
            nsCString warning("unknown command ");
            warning.AppendInt(data);
            NS_WARNING(warning.get());
#endif
            break;
        }
      } else {
        short events = mPollData[i].revents;
        mPollData[i].revents = 0;

        dbus_watch_handle(mWatchData[i], UnixEventsToDBusFlags(events));

        DBusDispatchStatus dbusDispatchStatus;
        do {
          dbusDispatchStatus = dbus_connection_dispatch(GetConnection());
        } while (dbusDispatchStatus == DBUS_DISPATCH_DATA_REMAINS);

        // Break at this point since we don't know if the operation
        // was destructive
        break;
      }
    }

    ++i;
  }

  return continueThread;
}
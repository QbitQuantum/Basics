    void
    terminate(void)
    {
      refresh_timer_.terminate();

      clear_xml();

      IOLockWrapper::free(lock_);
    }
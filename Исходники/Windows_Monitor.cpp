    void
    Windows_Monitor::update_i (void)
    {
      PdhCollectQueryData (this->query_);
      PDH_FMT_COUNTERVALUE pdh_value;

      PdhGetFormattedCounterValue (this->counter_,
                                   PDH_FMT_DOUBLE,
                                   0,
                                   &pdh_value);

      this->value_ = pdh_value.doubleValue;
    }
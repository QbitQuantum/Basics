  // ======================================================================
  void
  EventInputQueue::fire_timer_callback(OSObject* /*notuse_owner*/, IOTimerEventSource* /*notuse_sender*/)
  {
    if (! queue_) return;

    // IOLOG_DEVEL("EventInputQueue::fire queue_->size = %d\n", static_cast<int>(queue_->size()));

    // ------------------------------------------------------------
    // handle SimultaneousKeyPresses
    do {
      Item* front = static_cast<Item*>(queue_->front());
      if (! front) return;

      // ------------------------------------------------------------
      // clear temporary_count_
      //
      // Don't call FlagStatus::set(key, flags) here.
      // If SimultaneousKeyPresses is enabled, keys may be dropped.
      // For example, Shift_L+Shift_R to Space is enabled, Shift_L and Shift_R may be dropped.
      // If we call FlagStatus::set(key, flags) here, dropped keys are kept as pushed status.
      // So, call FlagStatus::set(key, flags) after EventInputQueue.
      // ------------------------------------------------------------
      if (! front->retainFlagStatusTemporaryCount) {
        FlagStatus::globalFlagStatus().set();
      }

      CommonData::setcurrent_deviceIdentifier(front->deviceIdentifier);
      {
        Params_KeyboardEventCallBack* params = (front->params).get_Params_KeyboardEventCallBack();
        if (params) {
          CommonData::setcurrent_keyboardType(params->keyboardType);
        }
      }

    } while (RemapClassManager::remap_simultaneouskeypresses());

    // ------------------------------------------------------------
    // handle BlockUntilKeyUp
    //
    // Note:
    // We need to handle BlockUntilKeyUp after SimultaneousKeyPresses
    // in order to avoid unintended modification by SimultaneousKeyPresses.
    bool needToFire = BlockUntilKeyUpHander::doBlockUntilKeyUp();
    if (needToFire) {
      doFire();
    }

    setTimer();
  }
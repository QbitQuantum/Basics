BOOL freespace_private_discoveryStatusChanged() {
    if ( freespace_instance_->needToRescanDevicesFlag_ || 
         WaitForSingleObject(freespace_instance_->discoveryEvent_, 0) == WAIT_OBJECT_0) {
        // Race condition note: the flags need to be reset before the scan takes
        // place. If device status changes again between when this thread is notified
        // and the flags get reset, we're ok, since the scan happens afterwards. If the
        // change occurs after the reset of the flags, the flags will be set again, and
        // we'll scan next trip around the event loop.
        freespace_instance_->needToRescanDevicesFlag_ = FALSE;

        // Force the timer to unsignaled by restarting and then cancelling.
        freespace_private_requestDeviceRescan();
        CancelWaitableTimer(freespace_instance_->discoveryEvent_);

        return TRUE;
    } else {
        return FALSE;
    }
}
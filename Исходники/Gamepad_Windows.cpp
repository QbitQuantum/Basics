 void Gamepad_Windows::destroy() {
     if (_reader_thread_handle) {
         DWORD errcode = ERROR_OBJECT_NOT_FOUND;
         if (_input_received_event)
             SetEvent(_input_received_event);
         if (_thread_exit_event)
             errcode = SignalObjectAndWait(_thread_exit_event, _reader_thread_handle, 1000, false);
         if (errcode)
             TerminateThread(_reader_thread_handle, errcode);
         CloseHandle(_reader_thread_handle);
         _reader_thread_handle = NULL;
     }
     if (_input_received_event) {
         CloseHandle(_input_received_event);
         _input_received_event = NULL;
     }
     if (_thread_exit_event) {
         CloseHandle(_thread_exit_event);
         _thread_exit_event = NULL;
     }
     if (_preparsed) {
         hid.HidD_FreePreparsedData(_preparsed);
         _preparsed = NULL;
     }
     if (_notif_handle != NULL) {
         UnregisterDeviceNotification(_notif_handle);
         _notif_handle = NULL;
     }
     if (_handle != INVALID_HANDLE_VALUE) {
         CloseHandle(_handle);
         _handle = INVALID_HANDLE_VALUE;
     }
 }
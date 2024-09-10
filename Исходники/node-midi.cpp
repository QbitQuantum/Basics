 ~NodeMidiInput()
 {
     in->closePort();
     delete in;
     uv_mutex_destroy(&message_mutex);
 }
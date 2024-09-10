 int Shm::unregister_server (const char * /* server_name */) {
     int i;
     if (shm_lock_registry () < 0) {
         jack_error ("jack_shm_lock_registry fails...");
         return -1;
     }
     
     for (i = 0; i < MAX_SERVERS; i++) {
         if (jack_shm_header->server[i].pid == GetPID()) {
             memset (&jack_shm_header->server[i], 0,
                 sizeof (jack_shm_server_t));
         }
     }
     
     shm_unlock_registry ();
     return 0;
 }
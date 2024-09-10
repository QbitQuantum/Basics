static void *clearThread( void *nul)
{
    while( !nul && !READ_ATOMIC_D( s_received_signal)) {
    FILES * first;
    time_t now;
    int cnt = 0;

        pthread_mutex_lock( &files_mutex);
        first = receiving_files;
        while( first) {
            first = first->next;
            cnt++;
        }
        pthread_mutex_unlock( &files_mutex);
        if( cnt) {
            printf( "Cache Clearance %d\r\n", cnt);
            time( &now);
            pthread_mutex_lock( &files_mutex);
            first = receiving_files;
            while( first) {
    //          printf( "File %s serving %d, %d seconds old\r\n", first->name, first->serving, now-first->first_usage);
                if( !first->serving && now>=first->first_usage) {
                FILES *ptr = first->next;

                    first = localFree( first, 1);
                }
                else {
                    first = first->next;
                }
            }
            pthread_mutex_unlock( &files_mutex);
        }
        sleep( M3U8_EXPIRY-1);
  }

  return NULL;
}
void *minstack_tcp_reading_thread(void *ptr) {
    minstack_tcp *mt = (minstack_tcp *) ptr;
    fd_set fds_read;
    int fdmax;
    struct timeval tv;

    printdebug("starting %s\n",__FUNCTION__);
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

    mt->pthread_reading_thread_stop = 0;
    while (!mt->pthread_reading_thread_stop) {
        int i, retval, socket_to_read = -1;
        fdmax = 0;
        tv.tv_sec = 0;
        tv.tv_usec = (mt->receive_loop_usleep);
        FD_ZERO(&fds_read);
        pthread_mutex_lock(&mt->mutex);
        if (mt->sockets.connected_client_nb == 0) {
            pthread_mutex_unlock(&mt->mutex);
            usleep(mt->receive_loop_usleep);
            //printdebug("there is no client\n");
#ifdef	STOP_READING_THREAD_WITHOUT_CLIENTS
            break;
#else
            continue;
#endif
        }
        for (i = 0; i < mt->sockets.connected_client_nb; i++) {
            printdebug("Stay socket %d\n",mt->sockets.client_socket_fd[i]);
            FD_SETMAX(mt->sockets.client_socket_fd[i],&fds_read,fdmax);
        }
        fdmax++;
        pthread_mutex_unlock(&mt->mutex);

        retval = select(fdmax, &fds_read, NULL, NULL, &tv);
        pthread_mutex_lock(&mt->mutex);
        if (retval == EBADF) {
            printmoreerror("Select Bad FD\n");
            continue;
        }
        if (retval < 0) {
            printerror("Select: got an error %d\n",retval);
            printmoreerror("Select:");
            break;
        }
        if (retval) {
            printdebug("there is something to read\n");
            for (i = 0; i < mt->sockets.connected_client_nb; i++) {
                if (FD_ISSET(mt->sockets.client_socket_fd[i],&fds_read)) {
                    socket_to_read = mt->sockets.client_socket_fd[i];
                }
            }
        }
        if (!retval) {
            //printmoreerror("Nothing much from the select\n");
        }
        pthread_mutex_unlock(&mt->mutex);
        if (socket_to_read > 0) {
        	char from[16];
            char *buffer=NULL;
            int buffer_size = 0;
            pthread_mutex_lock(&mt->mutex);
            pthread_mutex_unlock(&mt->mutex);
            buffer_size = mt->read_socket(socket_to_read, from,&buffer);

            if (buffer_size <= 0) {
                pthread_mutex_lock(&mt->mutex);
                if (mt && mt->connection_closed_callback
                        && (mt->type == SERVER)) {
                    mt->connection_closed_callback(&mt->sockets, socket_to_read);
                    minstack_close(socket_to_read);
                    printdebug("Closing the socket %d\n",socket_to_read);
                }
                pthread_mutex_unlock(&mt->mutex);
                if (mt && (mt->type == CLIENT)) {
                    printmessage("The server do not exists anymore we will close the connection\n");
                    minstack_close(socket_to_read);
                    minstack_tcp_stop(mt);
                }
            } else {
                printmessage("%s received from %s(%d):(%u)=>%s\n",mt->name,from, socket_to_read,buffer_size,buffer);
                if (mt->external_read_socket)
                    mt->external_read_socket(socket_to_read, from, buffer, buffer_size);
                //else
                free(buffer);
            }
        }

    }
    mt->pthread_reading_thread_stop = 1;
    printdebug("stopping %s\n",__FUNCTION__);
    pthread_exit(NULL);
    return NULL;
}
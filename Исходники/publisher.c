int
main_program(int num_messages, int num_channels, int num_connections, const char *server_hostname, int server_port, int timeout)
{
    struct sockaddr_in server_address;
    int main_sd = -1, num_events = 0, i, event_mask, channels_per_connection, num, start_time = 0, iters_to_next_summary = 0;
    Connection *connections = NULL, *connection;
    Statistics stats = {0,0,0,0,0};
    int exitcode = EXIT_SUCCESS;
    struct epoll_event events[MAX_EVENTS];
    char buffer[BIG_BUFFER_SIZE];

    info("Publisher starting up\n");
    info("Publish: %d messages to %d channels on server: %s:%d\n", num_messages, num_channels, server_hostname, server_port);

    if ((fill_server_address(server_hostname, server_port, &server_address)) != 0) {
        error2("ERROR host name not found\n");
    }

    if ((main_sd = epoll_create(200 /* this size is not used on Linux kernel 2.6.8+ */)) < 0) {
        error3("Failed %d creating main epoll socket\n", errno);
    }

    if ((connections = init_connections(num_connections, &server_address, main_sd)) == NULL) {
        error2("Failed to create to connections\n");
    }

    stats.requested_connections = num_connections;

    channels_per_connection = num_channels / num_connections;
    for (i = 0; i < num_connections; i++) {
        num = i * channels_per_connection;
        connections[i].channel_start = num;
        num += channels_per_connection - 1;
        connections[i].channel_end = ((num > num_channels) || (i == (num_connections - 1))) ? num_channels - 1 : num;
    }

    // infinite loop
    debug("Entering Infinite Loop\n");

    iters_to_next_summary = ITERATIONS_TILL_SUMMARY_PER_TIMEOUT/timeout;

    for(;;) {
        if ((num_events = epoll_wait(main_sd, events, MAX_EVENTS, timeout)) < 0) {
            error3("epoll_wait failed\n");
        }

        for (i = 0; i < num_events; i++) {
            event_mask = events[i].events;
            connection = (Connection *)(events[i].data.ptr);

            if ((connection->message_count >= num_messages) && (connection->channel_id > connection->channel_end)) {
                // remove write flag from event
                if (change_connection(connection, EPOLLIN | EPOLLHUP) < 0) {
                    error2("Failed creating socket for connection = %d\n", connection->index);
                }

                if (event_mask & EPOLLOUT) { // WRITE
                    continue;
                }
            }

            if (event_mask & EPOLLHUP) { // SERVER HUNG UP
                debug("EPOLLHUP\n");
                info("Server hung up on conncetion %d. Reconecting...\n", connection->index);
                sleep(1);
                reopen_connection(connection);

                continue;
            }

            if (event_mask & EPOLLERR) {
                debug("EPOLLERR\n");
                info("Server returned an error on connection %d. Reconecting...\n", connection->index);
                reopen_connection(connection);

                continue;
            }

            if (event_mask & EPOLLIN) { // READ
                debug("----------READ AVAILABLE-------\n");

                if (connection->state == CONNECTED) {
                    read_response(connection, &stats, buffer, BIG_BUFFER_SIZE);
                }
            }

            if (event_mask & EPOLLOUT) { // WRITE
                debug("----------WRITE AVAILABLE-------\n");

                if (start_time == 0) {
                    start_time = time(NULL);
                }

                if (connection->state == CONNECTING) {
                    connection->state = CONNECTED;
                    stats.connections++;
                    debug("Connection opened for index=%d\n", connection->index);
                }

                write_message(connection, &stats);
            }
        }

        if (iters_to_next_summary-- <= 0) {
            iters_to_next_summary = ITERATIONS_TILL_SUMMARY_PER_TIMEOUT/timeout;
            summary("Connections=%ld, Messages=%ld BytesWritten=%ld Msg/Sec=%0.2f\n", stats.connections, stats.messages, stats.bytes_written, calc_message_per_second(stats.messages, start_time));
        }

        if (stats.messages >= (num_channels * num_messages)) {
            summary("Connections=%ld, Messages=%ld BytesWritten=%ld Msg/Sec=%0.2f\n", stats.connections, stats.messages, stats.bytes_written, calc_message_per_second(stats.messages, start_time));
            for (i = 0; i < num_connections; i++) {
                close_connection(&connections[i]);
                stats.connections--;
            }
            exitcode = EXIT_SUCCESS;
            goto exit;
        }
    }


exit:
    if (connections != NULL) free(connections);

    return exitcode;
}
void rcopy_runloop(char *server_host, uint16_t server_port, char *remote_file_name, char *output_file_name, uint32_t buf_size, uint32_t window_size)
{
	int output_fd = -1;
	int select_count = 0;
	int state = STATE_FILENAME;
	Window *window = NULL;

	while (state != STATE_DONE) {
		switch (state) {

			case STATE_FILENAME:
				if (connectToServer(server_host, server_port, &server)) {
					perror("ERROR: unable to connect to host");
					exit(1);
				}
				state = filename(remote_file_name, buf_size, window_size);
				if (state == STATE_FILENAME) {
					close(server.socket_num);
				}
				select_count++;
				if (select_count >= MAX_RETRIES) {
					fprintf(stderr, "Ten failed filename tries: unable to reach server\n");
					exit(1);
				}
				break;

			case STATE_FILE_OK:
				select_count = 0;
				if((output_fd = open(output_file_name, O_WRONLY|O_CREAT|O_TRUNC, 0600)) < 0 ) {
			    	perror("Open local_file");
			    	exit(1);
			    }
			    window = newWindowWithSizeAndBuffer(window_size, buf_size);
			    state = STATE_RECV_DATA;
			    break;

			case STATE_RECV_DATA:
				state = recv_data(window);
				break;

			case STATE_WINDOW_FULL:
				state = window_full(window, output_fd);
				clearWindow(window);
				window->base_seq_num += window->window_size;
				window->buffer_size = 0;
				break;

			case STATE_EOF:
				if (select_count == 0) {
					window_full(window, output_fd);
				}
				select_count++;
				if (select_count >= MAX_RETRIES) {
					fprintf(stderr, "Ten failed EOF acks: file is ok but server doesn't know\n");
					state = STATE_DONE;
				}
				else {
					state = recv_eof(window, output_fd);
				}
				break;

			case STATE_DONE:
			default:
				break;
		}
	}

	if (window != NULL) {
		destroyWindow(window);
		window = NULL;
	}

	close(output_fd);
}
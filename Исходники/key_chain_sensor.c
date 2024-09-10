void* set_value_thread(void *context)
{
	sensor_context *sensor = NULL;
	message msg;
	int return_value;
	char *tokens[10];
	char line[LINE_MAX];
	int count = 0;
	int start, end, value;

	sensor = (sensor_context*)context;

	msg.type = CURRENT_VALUE;
	while(sensor->run)
	{
		if(!(start <= sensor->clock && sensor->clock < end))
		{
			/* Figure out the value from file */
			if(fgets(line, LINE_MAX, sensor->sensor_value_file_pointer) == NULL)
			{
				LOG_DEBUG(("DEBUG: Seeking to beginning of file"));
				rewind(sensor->sensor_value_file_pointer);
				sensor->clock = 0;
				continue;
			}

			str_tokenize(line, ";\n\r", tokens, &count);
			if(count != 3)
			{
				LOG_ERROR(("ERROR: Wrong sensor temperature value file\n"));
				break;
			}

			start = atoi(tokens[0]);
			end = atoi(tokens[1]);
			if(strcmp (tokens[2], "true") == 0)
			{
				value = 1; 
			}
			else
			{
				value = 0;
			}
			sensor->value = value;
		}

		msg.u.value = sensor->value;
		msg.timestamp = time(NULL);

		pthread_mutex_lock(&sensor->mutex_lock);

		sensor->logical_clock[2]++;
		LOG_SCREEN(("INFO: Event Sent, "));
		LOG_INFO(("INFO: Event Sent, "));
		print_logical_clock_to_screen(sensor->logical_clock);
		print_logical_clock(sensor->logical_clock);
		LOG_INFO(("timestamp: %lu, Motion: %s\n", msg.timestamp, tokens[2]));
		LOG_SCREEN(("timestamp: %lu, Motion: %s\n", msg.timestamp, tokens[2]));
		return_value = write_message(sensor->socket_fd, sensor->logical_clock, &msg);
		if(E_SUCCESS != return_value)
		{
			LOG_ERROR(("ERROR: Error in sending sensor temperature value to gateway\n"));
		}

		for(int index=0; index<sensor->send_peer_count; index++)
		{
			return_value = write_message(sensor->send_peer[index]->comm_socket_fd,
					sensor->logical_clock,
					&msg);
			if(E_SUCCESS != return_value)
			{
				LOG_ERROR(("ERROR: Error in sending sensor temperature value to peer\n"));
			}
		}
		pthread_mutex_unlock(&sensor->mutex_lock);

		sleep(sensor->interval);
		sensor->clock += sensor->interval;
	}

	LOG_DEBUG(("Exiting SetValueThread...\n"));
	return (NULL);
}
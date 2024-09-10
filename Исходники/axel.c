/* Main 'loop' */
void axel_do(axel_t *axel)
{
#if WIN32
	WSAEVENT hEventObject = WSACreateEvent();
	DWORD byte;
#else
	fd_set fds[1];
	struct timeval timeval[1];
	int hifd;
#endif
	int i;
	long long int remaining, size;

	/* Create statefile if necessary */
	if (axel->next_state < gettime())
	{
		save_state(axel);
		axel->next_state = gettime() + axel->conf->save_state_interval;
	}

	/* Wait for data on (one of) the connections */
#if !WIN32
	FD_ZERO(fds);
	hifd = 0;
	for (i = 0; i < axel->conf->num_connections; i++)
	{
		if (axel->conn[i].enabled) 
		{
			FD_SET(axel->conn[i].fd, fds);
		}
		hifd = max(hifd, axel->conn[i].fd);
	}

	if (0 == hifd)
	{
#ifdef DEBUG
		printf("DEBUG no connection yet. Wait...\n");
#endif
		/* No connections yet. Wait... */
		usleep(100000);
		goto conn_check;
	}
	else
	{
		timeval->tv_sec = 0;
		timeval->tv_usec = 100000;
		/* A select() error probably means it was interrupted
		   by a signal, or that something else's very wrong...	*/
		if (-1 == select(hifd + 1, fds, NULL, NULL, timeval))
		{
			axel->ready = -1;
			return;
		}
	}
#endif

	/* Handle connections which need attention */
	for (i = 0; i < axel->conf->num_connections; i++) 
	{
		if (axel->conn[i].enabled) 
		{
#if WIN32
			if (is_readable(axel, axel->conn[i].fd, hEventObject))
#else
			if (FD_ISSET(axel->conn[i].fd, fds))
#endif
			{
				axel->conn[i].last_transfer = gettime();
#if WIN32
				memset(buffer, 0, max(MAX_STRING, axel->conf->buffer_size));
				size = recv(axel->conn[i].fd, buffer, axel->conf->buffer_size, 0);
#else
				size = read(axel->conn[i].fd, buffer, axel->conf->buffer_size);
#endif
#if WIN32
				if (SOCKET_ERROR == size)
#else
				if (-1 == size)
#endif
				{
#if !WIN32
					if (axel->conf->verbose)
					{
						axel_message( axel, _("Error on connection %i! "
							"Connection closed"), i );
					}
#endif
					axel->conn[i].enabled = 0;
					conn_disconnect(&axel->conn[i]);
					continue;
				}
				else if (0 == size)
				{
					if (axel->conf->verbose)
					{
						/* Only abnormal behaviour if: */
						if (axel->conn[i].currentbyte < axel->conn[i].lastbyte && axel->size != INT_MAX)
						{
							axel_message(axel, _("Connection %i unexpectedly closed"), i);
						}
						else
						{
							axel_message(axel, _("Connection %i finished"), i);
						}
					}
					if (!axel->conn[0].supported)
					{
						axel->ready = 1;
					}
					axel->conn[i].enabled = 0;
					conn_disconnect(&axel->conn[i]);
					continue;
				}
				/* remaining == Bytes to go */
				remaining = axel->conn[i].lastbyte - axel->conn[i].currentbyte + 1;
				if (remaining < size)
				{
					if (axel->conf->verbose)
					{
						axel_message(axel, _("Connection %i finished"), i);
					}
					axel->conn[i].enabled = 0;
					conn_disconnect(&axel->conn[i]);
					size = remaining;
					/* Don't terminate, still stuff to write!	*/
				}
				/* This should always succeed..				*/
#if WIN32
				SetFilePointer(axel->outfd, axel->conn[i].currentbyte, NULL, FILE_BEGIN);
				if (0 == WriteFile(axel->outfd, buffer, size, &byte, NULL))
#else
				lseek(axel->outfd, axel->conn[i].currentbyte, SEEK_SET);
				if (write(axel->outfd, buffer, size) != size)
#endif
				{
					axel_message(axel, _("Write error!"));
					axel->ready = -1;
					return;
				}
				axel->conn[i].currentbyte += size;
				axel->bytes_done += size;
			}
			else
			{
				if (gettime() > axel->conn[i].last_transfer + axel->conf->connection_timeout)
				{
					if (axel->conf->verbose) 
					{
						axel_message(axel, _("Connection %i timed out"), i);
					}
					conn_disconnect(&axel->conn[i]);
					axel->conn[i].enabled = 0;
				}
			}
		}
	}
	if (axel->ready) 
	{
		return;
	}
	
conn_check:
	/* Look for aborted connections and attempt to restart them. */
	for (i = 0; i < axel->conf->num_connections; i++)
	{
		if (!axel->conn[i].enabled 
            && axel->conn[i].currentbyte < axel->conn[i].lastbyte)
		{
			if (0 == axel->conn[i].state)
			{	
				// Wait for termination of this thread
#if WIN32
				WaitForSingleObject(axel->conn[i].setup_thread, INFINITE);
				CloseHandle(axel->conn[i].setup_thread);
#else
				pthread_join(*(axel->conn[i].setup_thread), NULL);
#endif	
				conn_set(&axel->conn[i], axel->url->text);
				axel->url = axel->url->next;
				if (axel->conf->verbose >= 2) 
				{
					axel_message(axel, _("Connection %i downloading from %s:%i using interface %s"), 
						i, axel->conn[i].host, axel->conn[i].port, axel->conn[i].local_if);
				}
				
				axel->conn[i].state = 1;
#if WIN32
				axel->conn[i].setup_thread = CreateThread(NULL, 0, setup_thread_cb, &axel->conn[i], 0, NULL);
				if (NULL != axel->conn[i].setup_thread) 
#else
				if (pthread_create(axel->conn[i].setup_thread, NULL, setup_thread_cb, &axel->conn[i]) == 0)
#endif
				{
					axel->conn[i].last_transfer = gettime();
				}
				else
				{
					axel_message(axel, _("thread error in axel_do!!!"));
					axel->ready = -1;
				}
			}
			else
			{
				if (gettime() > axel->conn[i].last_transfer + axel->conf->reconnect_delay)
				{
#if WIN32
					TerminateThread(axel->conn[i].setup_thread, 0);
                    CloseHandle(axel->conn[i].setup_thread);
#else
					pthread_cancel(*axel->conn[i].setup_thread);
#endif
					axel->conn[i].state = 0;
				}
			}
		}
	}

	/* Calculate current average speed and finish_time		*/
	axel->bytes_per_second = (int)((double)(axel->bytes_done - axel->start_byte) / (gettime() - axel->start_time));
	axel->finish_time = (int)(axel->start_time + (double)(axel->size - axel->start_byte) / axel->bytes_per_second);

	/* Check speed. If too high, delay for some time to slow things
	   down a bit. I think a 5% deviation should be acceptable.	*/
	if (0 < axel->conf->max_speed)
	{
		if (1.05 < (float) axel->bytes_per_second / axel->conf->max_speed) 
		{
			axel->delay_time += 10000;
		}
		else if (((float)axel->bytes_per_second / axel->conf->max_speed < 0.95) 
            && 10000 <= (axel->delay_time)) 
		{
			axel->delay_time -= 10000;
		}
		else if (((float)axel->bytes_per_second / axel->conf->max_speed < 0.95)) 
		{
			axel->delay_time = 0;
		}
		usleep(axel->delay_time);
	}
	
	/* Ready? */
	if (axel->bytes_done == axel->size) 
	{
		axel->ready = 1;
	}
}
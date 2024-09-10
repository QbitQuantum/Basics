/******************************************************************************************
 * Function to send a command to a GSM modem and to check response
 *
 * Passed Parameters:
 *  Pointer to command string
 *  Pointer to response buffer
 *  Size of response buffer
 *  Modem timeout time in seconds
 *
 * Return Value:
 *  0: OK response received from modem
 *  -1: ERROR: response received from MODEM
 *  -2: Modem timed out
 *******************************************************************************************/
int send_command(char * command_ptr, char * response_ptr, int size, int wait_time)
{
	volatile int time;
	char CR_count=0;
	int x, termination_char_received = 0, command_received=0;
	char c;
	char buff[20];
	char rx_count = 0;
	char *temp_ptr = response_ptr;
	PRINTF("HERE");

	for(x=0;x<size;x++) //clear response buffer
		*temp_ptr++ = 0;
	for(x=0;x<20;x++)
		buff[x] = 0;
	//send command to serial port
	while(*command_ptr != '\0')
	{
		PUTCHAR(*command_ptr++);
	}
	//wait for a command response or a timeout
	time = tick_count;
	x=0;
	while(!command_received &&(tick_count - time < wait_time))
	{
		c = buffer_get();
		if(c)   //buffer not empty
		{
			*response_ptr++ = c;
			rx_count++;
			if(!termination_char_received)
			{
				if(strstr(response_ptr - rx_count, "OK") || strstr(response_ptr - rx_count, "ERROR:"))
				{
					PRINTF("\nOK or ERROR received\n");
					termination_char_received = 1;
				}
			}
			else if(c == '\r')
			{
				command_received = 1;
				//printf("\nResponse Received:  \n");
			}
		}
	}
	if(command_received)
	{
		if(strstr(response_ptr - rx_count, "OK"))
			return SUCCESS;
		else if(strstr(response_ptr - rx_count, "ERROR:"))
			return ERROR;
	}
	else
	{
		PRINTF("\nTimeout on serial response\n");
		return FAIL;
	}

}
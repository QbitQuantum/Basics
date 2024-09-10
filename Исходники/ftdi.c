int32_t FTDIListener(ftdi_context ftdihandle)
{
	int32_t returnvalue,i;
	unsigned char * bufferptr;
	
	#ifdef DEBUGMODE
	printf("FTDIListener\n");
	#endif 
	do
	{	
		do
		{
			returnvalue=p_ftdi_read_data(ftdihandle, RXBUFFER, 2);
		}while(returnvalue==0);
		if(returnvalue>0)
		{
			for(i=0;i<returnvalue;i++)
			{				
				rx_fifo.BUFFER[(rx_fifo.ptr_in)&(BUFFERSIZE-1)]=RXBUFFER[i];
				rx_fifo.ptr_in=(rx_fifo.ptr_in+1)&(BUFFERSIZE-1);
			}

			#ifdef DEBUGMODE
				printf("rx : %d %d \n",rx_fifo.ptr_in,returnvalue);
			#endif
			if(READ_THREAD_EVENT)setevent(READ_THREAD_EVENT);
		}
		else
		{
			#ifdef DEBUGMODE
				printf("FTDIListener : ftdi_read_data=%d\n",returnvalue);
			#endif

			stop_thread=1;
			if(READ_THREAD_EVENT)setevent(READ_THREAD_EVENT);
		}

	}while(!stop_thread);
	setevent(STOP_THREAD_EVENT);
	return 0;
}
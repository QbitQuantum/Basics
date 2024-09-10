static int SetSSIGap(unsigned int argc, unsigned char *argv[])
{
	UINT32 gap;
	struct nim_device *nim_dev = dev_get_by_id(HLD_DEV_TYPE_NIM, nim_id);
	
	if (argc != 2)
	{
	    SH_PRINTF("Usage: SetPara <clk>\n");
	    return -1;
	}
	else if(nim_dev == NULL)
	{
	    SH_PRINTF("Nim1 status error\n");
	    return -1;
	}

	if(strcasecmp("gap",argv[1]))
	{
		gap = ATOI(&(argv[1][3]));
		nim_io_control(nim_dev, NIM_DRIVER_CHANGE_TS_GAP, gap);
	}
	else
	{
		SH_PRINTF("parameter error\n");
		return -3;
	}

#if 1//path for lock delay
	UINT8	lock;
	UINT32 pre_tick = osal_get_tick();

	while((osal_get_tick()-pre_tick)>=SSI_GAP_TIMEOUT)
	{
		nim_get_lock(nim_dev,&lock);
		if(lock)
			break;

		osal_delay(30);
	}
#endif
	
	LIB_ASH_OC('S');
	LIB_ASH_OC('e');        
	LIB_ASH_OC('t');
	LIB_ASH_OC(' ');        
	LIB_ASH_OC('S');        
	LIB_ASH_OC('S');        	
	LIB_ASH_OC('I');       
	LIB_ASH_OC(' ');           	
	LIB_ASH_OC('G');          	
	LIB_ASH_OC('a');          	
	LIB_ASH_OC('p');          	
	LIB_ASH_OC(' ');          	
	LIB_ASH_OC('t');          	
	LIB_ASH_OC('o');          	
	LIB_ASH_OC(' ');          	
	LIB_ASH_OC('g');          	
	LIB_ASH_OC('a');          	
	LIB_ASH_OC('p');
	if(gap<10)
	{
		LIB_ASH_OC((gap + '0'));	
	}
	else
	{
		LIB_ASH_OC(((UINT8)gap/10 + '0'));	
		LIB_ASH_OC(((UINT8)gap%10 + '0'));	
	}

	LIB_ASH_OC('\r'); 
	LIB_ASH_OC('\n'); 	

	reset_perflag();
	return 0;    
}
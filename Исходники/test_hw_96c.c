//---------------------------------------------------------------------------
//----------------------------------------------------------------------------
int RegRead(int argc, char* argv[])
{

	if(argc<1)
	{//dump all	
	       dprintf("\n"); 		   
		dprintf("regr addr \n");
		return;
	}

	int addr,val;
	unsigned int check=0,mask=0xffffffff,expval=0;
	
	StrUpr( argv[0] );
	
	addr= strtoul((const char*)(argv[0]), (char **)NULL, 16);		
	val=REG32(addr);

	//regr iocmd
	if(argc==1)
	{	//dprintf("%x\n", val );
	}

	//regr iocmd 0001
	else if(argc==2)
	{
		mask = strtoul((const char*)(argv[1]), (char **)NULL, 16);		
	}
	//regr iocmd : 0x0001
	else if(   argc>=3  &&  *(argv[1])==':' )
	{	check=1;
		expval = strtoul((const char*)(argv[2]), (char **)NULL, 16);	
	}
	//regr iocmd 0x0001 : 0x0001
	else if(argc>=3  && *(argv[1]) != '\0')
	{	
		mask = strtoul((const char*)(argv[1]), (char **)NULL, 16);		
		if(argc>=3 && *(argv[2]) == ':')
		{	check=1;
			expval = strtoul((const char*)(argv[3]), (char **)NULL, 16);	
		}
	}


	//verify
	if(!check)
	{
		dprintf("Addr %08x, %s=%08x \n", addr, argv[0],val&mask );			
	}
	else
	{
		if( (val&mask) !=expval)
		{	dprintf("Fail, addr=%08x val=%x, expval=%x \n", addr, val, expval);
			at2_errcnt++;
		}
		else
			dprintf("Pass \n");

	}		

}
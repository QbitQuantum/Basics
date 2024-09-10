MyHostInfo::MyHostInfo(string& hostName,hostType type)
{
	#ifdef UNIX
		searchHostDB = 0;
	#endif

	try 
	{
		if (type == NAME)
		{
			//	¡¾gethostbyname¡¿
			// Retrieve host by name
			hostPtr = gethostbyname(hostName.c_str());

			if (hostPtr == NULL)
			{
				#ifdef WINDOWS_XP
					int errorCode;
					string errorMsg = "";
					detectErrorGethostbyname(&errorCode,errorMsg);
					MyException gethostbynameException(errorCode,errorMsg);
					throw gethostbynameException;
				#endif
	
				#ifdef UNIX
					MyException gethostbynameException(0,"unix: error getting host by name");
					throw gethostbynameException;
				#endif
			}
        }
		else if (type == ADDRESS)
		{
			// Retrieve host by address
		    unsigned long netAddr = inet_addr(hostName.c_str());
			if (netAddr == -1)
			{
				MyException inet_addrException(0,"Error calling inet_addr()");
				throw inet_addrException;
			}

			//	¡¾gethostbyaddr¡¿
	        hostPtr = gethostbyaddr((char *)&netAddr, sizeof(netAddr), AF_INET);
			if (hostPtr == NULL)
			{
				#ifdef WINDOWS_XP
					int errorCode;
					string errorMsg = "";
					detectErrorGethostbyaddr(&errorCode,errorMsg);
					MyException gethostbyaddrException(errorCode,errorMsg);
					throw gethostbyaddrException;
				#endif
	
				#ifdef UNIX
					MyException gethostbynameException(0,"unix: error getting host by name");
					throw gethostbynameException;
				#endif
			}
        }
		else
		{
			MyException unknownTypeException(0,"unknown host type: host name/address has to be given ");
			throw unknownTypeException;
		}
    }
	catch(MyException& excp)
	{
		excp.response();
		exit(1);
	}
}
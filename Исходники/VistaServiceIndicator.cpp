bool VistaServiceIndicator::Ping(const string &sPeerName, int iPeerPort, bool bQuit, int iWaitTime)
{
	VistaAppMsg sMsg;
	memset(&sMsg, 0, sizeof(sMsg));

	VistaIPAddress adr = (*m_pAdr).GetIPAddress();

	string sMyHostName;
	adr.GetHostName(sMyHostName);


//        assert(sMyHostName.length() < 256);

	strncpy(&sMsg.m_acHost[0], sMyHostName.c_str(), 256);
	sprintf(&sMsg.m_acPort[0], "%d", (*m_pAdr).GetPortNumber());

	VistaSocketAddress sAdr(sPeerName, iPeerPort);
	/*	vstr::outi() << "sending Ping to " 
		 << sPeerName << ", P=[" << iPeerPort << "] from "
		 << sMsg.m_acHost << ", P=[" << (*m_pAdr).GetPortNumber()
		 << "]" << std::endl;
*/
		if(bQuit)
			sMsg.m_acCtrl = 'q';
	(*m_pServiceSocket).SendDatagramRaw(&sMsg, sizeof(sMsg), sAdr);

	int iRet =0;

#if defined(VISTA_IPC_USE_EXCEPTIONS)
	try
	{
#endif
		if((iRet=(*m_pServiceSocket).ReceiveRaw(&sMsg, sizeof(sMsg), iWaitTime))<=0)
		{
			// fail
			return false;
		}
		else
		{
			if(iRet != sizeof(sMsg))
			{
				// fail
				return false;
			}

			if(!strncmp(&sMsg.m_acAck[0], "OK", 2))
			{
				/*	vstr::outi() << "Message received:\n Host: " << &sMsg.m_acHost[0]
					<< "\n Port: " << &sMsg.m_acPort[0]
					<< "\n Ack: " << &sMsg.m_acAck[0]
					<< "\n State: " << &sMsg.m_cState
					<< "\n Ctrl: " <<	&sMsg.m_acCtrl
					<< std::endl;
*/
				
				VistaIPAddress addressee(&sMsg.m_acHost[0]), addresser(sPeerName);
				string s_addressee, s_addresser;
				addressee.GetAddressString(s_addressee);
				addresser.GetAddressString(s_addresser);

/*				vstr::outi()	<< "addressee: "
						<< s_addressee
						<< "addresser: "
						<< s_addresser
						<< std::endl;
*/
				if (s_addressee == s_addresser)
				{
					//vstr::outi() <<"got packet from right sender" << std::endl;
					return (int)sMsg.m_cState>0;
				}
				else
				{
/*					vstr::outi() <<"got packet from "
						<<&sMsg.m_acHost[0]
						<<" but it was send to "
						<< sPeerName
						<<"" << std::endl;
*/					
					//wait for next packets
					while((*m_pServiceSocket).ReceiveRaw(&sMsg, sizeof(sMsg), 1000)>0);

					return false;
				}
			}
		}
		return false;
#if defined(VISTA_IPC_USE_EXCEPTIONS)
	}
	catch(VistaExceptionBase &x)
	{
		x.PrintException();
		return false;
	}
#endif

}
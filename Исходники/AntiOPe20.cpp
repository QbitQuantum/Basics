void AntiOPe20::onCallBack(UsineMessage *Message)
{
	
	if ((Message->wParam == 1) && (Message->lParam == MSG_CHANGE) && (sdkGetEvtData(m_receivedSendOrder) == 1)) // && (Message->result == 1)) //received 1 on "enable" input
	{
			m_textNew = sdkGetEvtPChar(m_textInput); //
			std::string str(m_textNew);
			int firstChar(0);
			for (unsigned i = 0; i < str.length(); ++i)
			{
				char m_simplechar = str.at(i);
				if (m_simplechar == ',') {
					std::string strToSend = str.substr(firstChar, i - (1 + firstChar)); // a string between 2 commas
					firstChar = i+1; // the index of the string to start the next subtring
					sdkSetEvtPChar(m_textOutput, (AnsiCharPtr) (strToSend.c_str()));
					sdkSetEvtData(m_SendOrderToOSCModule, 1);
					//wait one cycle here
					sdkTraceChar("sending to MINITEL");
					_sleep(160);
					sdkSetEvtData(m_SendOrderToOSCModule, 0);
					}
				else{}
			}

	}

	else{}
	
}
/********************************************************************

  Declaration:  CommPort constructor with 2 parameters
  Call: 
  Input:
  Returns:
  	  
*********************************************************************/ 
CommPort::CommPort(const int ComPortNumber, BitRate brBitRate)
{
  SetBufferSizeVar(1200);
	m_BitRate = brBitRate;
//printf ("CommPort constructor X X start.\n");
	if (ComPortNumber <= 0)
	{
	  CommPort(); // if error - call default.
	}
	else 
	{
	 m_sComPort = new TCHAR[50];
     sprintf(m_sComPort, "COM%d:", ComPortNumber);
     OpenPort();
	}
	
}
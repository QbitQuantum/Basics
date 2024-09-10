/********************************************************************

  Declaration: 
	Call:  Send_0x20_Message (nSize, nCOM)
  Input: size of message (int) and number of com-mport
  Returns: none
  27.10.2006 Initial coding / YS  
  
	binary part:
	\0x20\0x0\0x0\0xD\0x8E\0x0\0x0\0x0\0x17\0x0\0x0\0xD\0xC1\0x0
  \0x0\0xB\0xF\0x0\0x0\0xB\0x4D\0x0\0x0\0xA\0xDD\0x35\0xAC\0x7E

*********************************************************************/
void Send_0x20_Message (int nSize, int nCOM)
{
  unsigned char  *IRISbuffer;   
  const int nMsgSize = 28;
	unsigned char tmpchr;
	unsigned short calcCRC;
  unsigned char tmpBuf[2];

	t.TRACE ("nSize: 0x%X", nSize);
  t.TRACE (", %d\n", nSize);
  IRISbuffer = new unsigned char[nMsgSize];
  // Message ID:
	IRISbuffer[0] =0x20;

	// Flow ml/min - Total:
	IRISbuffer[1] =0x0;
	IRISbuffer[2] =0x0;	
	IRISbuffer[3] =0x0;
	IRISbuffer[4] =0x8E;
	// Flow ml/min - Oxygen:
	IRISbuffer[5] =0x0;
	IRISbuffer[6] =0x0;	
	IRISbuffer[7] =0x0;
	//*(IRISbuffer+8) = 6;
	IRISbuffer[8] = nSize;// 0x05;

// Flow ml/min - Air:	
	IRISbuffer[9] = 0x0;
	IRISbuffer[10] =0x0;
	IRISbuffer[11] =0x0;
	IRISbuffer[12] =0xC1;

//Temperature - Total:	
	IRISbuffer[13] =0x0;
	IRISbuffer[14] =0x0;	
	IRISbuffer[15] =nSize;
	IRISbuffer[16] =nSize; //0x0;

//Temperature - Oxygen:	
	IRISbuffer[17] =0x0;	
	IRISbuffer[18] =0x0;
	IRISbuffer[19] =0x0; // 0xB
	IRISbuffer[20] =0x4D;

//Temperature - air:		
	IRISbuffer[21] =0x0; 
	IRISbuffer[22] =0x0;
	IRISbuffer[23] =0x0;
	IRISbuffer[24] =0x4D;
	
	calcCRC = NetworkServices::calcCRC(IRISbuffer, nMsgSize-3);	
	t.TRACE ("calculated CRC: 0x%X\n", calcCRC);
	memcpy ((void*)(tmpBuf),  (const void*)&calcCRC, sizeof(calcCRC) );

  IRISbuffer[25] =tmpBuf[1]; //0x35
	IRISbuffer[26] =tmpBuf[0]; //0xAC

	IRISbuffer[27] =0x7E;
 
 t.TRACE("Send_0x20_Message- "); 
 for (int j=0; j < nMsgSize; j++)
  {
   tmpchr=(unsigned char) IRISbuffer[j];
   t.TRACE("\\0x%X", tmpchr); 
	}
	t.TRACE("\n"); 

  TxData(nCOM, (char*)IRISbuffer, nMsgSize);

	delete [] IRISbuffer;
}
// unsigned int WINAPI DOIrisSerialPort::ReadThread( LPVOID pArg )
unsigned int DOIrisReadThread(IRIS_Node *pINode, char *cBuffer, unsigned long num)
{
    //unsigned long fdwCommMask;
     
    unsigned long CharsInBuffer = 0;
    unsigned long NonPacketCharsInBuffer;
    unsigned long packetlength;
    unsigned char tmpchr;
	  char * pEndChar;
		// unsigned long num;

    //LPSerial pCaller = reinterpret_cast<LPSerial>(pArg);
	  //DO_ASSERT( pCaller != NULL );
    //pCaller->m_bReadThreadIsRunning = TRUE;
    /*
    if ( pCaller->m_msgReceiver )
    {
        pCaller->m_msgReceiver->InitializeThread();
    }
    */
    // Enable logging from this thread via pCaller->m_pRnDLog.
    
	//HRESULT hRes = E_FAIL;
    //pCaller->m_pRnDLog->AddThread( hRes );   
    //DO_ASSERT( SUCCEEDED(hRes) );
 //printf ("DOIrisReadThread income. length=%d\n", num);
	// Setup the input and packet buffers 
    //char *cBuffer = new char[300];// [pCaller->m_iInBufferLength];
    //DO_ASSERT( cBuffer != NULL );
    char *cPacketBuffer = new char[300];//[pCaller->m_iPacketBufferLength];
    //DO_ASSERT( cPacketBuffer != NULL );
    /*
    if( !SetCommMask( pCaller->m_hPort, EV_RXCHAR | EXIT_EVENT ) )
		{
      pCaller->m_pRnDLog->LogRnDEvent( IDS_IRISCOMMON_SETCOMMMASK_FAILED );
    }    
    
		// Main loop of read thread.
    while( !pCaller->m_bStopReadThread )
    {
        if( !WaitCommEvent(pCaller->m_hPort, &fdwCommMask, 0))
        {
            //pCaller->m_pRnDLog->LogRnDEvent( IDS_IRISCOMMON_WAITCOMMEVENT_FAILED, 
            //                                 static_cast<int>(GetLastError()) );
            break;	//	Get out of read thread while loop 
        }
        
      // Reset the comm Mask.
       if( !SetCommMask(pCaller->m_hPort, EV_RXCHAR | EXIT_EVENT))
				{
            //pCaller->m_pRnDLog->LogRnDEvent( IDS_IRISCOMMON_SETCOMMMASK_FAILED,
            //                                 static_cast<int>(GetLastError()));
        }
    
        if( fdwCommMask & EV_RXCHAR )
        {
            unsigned long num;
#ifdef _WIN32_WCE
         // Read all bytes received into cBuffer.
			  ReadFile(pCaller->m_hPort, &cBuffer[CharsInBuffer], pCaller->m_iInBufferLength-CharsInBuffer, &num, 0);
#else
        ReadFile(pCaller->m_hPort, &cBuffer[CharsInBuffer], pCaller->m_iInBufferLength-CharsInBuffer, &num, &(pCaller->m_overlapped));
#endif // _WIN32_WCE
				*/
            CharsInBuffer += num;
            //printf ("CharsInBuffer = %d\n", CharsInBuffer);
            // Check for a packet in the buffer
            while( CharsInBuffer && (pEndChar = FindChr( cBuffer, IRIS_PACKET_END_FLAG, CharsInBuffer )) != NULL )
            {	
							packetlength = static_cast<unsigned long>((pEndChar - cBuffer) + 1);  // Includes IRIS_PACKET_END_FLAG char
              //printf ("packetlength=%d, pEndChar=%d\n", packetlength, pEndChar); 
                // Make sure IRIS_PACKET_END_FLAG is in new message area of buffer
                if ( packetlength <= CharsInBuffer) //&& packetlength <= pCaller->m_iPacketBufferLength )
                {
                  // Move packet to buffer and send
                  memcpy( cPacketBuffer, cBuffer, packetlength);	// PC-Lint warning 688 expected
								  t.TRACE("cPacketBuffer: "); 
									for (int j=0; j < packetlength; j++)
									{
										tmpchr=(unsigned char) cPacketBuffer[j];
										t.TRACE("\\0x%X", tmpchr);
									}
									t.TRACE("\n"); 
		    	        // pCaller->PktCallRelay( cPacketBuffer, packetlength );
									pINode->receivePacket( cPacketBuffer, packetlength ); 

                }

                // Move remaining chars in buffer to beginning of buffer and adjust char counts
                NonPacketCharsInBuffer = CharsInBuffer - packetlength;

                if( NonPacketCharsInBuffer > 0 )
								{
									// PC-Lint warning 688 expected
                  memcpy( cBuffer, &cBuffer[CharsInBuffer-NonPacketCharsInBuffer], NonPacketCharsInBuffer);
                }
                else
                {
                  NonPacketCharsInBuffer = 0;
                }
				      CharsInBuffer = NonPacketCharsInBuffer; 
            }

			// Handle the case were the buffer is full but no packet is found
            if( CharsInBuffer >=  300)//pCaller->m_iInBufferLength )
            {
              CharsInBuffer = 0;
              //pCaller->m_pRnDLog->LogRnDEvent( IDS_IRISCOMMON_BUFFER_OVERFLOW );
            }
 //       } // if(?)
        
        // Clear buffers to prevent problem when exiting thread
				/*
        if( fdwCommMask & EXIT_EVENT )
				{
            PurgeComm(pCaller->m_hPort, PURGE_RXCLEAR | PURGE_TXCLEAR | 
                                        PURGE_RXABORT | PURGE_TXABORT );
        }
				*/
 //   }    //while

	//delete [] cBuffer;
	delete [] cPacketBuffer;

    //pCaller->m_pRnDLog->RemoveThread();
    /*
    if ( pCaller->m_msgReceiver )
    {
        pCaller->m_msgReceiver->ShutdownThread();
    }

    pCaller->m_bReadThreadIsRunning = FALSE;
    */

    return 0;
}
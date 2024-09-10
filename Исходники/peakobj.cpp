void *workThreadTransmit( void *pObject )
#endif
{
#ifdef WIN32
    DWORD errorCode = 0;
#else
    int rv = 0;
#endif

    CPeakObj * pobj = ( CPeakObj *)pObject;
    if ( NULL == pobj ) {
#ifdef WIN32
        ExitThread( errorCode ); // Fail
#else
        pthread_exit( &rv );
#endif
    }

    while ( pobj->m_bRun ) {

        LOCK_MUTEX( pobj->m_peakMutex );

        // Noting to do if we should end...
        if ( !pobj->m_bRun ) continue;

        // Is there something to transmit...
        int ret;
        while ( ( NULL != pobj->m_transmitList.pHead ) &&
                ( NULL != pobj->m_transmitList.pHead->pObject ) ) {

            canalMsg msg;
            memcpy( &msg, pobj->m_transmitList.pHead->pObject, sizeof( canalMsg ) );
            LOCK_MUTEX( pobj->m_transmitMutex );
            dll_removeNode( &pobj->m_transmitList, pobj->m_transmitList.pHead );
            UNLOCK_MUTEX( pobj->m_transmitMutex );

            PeakCanMsg peakMsg;

            peakMsg.id = msg.id;
            peakMsg.msgType = 0;
            peakMsg.len = msg.sizeData;
            memcpy( peakMsg.data, msg.data, peakMsg.len );

            // Check if RTR
            if ( ( msg.flags & CANAL_IDFLAG_RTR ) ) {
                peakMsg.msgType |= PCAN_MSGTYPE_RTR;
            }

            // Check if extended
            if ( ( msg.flags & CANAL_IDFLAG_EXTENDED ) ) {
                peakMsg.msgType |= PCAN_MSGTYPE_EXTENDED;
            }

            if ( PEAK_CAN_ERR_OK == ( ret = pobj->m_procWrite( &peakMsg ) ) ) {

                // Message sent successfully
                // Update statistics
                pobj->m_stat.cntTransmitData += msg.sizeData;
                pobj->m_stat.cntTransmitFrames += 1;


            }
            else {

                // Failed - put message back in queue front
                PCANALMSG pMsg	= new canalMsg;
                if ( NULL != pMsg ) {

                    // Copy in data
                    memcpy ( pMsg, &msg, sizeof( canalMsg ) );

                    dllnode *pNode = new dllnode;
                    if ( NULL != pNode ) {

                        pNode->pObject = pMsg;
                        LOCK_MUTEX( pobj->m_transmitMutex );
                        dll_addNodeHead( &pobj->m_transmitList, pNode );
                        UNLOCK_MUTEX( pobj->m_transmitMutex );

                    }
                    else {

                        delete pMsg;
                    }

                } // unable to allocate storage

            } // faild to send message

        } // while data


        // No data to write

        UNLOCK_MUTEX( pobj->m_peakMutex );
        SLEEP( 1 );

        //}

    } // while


#ifdef WIN32
    ExitThread( errorCode );
#else
    pthread_exit( &rv );
#endif

}
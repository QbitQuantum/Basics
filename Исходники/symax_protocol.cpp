// loop function, can be factorized (for later)
uint8_t symaxProtocol::run( rx_values_t *rx_value )
{
    uint8_t returnValue = UNKNOWN;
    
    switch(mState)
    {
        case BOUND:
        {
            unsigned long newTime = millis();
            returnValue = BOUND_NO_VALUES;
            if( !mWireless->rxFlag() )
            {
                // Signal lost
                if((newTime - mLastSignalTime) > 4000)
                {
					reset();
                    mLastSignalTime = newTime; 
                }
            }
            else
            {
                bool incrementChannel = false;
                mWireless->resetRxFlag();
                while ( !mWireless->rxEmpty() )
                {
                    mWireless->readPayload(mFrame, PSIZE);
                    if( checksum(mFrame) == mFrame[PSIZE-1] )
                    {
                        // a valid frame has been received
                        incrementChannel = true;

                        // Discard bind frame
                        if( mFrame[5] != 0xAA && mFrame[6] != 0xAA )
                        {
                            // Extract values
                            returnValue = BOUND_NEW_VALUES;
                            rx_value->throttle = mFrame[0];
                            
                            rx_value->yaw = mFrame[2];
                            if (rx_value->yaw < 0)
                              rx_value->yaw = 128 - rx_value->yaw;
                              
                            rx_value->pitch = mFrame[1];
                            if (rx_value->pitch < 0)
                              rx_value->pitch = 128 - rx_value->pitch;
                              
                            rx_value->roll = mFrame[3];
                            if (rx_value->roll < 0)
                              rx_value->roll = 128 - rx_value->roll;
                              
                            rx_value->trim_yaw = mFrame[6] & 0x3F;
                            if (rx_value->trim_yaw >= 32)
                              rx_value->trim_yaw = 32 - rx_value->trim_yaw;

                            rx_value->trim_pitch = mFrame[5] & 0x3F;
                            if (rx_value->trim_pitch >= 32)
                              rx_value->trim_pitch = 32 - rx_value->trim_pitch;

                            rx_value->trim_roll = mFrame[7] & 0x3F;
                            if (rx_value->trim_roll >= 32)
                              rx_value->trim_roll = 32 - rx_value->trim_roll;

                            rx_value->video = mFrame[4] & 0x80;
                            rx_value->picture = mFrame[4] & 0x40;
                            rx_value->highspeed = mFrame[5] & 0x80;
                            rx_value->flip = mFrame[6] & 0x40;

                            mLastSignalTime = newTime;
                        }
                    }
                }
                if(incrementChannel)
                {
                    mRfChNum++;
                    if( mRfChNum >= FSIZE)
                    mRfChNum = 0;
                    mWireless->switchFreq(mRFChanBufs[mRfChNum]);
                }
            }
            
        }
        break;
        // Initial state
        case NO_BIND:
        {
            returnValue = NOT_BOUND;
            unsigned long newTime = millis();
            
            if( !mWireless->rxFlag() )
            {
				scan();
            }
            else
            {
                
                mWireless->resetRxFlag();
                bool bFrameOk = false;
                while ( !mWireless->rxEmpty() )
                {
                    mWireless->readPayload(mFrame, PSIZE);
                    if(checksum(mFrame) == mFrame[PSIZE-1] && mFrame[5] == 0xAA && mFrame[6] == 0xAA)
                    {
                        
                        // Bind frame is OK
                        
                        uint8_t txAddr[5];
                        for (int k=0; k<5; k++)
                        txAddr[k] = mFrame[4-k];
                        
                        // Create TX frequency array
                        
                        mWireless->setAddress(txAddr, 5);
                        
                        setRFChannel(txAddr[0]);
                        mRfChNum = 0;
                        mWireless->switchFreq(mRFChanBufs[mRfChNum]);
                        
                        mLastSignalTime = newTime;
                        mState = WAIT_FIRST_SYNCHRO;
                        mWireless->flushRx();
                        returnValue = BIND_IN_PROGRESS;
                        
                        break;
                    }
                }
            }
        }
        break;
        
        // Wait on the first frequency of TX
        case WAIT_FIRST_SYNCHRO:
        {
            
            unsigned long newTime = millis();
            returnValue = BIND_IN_PROGRESS;
            if( mWireless->rxFlag() )
            {
                mWireless->resetRxFlag();
                bool incrementChannel = false;
                while ( !mWireless->rxEmpty() )
                {
                    mWireless->readPayload(mFrame, PSIZE);
                    
                    if( checksum(mFrame) == mFrame[PSIZE-1] )
                    {
                        incrementChannel = true;
                        mState = BOUND;
                        mLastSignalTime = newTime;
                    }
                }
                
                if(incrementChannel)
                {
                    // switch channel
                    mRfChNum++;
                    if( mRfChNum >= FSIZE)
                    mRfChNum = 0;
                    mWireless->switchFreq(mRFChanBufs[mRfChNum]);
                }
            }
            
            break;
        }
        
        default:
        break;
    }
    
    return returnValue;
}
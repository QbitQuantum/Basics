// ---------------------------------------------------------------------------
// CDTMFPayloadFormatWrite::EncodeNextDigitL
// Encodes next digit in sequence.
// ---------------------------------------------------------------------------
//
void CDTMFPayloadFormatWrite::EncodeNextDigitL()
    {
    DP_DTMF_WRITE2( _L("CDTMFPayloadFormatWrite::EncodeNextDigitL, tick = %u"),
        User::NTickCount() );

    iToneDuration = 0;
    iToneDuration += static_cast<TUint16>
        ( iCInfo.iPtime * iSampleRate * KMsToSecFactor );
    
    if ( iSendBuffer.Count() && ('p' == iSendBuffer[0].Tone() || 'w' == 
        iSendBuffer[0].Tone() ) )
        {
        HandleControlChar( iSendBuffer[0].Tone() );
        iSendBuffer.Remove( 0 );
        }
    else if ( iSendBuffer.Count() )
        {
        if ( EDTMFPayloadFormatEvent == iPayloadFormat ||
             EDTMFPayloadFormatRedEvents == iPayloadFormat )
            {
            // Encode digit to RTP packet using Payload Format
            // for Named Events
            TDTMFEventPayloadInfo eventInfo;
            eventInfo.SetEvent( iSendBuffer[0].Tone() );
            eventInfo.SetVolume( KDTMFDefaultToneVolume );
            eventInfo.SetDuration( iToneDuration );
            
            if ( KSignalOutbandDtmf == iGenerationMode )
                {
                TUint32 timeStamp( 0 );
                User::LeaveIfError( 
                    iRtpMediaClock->GetTimeStamp( iKey, timeStamp ) );
                iSinkBuffer->SetTimeToPlay( 
                    TTimeIntervalMicroSeconds( TInt64( timeStamp ) ) );
                }
            
            iPayloadEncoder->EncodeEvent( eventInfo, iSinkBuffer );
            }
        else if ( EDTMFPayloadFormatTone == iPayloadFormat )
            {
            TDTMFTonePayloadInfo toneInfo;
            toneInfo.SetModulation( KDTMFDefaultModulation );
            toneInfo.SetVolume( KDTMFDefaultToneVolume );
            toneInfo.SetDuration( iToneDuration );
            iPayloadEncoder->EncodeTone( toneInfo, iSinkBuffer );
            }
        else
            {
            // Not acceptable payload format
            DP_DTMF_WRITE2( _L("PayloadFormat not Acceptable!: %d"), 
                iPayloadFormat );
            }
        
        iStateMachine->ChangeStateTo( EStateToneOn );
        }
    else
        {
        if ( EModeAutomatic == iSendingMode )
            {
            SendEventSignalToClient( KMccDtmfSendingComplete );
            }

        iStateMachine->ChangeStateTo( EStateSendingIdle );
        }
    }
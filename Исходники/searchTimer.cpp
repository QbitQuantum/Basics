//
// searchTimer::expire ()
//
epicsTimerNotify::expireStatus searchTimer::expire ( 
    const epicsTime & currentTime ) // X aCC 361
{
    epicsGuard < epicsMutex > guard ( this->mutex );

    while ( nciu * pChan = this->chanListRespPending.get () ) {
        pChan->channelNode::listMember = 
            channelNode::cs_none;
        this->iiu.noSearchRespNotify ( 
            guard, *pChan, this->index );
    }
    
    this->timeAtLastSend = currentTime;

    // boost search period for channels not recently
    // searched for if there was some success
    if ( this->searchResponses && this->boostPossible ) {
        while ( nciu * pChan = this->chanListReqPending.get () ) {
            pChan->channelNode::listMember = 
                channelNode::cs_none;
            this->iiu.boostChannel ( guard, *pChan );
        }
    }

    if ( this->searchAttempts ) {
#if 0
        //
        // dynamically adjust the number of UDP frames per 
        // try depending how many search requests are not 
        // replied to
        //
        // The variable this->framesPerTry
        // determines the number of UDP frames to be sent
        // each time that expire() is called.
        // If this value is too high we will waste some
        // network bandwidth. If it is too low we will
        // use very little of the incoming UDP message
        // buffer associated with the server's port and
        // will therefore take longer to connect. We 
        // initialize this->framesPerTry to a prime number 
        // so that it is less likely that the
        // same channel is in the last UDP frame
        // sent every time that this is called (and
        // potentially discarded by a CA server with
        // a small UDP input queue). 
        //
        // increase frames per try only if we see better than
        // a 93.75% success rate for one pass through the list
        //
        if ( this->searchResponses >
            ( this->searchAttempts - (this->searchAttempts/16u) ) ) {
            // increase UDP frames per try if we have a good score
            if ( this->framesPerTry < maxTriesPerFrame ) {
                // a congestion avoidance threshold similar to TCP is now used
                if ( this->framesPerTry < this->framesPerTryCongestThresh ) {
                    this->framesPerTry += this->framesPerTry;
                }
                else {
                    this->framesPerTry += (this->framesPerTry/8) + 1;
                }
                debugPrintf ( ("Increasing frame count to %u t=%u r=%u\n", 
                    this->framesPerTry, this->searchAttempts, this->searchResponses) );
            }
        }
        // if we detect congestion because we have less than a 87.5% success 
        // rate then gradually reduce the frames per try
        else if ( this->searchResponses < 
            ( this->searchAttempts - (this->searchAttempts/8u) ) ) {
            if ( this->framesPerTry > 1 ) {
                this->framesPerTry--;
            }
            this->framesPerTryCongestThresh = this->framesPerTry/2 + 1;
            debugPrintf ( ("Congestion detected - set frames per try to %f t=%u r=%u\n", 
                this->framesPerTry, this->searchAttempts, this->searchResponses) );
        }
#else
        if ( this->searchResponses == this->searchAttempts ) {
            // increase UDP frames per try if we have a good score
            if ( this->framesPerTry < maxTriesPerFrame ) {
                // a congestion avoidance threshold similar to TCP is now used
                if ( this->framesPerTry < this->framesPerTryCongestThresh ) {
                    double doubled = 2 * this->framesPerTry;
                    if ( doubled > this->framesPerTryCongestThresh ) {
                        this->framesPerTry = this->framesPerTryCongestThresh;
                    }
                    else {
                        this->framesPerTry = doubled;
                    }
                }
                else {
                    this->framesPerTry += 1.0 / this->framesPerTry;
                }
                debugPrintf ( ("Increasing frame count to %g t=%u r=%u\n", 
                    this->framesPerTry, this->searchAttempts, this->searchResponses) );
            }
        }
        else  {
            this->framesPerTryCongestThresh = this->framesPerTry / 2.0;
            this->framesPerTry = 1u;
            debugPrintf ( ("Congestion detected - set frames per try to %g t=%u r=%u\n", 
                this->framesPerTry, this->searchAttempts, this->searchResponses) );
        }
#endif
    }

    this->dgSeqNoAtTimerExpireBegin = 
        this->iiu.datagramSeqNumber ( guard );

    this->searchAttempts = 0;
    this->searchResponses = 0;

    unsigned nFrameSent = 0u;
    while ( true ) {
        nciu * pChan = this->chanListReqPending.get ();
        if ( ! pChan ) {
            break;
        }

        pChan->channelNode::listMember = 
            channelNode::cs_none;
    
        bool success = pChan->searchMsg ( guard );
        if ( ! success ) {
            if ( this->iiu.datagramFlush ( guard, currentTime ) ) {
                nFrameSent++;
                if ( nFrameSent < this->framesPerTry ) {
                    success = pChan->searchMsg ( guard );
                }
            }
            if ( ! success ) {
                this->chanListReqPending.push ( *pChan );
                pChan->channelNode::setReqPendingState ( 
                    guard, this->index );
                break;
            }
        }

        this->chanListRespPending.add ( *pChan );
        pChan->channelNode::setRespPendingState ( 
            guard, this->index );

        if ( this->searchAttempts < UINT_MAX ) {
            this->searchAttempts++;
        }
    }

    // flush out the search request buffer
    if ( this->iiu.datagramFlush ( guard, currentTime ) ) {
        nFrameSent++;
    }

    this->dgSeqNoAtTimerExpireEnd = 
        this->iiu.datagramSeqNumber ( guard ) - 1u;

#   ifdef DEBUG
        if ( this->searchAttempts ) {
            char buf[64];
            currentTime.strftime ( buf, sizeof(buf), "%M:%S.%09f");
            debugPrintf ( ("sent %u delay sec=%f Rts=%s\n", 
                nFrameSent, this->period(), buf ) );
        }
#   endif

    return expireStatus ( restart, this->period ( guard ) );
}
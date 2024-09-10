void cac::destroyIIU ( tcpiiu & iiu )
{
    {
        callbackManager mgr ( this->notify, this->cbMutex );
        epicsGuard < epicsMutex > guard ( this->mutex );

        if ( iiu.channelCount ( guard ) ) {
            char hostNameTmp[64];
            iiu.getHostName ( guard, hostNameTmp, sizeof ( hostNameTmp ) );
            genLocalExcep ( mgr.cbGuard, guard, *this, ECA_DISCONN, hostNameTmp );
        }
        osiSockAddr addr = iiu.getNetworkAddress ( guard );
        if ( addr.sa.sa_family == AF_INET ) {
            inetAddrID tmp ( addr.ia );
            bhe * pBHE = this->beaconTable.lookup ( tmp );
            if ( pBHE ) {
                pBHE->unregisterIIU ( guard, iiu );
            }
        }
       
        assert ( this->pudpiiu );
        iiu.disconnectAllChannels ( mgr.cbGuard, guard, *this->pudpiiu );

        this->serverTable.remove ( iiu );
        this->circuitList.remove ( iiu );
    }

    // this destroys a timer that takes the primary mutex
    // so we must not hold the primary mutex here
    //
    // this waits for send/recv threads to exit
    // this also uses the cac free lists so cac must wait 
    // for this to finish before it shuts down

    iiu.~tcpiiu ();

    {
        epicsGuard < epicsMutex > guard ( this->mutex );
        this->freeListVirtualCircuit.release ( & iiu );
        this->iiuExistenceCount--;
        // signal iiu uninstall event so that cac can properly shut down
        this->iiuUninstall.signal();
    }
    // do not touch "this" after lock is released above
}
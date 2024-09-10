void DialupImpl::phoneCallStateChanged( const QPhoneCall& call)
{
    if ( (int)call.state()  >= (int) QPhoneCall::HangupLocal  && !pppdProcessBlocked ) {
        //if the call hangs up/aborts w/o being stopped manually by the user we need to cleanup 
        //in order to prevent that pppdProcessBlocked blocks the interface forever
        if ( tidStateUpdate ) {
            killTimer( tidStateUpdate );
            tidStateUpdate = 0;
            state = Initialize;
            logIndex = 0;
        }
        pppIface = QString();
        netSpace->setAttribute( "NetDevice", QString() );
        ifaceStatus = QtopiaNetworkInterface::Down;
        status();
    }
    qLog(Network) << "Call state: " << call.state();
}
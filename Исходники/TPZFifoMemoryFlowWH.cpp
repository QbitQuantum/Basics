Boolean TPZFifoMemoryFlowWH::inputReading() {
    TPZMessage* msg;
    inputInterfaz()->getData(&msg);

    if (!inputInterfaz()->isReadyActive() && m_tail==false) {
        uTIME delayTime = getOwnerRouter().getCurrentTime() ;
        TPZString err= "A tail flit was expected but transmission has been interrupted";
        err=err+msg->asString()+ "Time crash=" + TPZString(delayTime);
        EXIT_PROGRAM(err);
    }

    if (inputInterfaz()->isReadyActive() ) {
        msg->incDistance();
	((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::BufferWrite);
        
	if (msg->isTail() || msg->isHeadTail()) {
            m_tail=true;
            setControlTail(true);
        }

        if (msg->isHeader() || msg->isHeadTail()) {
            getOwnerRouter().incrContadorTotal();
        }
        
        if (msg->isHeader() && m_tail==false) {
            uTIME delayTime = getOwnerRouter().getCurrentTime() ;
            TPZString err= "A head flit arrives before previous tail flit";
            err=err+msg->asString()+ "Time crash=" + TPZString(delayTime);
            EXIT_PROGRAM(err);
        }

        if ( !bufferHoles()) {
            uTIME delayTime = getOwnerRouter().getCurrentTime() ;
            TPZString err;
            err.sprintf(ERR_TPZFFLOW_001, (char*)getComponent().asString());
            err=err+msg->asString()+ "Time crash=" + TPZString(delayTime);
            EXIT_PROGRAM(err);
        }

        uTIME delay = getOwnerRouter().getCurrentTime() + getDataDelay();
        TPZEvent event(_BufferData_, msg);
        getEventQueue().enqueue(event, delay);

#ifndef NO_TRAZA
        uTIME delayTime = getOwnerRouter().getCurrentTime() ;
        TPZString texto = getComponent().asString() + " Flit Rx on Time" + TPZString(delayTime) + " # "
                + msg->asString() + ") holes= " + TPZString(bufferHoles());
        TPZWRITE2LOG(texto);
#endif

        stateChange();
        if (m_SendStop) {
            inputInterfaz()->sendStopRightNow();
#ifndef NO_TRAZA
            uTIME time = getOwnerRouter().getCurrentTime();
            TPZString texto = getComponent().asString() + ": Full Buffer->Stop ";
            texto += TPZString(time);
            TPZWRITE2LOG(texto);
#endif
        } else {
            inputInterfaz()->clearStopRightNow();
        }
        return true;
    }
    return false;
}
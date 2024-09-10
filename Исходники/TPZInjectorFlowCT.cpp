Boolean TPZInjectorFlowCT :: outputWriting()
{
   outputInterfaz() -> clearData();

   if( isAnyMessageToSend())
   {
      if( (!outputInterfaz()->isStopActive())  || isHeaderSent() )
      {
         TPZMessage* msg = getNextFlitToSend();
         m_flitsSent++;
         if(!msg) return true;
  #ifdef PTOPAZ      
         TPZNetwork* net = ((TPZSimulation*)(getComponent().getSimulation()))->getNetwork();
         unsigned n = net->getThreadID(pthread_self());
         msg -> setPoolIndex(n);
#endif  
    
         if( msg->isHeader() || msg->isHeadTail() )
     {
        setHeaderSent(true);
        TPZNetwork* net = ((TPZSimulation*)(getComponent().getSimulation()))->getNetwork();
        TPZPosition source = msg->source();
        net->incrInjectedFlitsAt(source.valueForCoordinate(TPZPosition::X),source.valueForCoordinate(TPZPosition::Y),source.valueForCoordinate(TPZPosition::Z),msg->packetSize());
        if (msg->isHeadTail()) setHeaderSent(false);
     }
         if(msg->isTail() ) setHeaderSent(false);
         
	 outputInterfaz()->sendData(msg);
	 #ifndef NO_TRAZA
            uTIME delayTime = getOwnerRouter().getCurrentTime() ;
            TPZString texto = getComponent().asString() + " Flit Tx. TIME = ";
            texto += TPZString(delayTime) + " # " + msg->asString();
            if( msg->isHeader() || msg->isHeadTail() )
            {
               texto += TPZString("  HEADER: ") + 
                        msg->source().asString() + " => " + 
                        msg->destiny().asString();
            }
            TPZWRITE2LOG( texto );
         #endif
     }
   }
   return true;   
}
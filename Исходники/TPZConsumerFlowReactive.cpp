Boolean TPZConsumerFlowReactive :: stateChange()
{
   if( (!inputInterfaz()->isStopActive()) && m_DataReceived )
   {
#ifndef NO_TRAZA
         TPZString time = getOwnerRouter().getCurrentTime();
         TPZString texto= getComponent().asString() +
                          " Flit Rx. TIME = " +
                          time + ".  " +
                          m_InputData->asString();
#endif
      if(m_State  == Information && m_InputData->isHeader())
      {
         TPZString err;
         err.sprintf( "%s : I detect a Header flit before previous message Tail flit: %s",
                      (char*)getComponent().asString(),
                      (char*)m_InputData->asString() );
         EXIT_PROGRAM(err);
      } 
   

      if( m_State == Header )
      {
         if (m_InputData->isHeadTail()) m_State = Header;
          else m_State = Information;

         if( m_InputData->destiny() != getOwnerRouter().getPosition() && !m_InputData->isMulticast() )
         {
            TPZString err;
            err.sprintf( ERR_TPZCOFLO_001,(char*)getComponent().asString(),(char*)m_InputData->asString() );
            EXIT_PROGRAM(err);
         }
         if(m_InputData->isHeadTail())
         {
#ifndef NO_TRAZA
            texto += "  PACKET RX";
#endif
            m_InputData->setDestiny(getOwnerRouter().getPosition());
            getOwnerRouter().onPacketReceived(m_InputData);
            uTIME lastTime = getOwnerRouter().getCurrentTime();
            ((TPZSimulation*)(getComponent().getSimulation()))->setLastMessage ( lastTime );
         }
      }
          
      if( m_InputData->isTail() )
      {
#ifndef NO_TRAZA
         texto += "  PACKET RX";
#endif
        
         getOwnerRouter().onPacketReceived(m_InputData);
         m_State = Header;
         uTIME lastTime = getOwnerRouter().getCurrentTime();
         ((TPZSimulation*)(getComponent().getSimulation()))->setLastMessage ( lastTime );
        //reinjection of the packet, in order to emulate reactive nature
        //injectProtocolMessage emulates traffic where messages travel back to their source node
        //injectProtocolRandomMessage function can also be employed. In this case, destination of
        //re-injected packet is chosen randomly.
     
        int order = m_InputData-> getVnet ();
        unsigned mess_types= ((TPZSimulation*)(getComponent().getSimulation()))->getProtocolMessTypes();
        if (order < mess_types)
        ((TPZSimulation *)(getComponent().getSimulation()))->injectProtocolMessage(m_InputData->destiny(), m_InputData->source(), order+1);
      
     }
       
#ifndef NO_TRAZA
   TPZWRITE2LOG(texto);
#endif
   }

   return true;
}
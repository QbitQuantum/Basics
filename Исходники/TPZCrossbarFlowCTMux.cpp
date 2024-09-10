Boolean TPZCrossbarFlowCTMux :: dispatchEvent(const TPZEvent& event)
{        
   if( ( event.type() == _CrossbarRequest_ ) ||
       ( event.type() == _CrossbarPass_ ) )
   {
      TPZCrossbar& crossbar = (TPZCrossbar&)(getComponent());
      unsigned iPort =   event.source();
      unsigned oPort =   getOutputForInput(iPort).left();
      unsigned channel = getOutputForInput(iPort).right();
      
      if(event.type() == _CrossbarRequest_)
      {
        oPort=event.destiny();
        channel=event.channel();  
      } 
      TPZMessage *msg;
      m_MessageReceivedTable->valueAt(iPort,&msg);
      
      if(!msg) return true;
      
      if(!channel)
      {
         if(_CrossbarRequest_)
         {
           EXIT_PROGRAM("Channel set to 0 in request Not allowed");
         }
         else
         {
           EXIT_PROGRAM("Channel set to 0 in data Not allowed");
         }
      }  
      else if( ! iPort )
      {
         TPZString err;
         err.sprintf( ERR_TPZCFLOC_001, 
                      (char*)getComponent().asString(),
                      (char*)msg->asString() );
         EXIT_PROGRAM(err);
      }
      else if(!oPort)
      {
         TPZString err;
         err.sprintf( ERR_TPZCFLOC_002, 
                      (char*)getComponent().asString(),
                      (char*)msg->asString() );
         EXIT_PROGRAM(err);
      }
      
      //Here's the difference with the normal version
      if( event.type() == _CrossbarRequest_)
      {
         for(int i=1; i<=crossbar.numberOfInputs(); i++)
         {
            uPAIR temp;
            m_PortAsignamentTable->valueAt(i,temp);
            if(i!=iPort && (temp.left()==oPort) )
            {
                inputInterfaz(iPort)->sendStop();
                uTIME delayTime = getOwnerRouter().getCurrentTime() + 1;
                getEventQueue().enqueue(event,delayTime); 

   #ifndef NO_TRAZA 
                TPZString time = getOwnerRouter().getCurrentTime();       
                TPZString texto = getComponent().asString() + " CONTENTION  STOP TIME = ";
                texto += time + msg->asString() + " i=" + TPZString(iPort) +
                    ", o=" + TPZString(oPort) + ", OPORT used by i=" + TPZString(i);
                TPZWRITE2LOG( texto );
   #endif
                return true;
            }
         }
      
         if( (outputInterfaz(oPort)->isStopActive(channel)))
         {
            inputInterfaz(iPort)->sendStop();
            uTIME delayTime = getOwnerRouter().getCurrentTime() + 1;
            getEventQueue().enqueue(event,delayTime);

   #ifndef NO_TRAZA 
      TPZString time = getOwnerRouter().getCurrentTime();       
      TPZString texto = getComponent().asString() + " QUEUES  STOP TIME = ";
      texto += time + msg->asString() + " i=" + TPZString(iPort) +
               ", o=" + TPZString(oPort);
             
      TPZWRITE2LOG( texto );
   #endif
               return true;
         }
               establishConnection(iPort,oPort,channel);

      setStateForInput(iPort,Connect);   
      }

   
    
      inputInterfaz(iPort)->clearStopRightNow();
     
      outputInterfaz(oPort)->sendData(msg,channel);
      ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::SWTraversal);
      if (msg->getRoutingPort()!=_LocalNode_) 
      ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::LinkTraversal);
           
   #ifndef NO_TRAZA 
      TPZString time = getOwnerRouter().getCurrentTime();       
      TPZString texto = getComponent().asString() + " Flit Tx. TIME = ";
      texto += time + msg->asString() + " i=" + TPZString(iPort) +
               ", o=" + TPZString(oPort);
            
      TPZWRITE2LOG( texto );
   #endif
   
      if( msg->isTail() )
      {
         clearConnection(iPort);
         uPAIR temp;
         temp = getConnectionRequestForWith(oPort);
         iPort=temp.left();
         channel=temp.right();
         if( iPort != 0 )
         {
            establishConnection(iPort,oPort,channel);
            TPZEvent requestEvent(_CrossbarRequest_,iPort,oPort,channel);
            uTIME delayTime = getOwnerRouter().getCurrentTime() +
                              MAXIMO(1,getHeaderDelay());
            
            if( ((TPZCrossbar&)getComponent()).isLocalNodeOutput(oPort) )
            {
               if( getHeaderDelay() > 1 )
                  delayTime -= 1;
            }
            
            getEventQueue().enqueue(requestEvent,delayTime);
         }
      }
   }  
   return true;
}
//*************************************************************************
//:
//  f: virtual Boolean inputReading ();
//
//  d:
//:
//*************************************************************************
Boolean TPZSimpleRouterFlowWH :: inputReading()
{  
   unsigned outPort;
   unsigned inPort;
   unsigned virtualChannel;
   cleanOutputInterfaces();
   TPZNetwork* net = ((TPZSimulation*)(getComponent().getSimulation()))->getNetwork();
   
   //**********************************************************************************************************
   // PART 4: Loop through all output ports.
   // We move the data flits for already established connections
   //**********************************************************************************************************
   for( outPort = 1; outPort <= m_ports; outPort++)
   {   
      // Find the input port assigned to outport.
      // If not assigned, go to the next.
      if( ! (inPort = m_connections[outPort] ) ) 
      {
                 continue;
      }
      
      // If no message at routing, go to the next
      if( ! m_routing[inPort] )
      {
          TPZString err = getComponent().asString() +  " TIME: " + TPZString(getOwnerRouter().getCurrentTime());
          err+=" connection indicates that input: ";
          err+= TPZString(inPort)+"is connected to output: ";
          err+= TPZString(outPort);
          err+=" but the routing unit is empty (Packet fragmented at the link?)"; 
          //EXIT_PROGRAM (err);
          continue;
      }
      

      virtualChannel=(inPort-1)/m_ports+1;
      if( inPort % m_ports == 0  ) 
      {
         virtualChannel=m_routing[inPort]->getVnet(); 
	 if(inPort>m_ports)continue;
      }
      if(outPort == m_ports) virtualChannel=1;
      
      if( outputInterfaz(outPort)->isStopActive(virtualChannel) ) 
      {
         continue;
      }
      // If there is a message at routing and delay is over
      if( ! ( m_routingtime[inPort]-- ) )
      {
         TPZMessage* mess=m_routing[inPort];
	 
	 if (mess->isMulticast())
	 {
	    unsigned long long messageMask=mess->getMsgmask();
	    unsigned long long portMask=getOwnerRouter().getMask(mess->getRoutingPort());
	    //The last message, no replication is needed
	    if ( (messageMask & (~portMask))== 0)
	    {
	       mess->setMsgmask(messageMask & portMask);
	       m_routing[inPort] = 0;
#ifndef NO_TRAZA
               TPZString texto = getComponent().asString() + " NO-REPLICATION ";
	       texto += TPZString( " Leaving MSG= ") + mess->asString();
               texto += TPZString( " Leaving Mask= ") + TPZString(mess->getMsgmask());
	       texto += TPZString( " OPORT= ") + TPZString(outPort);
               TPZWRITE2LOG(texto);
#endif		       
	    }
	    //need to replicate, destinations remaining
	    else
	    {
	       if((mess = getMessagePool().allocate())==0) 
	       {
	          TPZString err;
                  err.sprintf(ERR_TPZPOOL_001);
                  EXIT_PROGRAM(err);
               }
               *mess=*m_routing[inPort];
	       //New message mask
	       mess->setMulticast();
	       mess->setMsgmask(messageMask & portMask);
#ifdef PTOPAZ	
               unsigned pool_index=net->getThreadID(pthread_self());
               mess->setPoolIndex(pool_index);
#endif 	        
               // Statistics functions 
               net->incrementTx(TPZNetwork::Message);
               net->incrementTx(TPZNetwork::Packet,mess->messageSize());
               net->incrementTx(TPZNetwork::Flit,mess->messageSize()*mess->packetSize());
	       m_routing[inPort]->setMsgmask(messageMask & (~portMask));
	       updateMessageInfo(m_routing[inPort]);
               m_routingtime[inPort] = getHeaderDelay();
#ifndef NO_TRAZA
               TPZString texto = getComponent().asString() + " REPLICATION ";
	       texto += TPZString( " Leaving Mask= ") + TPZString(mess->getMsgmask());
               texto += TPZString(" Remaining Mask= ") + TPZString(m_routing[inPort]->getMsgmask());
               TPZWRITE2LOG(texto);
#endif	       
	    }
	 }
	 else
	 {
	    m_routing[inPort] = 0;
	 }
	    
	 outputInterfaz(outPort)->sendData(mess,virtualChannel);
         ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::SWTraversal);
         ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::BufferRead);
         if ( ((TPZSimpleRouter&)getComponent()).getTypeForOutput(outPort) != _LocalNode_ )
         {
            getOwnerRouter().incrLinkUtilization();
            ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::LinkTraversal);
         }
#ifndef NO_TRAZA
         TPZString texto = getComponent().asString() + " SW TRAVERSAL ";
         texto +=  " From  ";
         texto += mess->asString() + " TIME: " + TPZString(getOwnerRouter().getCurrentTime());
         texto += TPZString(" inPort: ") + TPZString(inPort) + TPZString(" outPort: ") + TPZString(outPort);
         texto += TPZString(" VChannel: ") + TPZString(virtualChannel);
         TPZWRITE2LOG(texto);
#endif
         // If end of message
         if( mess->isTail() || mess->isHeadTail() )
         {
            m_connections[outPort] = 0;
#ifndef NO_TRAZA
            TPZString texto = getComponent().asString() + " CLEARING ";
            texto +=  " From  ";
            texto += mess->asString() + " TIME: " + TPZString(getOwnerRouter().getCurrentTime());
            texto += TPZString(" inPort: ") + TPZString(inPort) + TPZString(" outPort: ") + TPZString(outPort);
            texto += TPZString(" VChannel: ") + TPZString(virtualChannel);
            TPZWRITE2LOG(texto);
#endif
         }
      }
   }
   
   //******************************************************************************************************************
   // PART 3: Process the connection of the crossbar
   // the token is to be round robin arbitration
   //******************************************************************************************************************
   inPort = m_ports*m_vnets;
   m_token = 0;
   int i;
   for(i = 0; i < m_ports*m_vnets ; i++, inPort = inPort - 1)
   {
      virtualChannel=(inPort-1)/m_ports+1;
     
      // If the routing is empty, go to the next
      if( ! m_routing[inPort] ) 
      {
           continue;
      }
      // If it is not a header, go to the next
      if( (! m_routing[inPort]->isHeader()) && (! m_routing[inPort]->isHeadTail()) )
      {
           continue;
      }  
      // Extract the output port
      outPort = extractOutputPortNumber(m_routing[inPort]); 
      
      if(inPort == m_ports) 
      {
         virtualChannel=m_routing[inPort]->getVnet(); 
	 if(inPort>m_ports)continue;
      }
      if(outPort == m_ports) virtualChannel=1;
      
      if( outputInterfaz(outPort)->isStopActive(virtualChannel) ) 
      {
         if( ! m_token ) m_token = inPort;
     continue;
      }
      
      if( ! m_connections[outPort] )
      {
         // Reserve the port
         m_connections[outPort] = inPort;
#ifndef NO_TRAZA
        TPZString texto = getComponent().asString() + " SW ARB [GRANT] ";
        texto +=  " From  ";
        texto += m_routing[inPort]->asString() + " TIME: " + TPZString(getOwnerRouter().getCurrentTime());
        texto += TPZString(" inPort: ") + TPZString(inPort) + TPZString(" outPort: ") + TPZString(outPort);
        texto += TPZString(" VChannel: ") + TPZString(virtualChannel);
        TPZWRITE2LOG(texto);
#endif
      }
      else
      {
#ifndef NO_TRAZA
           TPZString texto = getComponent().asString() + " SW ARB {REJECT] ";
           texto +=  " From  ";
           texto += m_routing[inPort]->asString() + " TIME: " + TPZString(getOwnerRouter().getCurrentTime());
           texto += TPZString(" inPort: ") + TPZString(inPort) + TPZString(" outPort: ") + TPZString(outPort);
           texto += TPZString(" VChannel: ") + TPZString(virtualChannel);
           TPZWRITE2LOG(texto);
#endif
         // If this is the first port rejected in this round
         // keep it to serve first in the following
         if( ! m_token )
         {
            m_token = inPort;
         }
      }
      
   }
   // No ports were rejected.
   if( ! m_token ) m_token = inPort;
       
   //****************************************************************************************************************
   // PART 2: Loop through all the routing
   // Filling those that are empty with data from the fifo
   //****************************************************************************************************************
   for(inPort = 1; inPort <= m_ports*m_vnets; inPort++) 
   {
      // If the routing is not empty
      if( ! m_routing[inPort] )
      {
        // Take the next message from the corresponding fifo
         if(m_fifos[inPort].numberOfElements()!=0)
         {
                m_fifos[inPort].dequeue(m_routing[inPort]);
#ifndef NO_TRAZA
                  TPZString texto = getComponent().asString() + " BUFFER-READ ";
                  texto +=  m_routing[inPort]->asString()+ " TIME: " + TPZString(getOwnerRouter().getCurrentTime());
                  TPZWRITE2LOG(texto);
#endif
               // If the message is header
               if( m_routing[inPort]->isHeader() || m_routing[inPort]->isHeadTail() )
               {
                  // Calculate the output port
                  updateMessageInfo(m_routing[inPort]);
                  m_routingtime[inPort] = getHeaderDelay();
               }
           else
           {
              m_routingtime[inPort] = 0;
           }

          }          
      }
   }
   
   //**********************************************************************************************************
   // PART 1: Loop through all sync.
   //**********************************************************************************************************
   for( inPort = 1; inPort <= m_ports*m_vnets; inPort++)
   {
      // If there is a message at syncronizer,
      
      if( m_sync[inPort] )
      {
#ifndef NO_TRAZA
                  TPZString texto = getComponent().asString() + " BUFFER-WRITE ";
                  texto +=  m_sync[inPort]->asString()+ " TIME: " + TPZString(getOwnerRouter().getCurrentTime());
                  TPZWRITE2LOG(texto);
#endif
            // Put it in the corresponding buffer
            m_fifos[inPort].enqueue(m_sync[inPort]);
            // and remove it from syncs
            m_sync[inPort]=0;
      }
   }  
   return true;   
}
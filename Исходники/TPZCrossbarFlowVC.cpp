//*************************************************************************
//:
//  f: virtual Boolean dispatchEvent (const TPZEvent & event);
//
//  d:
//:
//*************************************************************************
Boolean TPZCrossbarFlowVC::dispatchEvent(const TPZEvent& event) 
{
   uTIME delayTime = getOwnerRouter().getCurrentTime();
   //**********************************************************************
   // EVENT= ROUTING
   //**********************************************************************
   if (event.type() == _RoutingVC_) 
   {
      //update the header and select output port
      TPZMessage *msg;
      unsigned iPort = event.source();
      m_MessageReceivedTable->valueAt(iPort, &msg);
      if ( (!(msg->isHeader())) && (!(msg->isHeadTail())) ) 
      {
         TPZString err;
         err.sprintf("%s :Body flits should not pass through this state", (char*)getComponent().asString() );
         EXIT_PROGRAM(err);
      }
#ifndef NO_TRAZA
      TPZString texto = getComponent().asString() + " Event ROUTING. TIME = ";
      texto += TPZString(getOwnerRouter().getCurrentTime()) + " # " + "iPort=" + TPZString(iPort) + " # " + msg->asString() ;
      TPZWRITE2LOG(texto);
#endif

      if (!msg->isMulticast()) //MC messages have been already processed
      {
         int deltaX = msg->delta(0);
         int deltaY = msg->delta(1);
         int deltaZ = msg->delta(2);
      
         if (deltaX > 1) msg->setRoutingPort(_Xplus_);
         else if (deltaX < -1) msg->setRoutingPort(_Xminus_);
         else if (deltaY > +1) msg->setRoutingPort(_Yplus_);
         else if (deltaY < -1) msg->setRoutingPort(_Yminus_);
         else if (deltaZ > +1) msg->setRoutingPort(_Zplus_);
         else if (deltaZ < -1) msg->setRoutingPort(_Zminus_);
         else msg->setRoutingPort(_LocalNode_);
      }
      unsigned portout = extractOutputPortNumber(msg);
      
      //*****************************************************************
      //Ideal assignation of the first VC to request
      //*****************************************************************
      unsigned msgtype=msg->getVnet();
      unsigned VCFirstReq;
      //Oredered messages must request the same VC to avoid message forwarding
      if (msg->isOrdered()) VCFirstReq=1;
      else VCFirstReq= getFirstVCReqFor(iPort, portout, msgtype);
      
      m_InOutVCTable->setValueAt(iPort, VCFirstReq);
      //*****************************************************************

      TPZEvent VCAllocEvent(_VCAllocator_, iPort, portout, VCFirstReq, msg);
      getEventQueue().enqueue(VCAllocEvent, delayTime+m_routingDelay);

    }
   //**********************************************************************
   // EVENT= VIRTUAL CHANNEL ARBITRATION
   //**********************************************************************
    else if (event.type() == _VCAllocator_) 
    {
       unsigned iPort = event.source();
       unsigned oPort = event.destiny();
       unsigned VChannel = event.channel();
       TPZMessage* msg;
       m_MessageReceivedTable->valueAt(iPort, &msg);
       
       if ( ( (!(msg->isHeader())) && (!(msg->isHeadTail())) ) || (!iPort) || (!oPort) ) 
       {
          TPZString err;
          err.sprintf("%s :Some kind of error at this point", (char*)getComponent().asString() );
          EXIT_PROGRAM(err);
       }
       
#ifndef NO_TRAZA
       TPZString texto = getComponent().asString() + " Event VC ALLOCATION. TIME = ";
       texto += TPZString(getOwnerRouter().getCurrentTime()) + " # " + "iPort=" + TPZString(iPort) + " # oPort="
       + TPZString(oPort) + " # VChannel =" + TPZString(VChannel) + msg->asString() ;
       TPZWRITE2LOG(texto);
#endif
       
       //The absolute port value corresponding to the message must be calculated
       unsigned messtype=msg->getVnet();
       unsigned oVirtualChannel=getAbsolutValueForOutputVC(oPort, VChannel, messtype);
       
       TPZState state=getStateForOutputVC(oVirtualChannel);

       if (state!=FREE) 
       {
          //On the next VC arbitration event we request a different Virtual Channel
          unsigned mux = ((TPZCrossbar&)(getComponent())).getOutputMux();
          unsigned msgtypes = ((TPZCrossbar&)(getComponent())).getNumberMT();
          unsigned VCNextRequest;
          if (msg->isOrdered()) VCNextRequest=VChannel;
          else VCNextRequest=((VChannel)%(mux/msgtypes))+1;
          m_InOutVCTable->setValueAt(iPort, VCNextRequest);
#ifndef NO_TRAZA
          TPZString texto3 = getComponent().asString() + " VC Occupied" + " # New VC Requested = " + TPZString(VCNextRequest);
          TPZWRITE2LOG(texto3);
#endif
          TPZEvent VCAllocEvent(_VCAllocator_, iPort, oPort, VCNextRequest);
          getEventQueue().enqueue(VCAllocEvent, delayTime+m_VCArbitrationDelay);
       }
       else 
       {
#ifndef NO_TRAZA
          TPZString texto2 = getComponent().asString() + " Found Free VC" + " # OutputVC = " + TPZString(oVirtualChannel);
          TPZWRITE2LOG(texto2);
#endif
          setStateForOutputVC(oVirtualChannel, ASIGNED);
          TPZEvent SWAllocEvent(_SwitchAllocator_, iPort, oPort, VChannel, msg);
          getEventQueue().enqueue(SWAllocEvent, delayTime+m_VCArbitrationDelay);
       }
       ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::VCArbitration);
    }
   
   //**********************************************************************
   // EVENT= SWITCH ARBITRATION
   //**********************************************************************
    else if (event.type() == _SwitchAllocator_) 
    {
       unsigned iPort = event.source();
       unsigned oPort = event.destiny();
       unsigned VChannel = event.channel();
       TPZMessage* msg;
       m_MessageReceivedTable->valueAt(iPort, &msg);

#ifndef NO_TRAZA
       TPZString texto = getComponent().asString() + " Event SW ALLOCATION. TIME = "
       + TPZString(getOwnerRouter().getCurrentTime()) + " # " + "iPort=" + TPZString(iPort)
       + " # oPort=" + TPZString(oPort) + " # VChannel =" + TPZString(VChannel) + msg->asString() ;
       TPZWRITE2LOG(texto);
#endif
       unsigned mux = ((TPZCrossbar&)(getComponent())).getOutputMux();
       unsigned msgtypes = ((TPZCrossbar&)(getComponent())).getNumberMT();
       unsigned messtype=msg->getVnet();
       unsigned outputVChannel= (messtype-1)*(mux/msgtypes) + VChannel;
       if (oPort == m_outputs) outputVChannel=1;
       
       TPZState state=getStateForOutputPort(oPort);
       
       if ( (!outputInterfaz(oPort)->isStopActive(outputVChannel)) && state==FREE) 
       {
#ifndef NO_TRAZA
          TPZString texto2 = getComponent().asString() + " Free Port=" + TPZString(oPort) + "turns into ASIGNED";
          TPZWRITE2LOG(texto2);
#endif
          setStateForOutputPort(oPort, ASIGNED);
	  m_InOutPortTable->setValueAt(iPort, oPort);
          TPZEvent SWTravEvent(_SwitchTraversal_, iPort, oPort, VChannel, msg);
          getEventQueue().enqueue(SWTravEvent, delayTime+m_SWArbitrationDelay);
       }
       else 
       {
#ifndef NO_TRAZA
          TPZString texto3 = getComponent().asString() + "already occupied port";
          TPZWRITE2LOG(texto3);
#endif
          TPZEvent SWAllocEvent(_SwitchAllocator_, iPort, oPort, VChannel, msg);
          getEventQueue().enqueue(SWAllocEvent, delayTime+m_SWArbitrationDelay);
       }
       ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::SWArbitration);
    }
   //**********************************************************************
   // EVENT= SWITCH TRAVERSAL
   //**********************************************************************
    else if (event.type() == _SwitchTraversal_) 
    {
       unsigned iPort = event.source();
       unsigned oPort = event.destiny();
       unsigned VChannel = event.channel();
       TPZMessage* msg;
       m_MessageReceivedTable->valueAt(iPort, &msg);
       
#ifndef NO_TRAZA
       TPZString texto = getComponent().asString() + " Event SW TRAVERSAL. TIME = "
       + TPZString(getOwnerRouter().getCurrentTime()) + " # " + "iPort=" + TPZString(iPort)
       + " # oPort=" + TPZString(oPort) + " # VChannel =" + TPZString(VChannel) + msg->asString() ;
        TPZWRITE2LOG(texto);
#endif
       unsigned mux = ((TPZCrossbar&)(getComponent())).getOutputMux();
       unsigned msgtypes = ((TPZCrossbar&)(getComponent())).getNumberMT();
       unsigned messtype=msg->getVnet();
       unsigned outputVChannel= (messtype-1)*(mux/msgtypes) + VChannel;
       if (oPort == m_outputs) outputVChannel=1;
       
       inputInterfaz(iPort)->clearStopRightNow();
       if (!msg->isMulticast() )updateMessageInfo(msg);//only unicast message need to update their contents.
       outputInterfaz(oPort)->sendData(msg, outputVChannel);
#ifndef NO_TRAZA
       TPZString texto2 = getComponent().asString() + "Port liberation =" + TPZString(oPort);
       TPZWRITE2LOG(texto2);
#endif
       setStateForOutputPort(oPort, FREE);

       if (msg->isTail() || msg->isHeadTail() ) 
       {
          unsigned oVirtualChannel= getAbsolutValueForOutputVC(oPort, VChannel, messtype);
          
#ifndef NO_TRAZA
            TPZString texto3 = getComponent().asString() + "Channel liberation =" + TPZString(oVirtualChannel);
            TPZWRITE2LOG(texto3);
#endif
          setStateForOutputVC(oVirtualChannel, FREE);
       }
       ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::SWTraversal);
       if ( ((TPZCrossbar&)getComponent()).getTypeForOutput(oPort,1) != _LocalNode_)
       {
          getOwnerRouter().incrLinkUtilization();
	  ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::LinkTraversal);
       }
    }
    return true;
}
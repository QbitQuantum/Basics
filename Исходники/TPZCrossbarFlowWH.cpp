//*************************************************************************
//:
//  f: virtual Boolean dispatchEvent (const TPZEvent & event);
//
//  d:
//:
//*************************************************************************
Boolean TPZCrossbarFlowWH :: dispatchEvent(const TPZEvent& event)
{
   uTIME delayTime = getOwnerRouter().getCurrentTime();

   //**********************************************************************
   // EVENT= ROUTING
   //**********************************************************************
   if( event.type() == _RoutingVC_ )
   {

      //update the header and select output port
      TPZMessage *msg;
      unsigned iPort = event.source();
      m_MessageReceivedTable->valueAt(iPort,&msg);

      if( (!(msg->isHeader())) && (!(msg->isHeadTail())))
      {
         TPZString err;
         err.sprintf( "%s :Data flits should not pass through this event",(char*)getComponent().asString() );
         EXIT_PROGRAM(err);
      }

#ifndef NO_TRAZA
         TPZString texto = getComponent().asString() + " Event ROUTING. TIME = ";
         texto += TPZString(getOwnerRouter().getCurrentTime()) + " # " + "iPort=" + TPZString(iPort) + " # " + msg->asString() ;
         TPZWRITE2LOG( texto );
#endif

      if (!msg->isMulticast())//multicast messages are proceesed at FIFO buffer, avoid re-routing
      {
         int deltaX = msg->delta(0);
         int deltaY = msg->delta(1);
         int deltaZ = msg->delta(2);

         if( deltaX > 1 ) msg->setRoutingPort(_Xplus_);
         else if( deltaX < -1 ) msg->setRoutingPort(_Xminus_);
         else if( deltaY > +1 ) msg->setRoutingPort(_Yplus_);
         else if( deltaY < -1 ) msg->setRoutingPort(_Yminus_);
         else if( deltaZ > +1 ) msg->setRoutingPort(_Zplus_);
         else if( deltaZ < -1 ) msg->setRoutingPort(_Zminus_);
         else msg->setRoutingPort(_LocalNode_);
      }
      unsigned portout = extractOutputPortNumber(msg);
      m_InOutPortTable->setValueAt(iPort, portout);

      TPZEvent SWAllocEvent(_SwitchAllocator_, iPort, portout, 1, msg);
      getEventQueue().enqueue(SWAllocEvent, delayTime+m_routingDelay);

   }

   //**********************************************************************
   // EVENT= SWITCH ALLOCATION
   //**********************************************************************
   else if( event.type() == _SwitchAllocator_ )
   {

      unsigned iPort  = event.source();
      unsigned oPort = event.destiny();
      TPZMessage* msg;
      m_MessageReceivedTable->valueAt(iPort,&msg);

#ifndef NO_TRAZA
      TPZString texto = getComponent().asString() + " Event SW ALLOCATION. TIME = "
      + TPZString(getOwnerRouter().getCurrentTime()) + " # " + "iPort=" + TPZString(iPort)
      + " # oPort=" + TPZString(oPort) + msg->asString() ;
      TPZWRITE2LOG( texto );
#endif

      if (getStateForOutputPort(oPort)==FREE)
      {
#ifndef NO_TRAZA
         TPZString texto2 = getComponent().asString() + " Free port=" + TPZString(oPort);
         TPZWRITE2LOG( texto2);
#endif
         setStateForOutputPort(oPort, ASIGNED);

         TPZEvent SWTravEvent(_SwitchTraversal_, iPort, oPort, 1, msg);
         getEventQueue().enqueue(SWTravEvent, delayTime+1);
      }

      else
      {
#ifndef NO_TRAZA
         TPZString texto3 = getComponent().asString() + "Occupied port";
         TPZWRITE2LOG( texto3 );
#endif

         TPZEvent SWAllocEvent(_SwitchAllocator_,iPort, oPort, 1, msg);
         getEventQueue().enqueue(SWAllocEvent, delayTime+m_SWArbitrationDelay);
      }
      ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::SWArbitration);
   }

   //**********************************************************************
   // EVENT= SWITCH TRAVERSAL
   //**********************************************************************
   else if( event.type() == _SwitchTraversal_ )
   {

      unsigned iPort  = event.source();
      unsigned oPort = event.destiny();
      TPZMessage* msg;
      m_MessageReceivedTable->valueAt(iPort,&msg);

#ifndef NO_TRAZA
      TPZString texto = getComponent().asString() + " Event SW TRAVERSAL. TIME = "
      + TPZString(getOwnerRouter().getCurrentTime()) + " # " + "iPort=" + TPZString(iPort)
      + " # oPort=" + TPZString(oPort) + msg->asString() ;
      TPZWRITE2LOG( texto );
#endif

      if ( (!outputInterfaz(oPort)->isStopActive()))
      {
         inputInterfaz(iPort)->clearStopRightNow();
         if (!msg->isMulticast()) updateMessageInfo(msg); //again, MC messages already processed
         outputInterfaz(oPort)->sendData(msg);

         if ( msg->isTail() || msg->isHeadTail() )
         {
            setStateForOutputPort(oPort, FREE);
         }

	 ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::SWTraversal);
	 if ( ((TPZCrossbar&)getComponent()).getTypeForOutput(oPort,1) != _LocalNode_)
	 {
	    getOwnerRouter().incrLinkUtilization();
	    ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::LinkTraversal);
	 }
      }
      else
      {
         uTIME delayTime = getOwnerRouter().getCurrentTime() ;
         TPZEvent SWTravEvent(_SwitchTraversal_,iPort, oPort, 1, msg);
         getEventQueue().enqueue(SWTravEvent, delayTime+m_SWTraversalDelay);
      }

   }
   return true;
}
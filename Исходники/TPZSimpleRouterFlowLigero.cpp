//*************************************************************************
//:
//  f: virtual Boolean inputReading ();
//
//  d:
//:
//*************************************************************************
Boolean TPZSimpleRouterFlowLigero :: inputReading()
{
   unsigned outPort;
   unsigned inPort;
   unsigned virtualChannel=1;
   cleanOutputInterfaces();
   TPZNetwork* net = ((TPZSimulation*)(getComponent().getSimulation()))->getNetwork();

#ifndef NO_TRAZA
   TPZString txt_comp= getComponent().asString() + TPZString(" TIME: ") + TPZString(getOwnerRouter().getCurrentTime());
#endif

   //**********************************************************************************************************
   //**********************************************************************************************************
   // PART 0: ESCAPE PATH
   //**********************************************************************************************************
   //**********************************************************************************************************

   //**********************************************************************************
   // Part 0-a: fifo escape
   //**********************************************************************************
   if( (! m_latch_escape ) && (m_fifo_escape.numberOfElements()!=0) )
   {
      m_fifo_escape.dequeue(m_latch_escape);
   }

   m_clearEscConnection=false;

   if(m_latch_escape)
   {
#ifndef NO_TRAZA
      TPZString texto = txt_comp + " LATCH-ESCAPE " + m_latch_escape->asString();
      texto += TPZString(" Occupation:") + TPZString(m_fifo_escape.numberOfElements());
      TPZWRITE2LOG(texto);
#endif
      Boolean checkFlow=true;

      if (m_latch_escape->isHeader() || m_latch_escape->isHeadTail())
      {
         m_escape_ctrl= getOutputDirection(m_latch_escape);
	 outPort=extractOutputPortNumber(m_escape_ctrl);
         if ( (m_escape_ctrl==_LocalNode_) && (checkFlowControl(0, m_fifos_cons, 1, m_bufferSize)==false) )
         {
	    checkFlow=false;
	 }
	 if ( (m_escape_ctrl!=_LocalNode_) && ( (checkEscapePath(m_escape_ctrl)==false) || (m_linkAvailable[outPort]==false) ) )
	 {
	    checkFlow=false;
	 }
      }

      if (checkFlow==true)
      {
         if (m_escape_ctrl==_LocalNode_)
	 {
#ifndef NO_TRAZA
            TPZString texto = txt_comp + " ESCAPE->CONS " + m_latch_escape->asString();
            TPZWRITE2LOG(texto);	
#endif
            m_fifos_cons[0].enqueue(m_latch_escape);
	    m_escape_ctrl=_LocalNode_;
	    m_latch_escape=0;	
	 }
	 else
	 {
#ifndef NO_TRAZA
            TPZString texto2 = txt_comp + " LINK TRAVERSAL (ESCAPE) " + TPZString(outPort) + m_latch_escape->asString();
            TPZWRITE2LOG(texto2);
#endif	
	    outPort=extractOutputPortNumber(m_escape_ctrl);
	    if (m_latch_escape->isHeader() || m_latch_escape->isHeadTail()) m_linkAvailable[outPort]=false;
	
	    outputInterfaz(outPort)->sendData(m_latch_escape,virtualChannel);
            ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::OStageTraversal);
            getOwnerRouter().incrLinkUtilization();
            ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::LinkTraversal);
	
	    // Clear the latch and the connection if necessary
            if( m_latch_escape->isHeadTail() || m_latch_escape->isTail()) m_clearEscConnection=true;
            m_latch_escape=0;
	 }
      }
   }
   //**********************************************************************************
   // Part 0-b: fifo reading to fill latches
   //**********************************************************************************
   if( (! m_latch_pre_escape ) && (m_fifo_pre_escape.numberOfElements()!=0) )
   {
      m_fifo_pre_escape.dequeue(m_latch_pre_escape);
   }
   if( (! m_latch_inj_escape ) && (m_fifo_inj_escape.numberOfElements()!=0) )
   {
      m_fifo_inj_escape.dequeue(m_latch_inj_escape);
   }

   //**********************************************************************************
   // Part 0-c: arbitration to access escape fifo
   //**********************************************************************************

   //first messages trying to access escape path for the first time
   if(m_latch_inj_escape)
   {
#ifndef NO_TRAZA
      TPZString texto = txt_comp + " LATCH-INJ-ESCAPE " + m_latch_inj_escape->asString();
      texto += TPZString(" Occupation:") + TPZString(m_fifo_inj_escape.numberOfElements());
      TPZWRITE2LOG(texto);
#endif
      Boolean checkFlow=true;

      if (m_latch_inj_escape->isHeader() || m_latch_inj_escape->isHeadTail())
      {
         //bubble check to access the escape path
	 if( (checkEscapeFlowControl()==false) || m_escAvailable==false) checkFlow=false;
	 else m_escAvailable=false;	
      }

      if (checkFlow==true)
      {
#ifndef NO_TRAZA
         TPZString texto = txt_comp + " INJ-ESCAPE->ESCAPE " + m_latch_inj_escape->asString();
         TPZWRITE2LOG(texto);
#endif
	 m_fifo_escape.enqueue(m_latch_inj_escape);
	 if (m_latch_inj_escape->isTail() || m_latch_inj_escape->isHeadTail()) m_clearPreEsc=true;
	 m_latch_inj_escape=0;	
      }
   }

   //Then we arbitrate messages in transit through escape path
   if(m_latch_pre_escape)
   {
#ifndef NO_TRAZA
      TPZString texto = txt_comp + " LATCH-PRE-ESCAPE " + m_latch_pre_escape->asString();
      texto += TPZString(" Occupation:") + TPZString(m_fifo_pre_escape.numberOfElements());
      TPZWRITE2LOG(texto);
#endif
      Boolean checkFlow=true;

      if (m_latch_pre_escape->isHeader() || m_latch_pre_escape->isHeadTail())
      {
         //simple CT check for messages in transit
	 if( (m_fifo_escape.numberOfElements()>2) || m_escAvailable==false) checkFlow=false;
	 else m_escAvailable=false;	
      }

      if (checkFlow==true)
      {
#ifndef NO_TRAZA
         TPZString texto = txt_comp + " PRE-ESCAPE->ESCAPE " + m_latch_pre_escape->asString();
         TPZWRITE2LOG(texto);
#endif
	 m_fifo_escape.enqueue(m_latch_pre_escape);
	 if (m_latch_pre_escape->isTail() || m_latch_pre_escape->isHeadTail()) m_clearPreEsc=true;
	 m_latch_pre_escape=0;
	
      }
   }

   //Finally, we check mux status
   if (m_clearPreEsc==true)
   {
      m_escAvailable=true;
      m_clearPreEsc=false;
   }

   //**********************************************************************************************************
   //**********************************************************************************************************
   // PART 1: CONSUMPTION
   //**********************************************************************************************************
   //**********************************************************************************************************

   //in the case of consumption, for index starts with 0 because the zero position
   //is employed for escape path. the rest of for loops start with 1.
   for( inPort = 0; inPort < m_ports; inPort++)
   {
     // Injection buffers
      if( (! m_latch_cons[inPort] ) && (m_fifos_cons[inPort].numberOfElements()!=0) )
      {
         m_fifos_cons[inPort].dequeue(m_latch_cons[inPort]);
      }
   }
   // Clear connection
   m_clearConsConnection=false;

   for( inPort = 0; inPort < m_ports; inPort++)
   {
      if( ! m_latch_cons[inPort] ) continue;

      if( m_latch_cons[inPort]->isHeader() || m_latch_cons[inPort]->isHeadTail() )
      {
         //First we check if the link is in use
	 if(m_consAvailable==false) continue;
	
	 if( outputInterfaz(m_ports)->isStopActive(virtualChannel) ) continue;
	
	 //reserve the link for the remaining flits
	 m_consAvailable=false;
      }

      //send the message
      outputInterfaz(m_ports)->sendData(m_latch_cons[inPort],virtualChannel);
      	
#ifndef NO_TRAZA
      TPZString texto = txt_comp + " TO CONSUMER " + m_latch_cons[inPort]->asString();
      TPZWRITE2LOG(texto);
#endif

      // Clear the latch and the connection if necessary
      if( m_latch_cons[inPort]->isHeadTail() || m_latch_cons[inPort]->isTail() ) m_clearConsConnection=true;
      m_latch_cons[inPort]=0;
   }

   if (m_clearConsConnection==true) m_consAvailable=true;

   //**********************************************************************************************************
   //**********************************************************************************************************
   // PART 2: OUTPUT STAGE
   //**********************************************************************************************************
   //**********************************************************************************************************

   //**********************************************************************************
   // Part 2-a: from buffers to latches
   //**********************************************************************************
   for( outPort = 1; outPort < m_ports; outPort++)
   {
      // Bypass buffers
      if( (! m_latch_out_byp[outPort] ) && (m_fifos_out_byp[outPort].numberOfElements()!=0) )
      {
         m_fifos_out_byp[outPort].dequeue(m_latch_out_byp[outPort]);
      }

      // From-Ring buffers
      if( (! m_latch_out_turn[outPort] ) && (m_fifos_out_turn[outPort].numberOfElements()!=0) )
      {
         m_fifos_out_turn[outPort].dequeue(m_latch_out_turn[outPort]);
      }

      // Injection buffers
      if( (! m_latch_out_inj[outPort] ) && (m_fifos_out_inj[outPort].numberOfElements()!=0) )
      {
         m_fifos_out_inj[outPort].dequeue(m_latch_out_inj[outPort]);
      }

      // Clear connection
      m_clearConnection[outPort]=false;

   }
   //**********************************************************************************
   // Part 2-b: Request the Output link for Bypass buffers
   //**********************************************************************************
   for( outPort = 1; outPort < m_ports; outPort++)
   {
      if( ! m_latch_out_byp[outPort] ) continue;
#ifndef NO_TRAZA
      TPZString texto = txt_comp + " LATCH-OUT-BYPASS " + m_latch_out_byp[outPort]->asString();
      texto += TPZString(" outPort:") + TPZString(outPort);
      texto += TPZString(" Occupation:") + TPZString(m_fifos_out_byp[outPort].numberOfElements());
      TPZWRITE2LOG(texto);
#endif
      if( m_latch_out_byp[outPort]->isHeader() || m_latch_out_byp[outPort]->isHeadTail() )
      {
         //First we check if the link is in use and if the next router has buffers available
	 if(m_linkAvailable[outPort]==false) continue;	
	 if( outputInterfaz(outPort)->isStopActive(virtualChannel) ) continue;
	
	 //reserve the link for the remaining flits
	 m_linkAvailable[outPort]=false;	
      }

      //send the message
      updateMessageInfo(m_latch_out_byp[outPort], outPort);
      outputInterfaz(outPort)->sendData(m_latch_out_byp[outPort],virtualChannel);
      ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::OStageTraversal);

      if ( ((TPZSimpleRouter&)getComponent()).getTypeForOutput(outPort) != _LocalNode_ )
      {
         getOwnerRouter().incrLinkUtilization();
         ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::LinkTraversal);
      }
	
#ifndef NO_TRAZA
      TPZString texto2 = txt_comp + " LINK TRAVERSAL (BYPASS) " + m_latch_out_byp[outPort]->asString();
      TPZWRITE2LOG(texto2);
#endif

      // Clear the latch and the connection if necessary
      if( m_latch_out_byp[outPort]->isHeadTail() || m_latch_out_byp[outPort]->isTail() )
      {
         m_clearConnection[outPort]=true;
	
	 //If the message is ordered, clear the input port restriction
	 if(m_latch_out_byp[outPort]->isOrdered()) m_interfazInOrder[m_latch_out_byp[outPort]->getInputInterfaz()]=false;
      }
      m_latch_out_byp[outPort]=0;
   }

   //**********************************************************************************
   // PART 2-c: Request the Output link for From-Ring buffers
   //**********************************************************************************
   for( outPort = 1; outPort < m_ports; outPort++)
   {
      if( ! m_latch_out_turn[outPort] ) continue;
 #ifndef NO_TRAZA
      TPZString texto = txt_comp + " LATCH-OUT-TURN " + m_latch_out_turn[outPort]->asString();
      texto += TPZString(" outPort:") + TPZString(outPort);
      texto += TPZString(" Occupation:") + TPZString(m_fifos_out_turn[outPort].numberOfElements());
      TPZWRITE2LOG(texto);
#endif
      if( m_latch_out_turn[outPort]->isHeader() || m_latch_out_turn[outPort]->isHeadTail() )
      {
         //First we check if the link is in use
	 if(m_linkAvailable[outPort]==false) continue;
	
	 if( outputInterfaz(outPort)->isStopActive(virtualChannel) ) continue;
	
	 //If the msg is on Escape, bubble must be checked
	 if ( (m_latch_out_turn[outPort]->isOnScape()==true) && (checkEscapeFlowControl()==false) ) continue;
	
	 //reserve the link for the remaining flits
	 m_linkAvailable[outPort]=false;
      }

      //send the message
      updateMessageInfo(m_latch_out_turn[outPort], outPort);
      outputInterfaz(outPort)->sendData(m_latch_out_turn[outPort],virtualChannel);
      ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::OStageTraversal);

      if ( ((TPZSimpleRouter&)getComponent()).getTypeForOutput(outPort) != _LocalNode_ )
      {
         getOwnerRouter().incrLinkUtilization();
         ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::LinkTraversal);
      }
	
#ifndef NO_TRAZA
     TPZString texto2 = txt_comp + " LINK TRAVERSAL (RING) " + m_latch_out_turn[outPort]->asString();
      TPZWRITE2LOG(texto2);
#endif

      // Clear the latch and the connection if necessary
      if( m_latch_out_turn[outPort]->isHeadTail() || m_latch_out_turn[outPort]->isTail() )
      {
         m_clearConnection[outPort]=true;
	
	 //If the message is ordered, clear the input port restriction
	 if(m_latch_out_turn[outPort]->isOrdered()) m_interfazInOrder[m_latch_out_turn[outPort]->getInputInterfaz()]=false;
      }
      m_latch_out_turn[outPort]=0;
   }

   //**********************************************************************************
   // PART 2-d: Request the Output link for Injection buffers
   //**********************************************************************************
   for( outPort = 1; outPort <= m_ports; outPort++)
   {
      if( ! m_latch_out_inj[outPort] ) continue;
#ifndef NO_TRAZA
      TPZString texto = txt_comp + " LATCH-OUT-INJ " + m_latch_out_inj[outPort]->asString();
      texto += TPZString(" outPort:") + TPZString(outPort);
      texto += TPZString(" Occupation:") + TPZString(m_fifos_out_inj[outPort].numberOfElements());
      TPZWRITE2LOG(texto);
#endif
      if( m_latch_out_inj[outPort]->isHeader() || m_latch_out_inj[outPort]->isHeadTail() )
      {
         //First we check if the link is in use
	 if(m_linkAvailable[outPort]==false) continue;
	 if( outputInterfaz(outPort)->isStopActive(virtualChannel) ) continue;
	
	 //reserve the link for the remaining flits
	 m_linkAvailable[outPort]=false;
      }

      //send the message
      updateMessageInfo(m_latch_out_inj[outPort], outPort);
      outputInterfaz(outPort)->sendData(m_latch_out_inj[outPort],virtualChannel);
      ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::OStageTraversal);

      if ( ((TPZSimpleRouter&)getComponent()).getTypeForOutput(outPort) != _LocalNode_ )
      {
         getOwnerRouter().incrLinkUtilization();
         ((TPZNetwork*)(getOwnerRouter().getOwner()))->incrEventCount( TPZNetwork::LinkTraversal);
      }
	
#ifndef NO_TRAZA
      TPZString texto2 = txt_comp + " LINK TRAVERSAL (INJ) " + m_latch_out_inj[outPort]->asString();
      TPZWRITE2LOG(texto2);
#endif

      // Clear the latch and the connection if necessary
      if( m_latch_out_inj[outPort]->isHeadTail() || m_latch_out_inj[outPort]->isTail() ) m_clearConnection[outPort]=true;
      m_latch_out_inj[outPort]=0;
   }

   //**********************************************************************************
   // PART 2-e: Clear all the links (tail flit) occupied this cycle
   //**********************************************************************************
   for( outPort = 1; outPort <= m_ports; outPort++)
   {
      if (m_clearConnection[outPort]==true) m_linkAvailable[outPort]=true;
   }

   if (m_clearEscConnection==true)
   {
      outPort=extractOutputPortNumber(m_escape_ctrl);
      m_linkAvailable[outPort]=true;
   }

   //**********************************************************************************************************
   //**********************************************************************************************************
   // PART 3: MULTIPORT BUFFERS (INTERNAL RING)
   //**********************************************************************************************************
   //**********************************************************************************************************

   //**********************************************************************************
   // Part 3-a: from buffers to latches
   //**********************************************************************************
   for( inPort = 1; inPort < m_ports; inPort++)
   {
      if( (! m_latch_mp_one[inPort] ) && (m_fifos_mp_one[inPort].numberOfElements()!=0) )
      {
         m_fifos_mp_one[inPort].dequeue(m_latch_mp_one[inPort]);
      }
      if( (! m_latch_mp_two[inPort] ) && (m_fifos_mp_two[inPort].numberOfElements()!=0) )
      {
         m_fifos_mp_two[inPort].dequeue(m_latch_mp_two[inPort]);
      }

      m_clearRingExit[inPort]=false;
      m_clearRingAdvance[inPort]=false;
   }

   //**********************************************************************************
   // Part 3-b: Arbitrate buffer one (the one comming from input stage)
   //**********************************************************************************
   for( inPort = 1; inPort < m_ports; inPort++)
   {
      if( !m_latch_mp_one[inPort] ) continue;
      //********************************************************
      // BORRAR, INJECTION ON SCAPE ALWAYS
      //********************************************************
      //m_latch_mp_one[inPort]->setOnScape();
      //********************************************************
      if( m_latch_mp_one[inPort]->isHeader() || m_latch_mp_one[inPort]->isHeadTail() )
      {
         //First we check if the message can leave the ring
	 if(m_ringExitAvailable[inPort]==true && checkFlowControl((inPort%(m_ports-1))+1, m_fifos_out_turn, 1, m_OSSize)==true)
	 {
	    Boolean checkHead=checkHeader(inPort, m_latch_mp_one[inPort]);
	    if ( checkHead==true )
	    {
#ifndef NO_TRAZA
               TPZString texto = txt_comp + " MP->OSTAGE " + m_latch_mp_one[inPort]->asString();
	       texto += TPZString(" OutPort= ") + TPZString((inPort%(m_ports-1))+1);
               TPZWRITE2LOG(texto);
#endif	
               m_fifos_out_turn[(inPort%(m_ports-1))+1].enqueue(m_latch_mp_one[inPort]);
	       m_mp_one_ctrl[inPort]=Leave;
	       m_ringExitAvailable[inPort]=false;
	       if(m_latch_mp_one[inPort]->isHeadTail()) m_clearRingExit[inPort]=true;
	       m_latch_mp_one[inPort]=0;
	       continue;
	    }
	 }
	
	 //If not, we request the next multiport. As we are entering the internal router ring
	 //two conditions: two holes on mp_two[inPort] and one hole on mp_two[(inPort%(m_ports-1))+1]
	 Boolean BubbleFlowControl=checkFlowControl(inPort, m_fifos_mp_two, 2, m_MPSize );
	 Boolean CTFlowControl=checkFlowControl((inPort%(m_ports-1))+1, m_fifos_mp_two, 1, m_MPSize);
	
	 if(m_ringAdvanceAvailable[inPort]==true && BubbleFlowControl==true && CTFlowControl==true)
	 {
#ifndef NO_TRAZA
            TPZString texto = txt_comp + " MP->MP " + m_latch_mp_one[inPort]->asString();
	    texto += TPZString(" NextMP= ") + TPZString((inPort%(m_ports-1))+1);
            TPZWRITE2LOG(texto);
#endif	
	    m_fifos_mp_two[(inPort%(m_ports-1))+1].enqueue(m_latch_mp_one[inPort]);
	    m_mp_one_ctrl[inPort]=Advance;
	    m_ringAdvanceAvailable[inPort]=false;
	    if(m_latch_mp_one[inPort]->isHeadTail()) m_clearRingAdvance[inPort]=true;
	    m_latch_mp_one[inPort]=0;
	    continue;
	 }
      }
      else
      {
         if ( m_mp_one_ctrl[inPort]==Leave)
	 {
#ifndef NO_TRAZA
            TPZString texto = txt_comp + " MP->OSTAGE " + m_latch_mp_one[inPort]->asString();
	    texto += TPZString(" OutPort= ") + TPZString((inPort%(m_ports-1))+1);
            TPZWRITE2LOG(texto);
#endif	
	    m_fifos_out_turn[(inPort%(m_ports-1))+1].enqueue(m_latch_mp_one[inPort]);
	    if(m_latch_mp_one[inPort]->isTail()) m_clearRingExit[inPort]=true;
	    m_latch_mp_one[inPort]=0;
	 }
	 else
	 {
#ifndef NO_TRAZA
            TPZString texto = txt_comp + " MP->MP " + m_latch_mp_one[inPort]->asString();
	    texto += TPZString(" NextMP= ") + TPZString((inPort%(m_ports-1))+1);
            TPZWRITE2LOG(texto);
#endif	
	    m_fifos_mp_two[(inPort%(m_ports-1))+1].enqueue(m_latch_mp_one[inPort]);
	    if(m_latch_mp_one[inPort]->isTail()) m_clearRingAdvance[inPort]=true;
	    m_latch_mp_one[inPort]=0;
	 }
      }
   }
   //**********************************************************************************
   // Part 3-c: Arbitrate buffer two (the one forming the ring)
   //**********************************************************************************
   for( inPort = 1; inPort < m_ports; inPort++)
   {
      if( !m_latch_mp_two[inPort] ) continue;

      if( m_latch_mp_two[inPort]->isHeader() || m_latch_mp_two[inPort]->isHeadTail() )
      {
         //First we check if the message must go to escape path
	 if( (inPort==1) && m_latch_mp_two[inPort]->isOnScape() )
	 {
	    if(m_fifo_inj_escape.numberOfElements()<=2)
	    {
#ifndef NO_TRAZA
               TPZString texto = txt_comp + " MP->ESCAPE " + m_latch_mp_two[inPort]->asString();
	       texto += TPZString(" OutPort= ") + TPZString((inPort%(m_ports-1))+1);
               TPZWRITE2LOG(texto);
#endif 	
	       m_fifo_inj_escape.enqueue(m_latch_mp_two[inPort]);
	       m_mp_two_ctrl[inPort]=Escape;
	       m_latch_mp_two[inPort]=0;
	       continue;
	    }
	 }
	
	 //Then we check if the message can leave the ring
	 if(m_ringExitAvailable[inPort]==true && checkFlowControl((inPort%(m_ports-1))+1, m_fifos_out_turn, 1, m_OSSize)==true)
	 {
	    Boolean checkHead=checkHeader(inPort, m_latch_mp_two[inPort]);
	    if ( checkHead==true )
	    {
#ifndef NO_TRAZA
               TPZString texto = txt_comp + " MP->OSTAGE " + m_latch_mp_two[inPort]->asString();
	       texto += TPZString(" OutPort= ") + TPZString((inPort%(m_ports-1))+1);
               TPZWRITE2LOG(texto);
#endif 	
	       m_fifos_out_turn[(inPort%(m_ports-1))+1].enqueue(m_latch_mp_two[inPort]);
	       m_mp_two_ctrl[inPort]=Leave;
	       m_ringExitAvailable[inPort]=false;
	       if(m_latch_mp_two[inPort]->isHeadTail()) m_clearRingExit[inPort]=true;
	       m_latch_mp_two[inPort]=0;
	       continue;
	    }
	 }
	
	 //If not, we request the next multiport
	 if(m_ringAdvanceAvailable[inPort]==true && checkFlowControl((inPort%(m_ports-1))+1, m_fifos_mp_two, 1, m_MPSize)==true)
	 {
#ifndef NO_TRAZA
            TPZString texto = txt_comp + " MP->MP " + m_latch_mp_two[inPort]->asString();
	    texto += TPZString(" NextMP= ") + TPZString((inPort%(m_ports-1))+1);
            TPZWRITE2LOG(texto);
#endif	
	    m_fifos_mp_two[(inPort%(m_ports-1))+1].enqueue(m_latch_mp_two[inPort]);
	    m_mp_two_ctrl[inPort]=Advance;
	    m_ringAdvanceAvailable[inPort]=false;
	    if(m_latch_mp_two[inPort]->isHeadTail()) m_clearRingAdvance[inPort]=true;
	
	    //Normal messages must check the number of multiports to move to missrtg or escape
	    if (!m_latch_mp_two[inPort]->isOrdered())
	    {
	       if (m_latch_mp_two[inPort]->getLastMissRouted()==false && m_latch_mp_two[inPort]->isOnScape()==false)
	       {
	          m_latch_mp_two[inPort]->incrMultiportNumber();
	          if (m_latch_mp_two[inPort]->getMultiportNumber() >= (m_ports-1)*m_missLoops)
                  {
                     m_latch_mp_two[inPort]->incrTimesMiss();
                     if (m_latch_mp_two[inPort]->getTimesMiss() >= m_missLimit) m_latch_mp_two[inPort]->setOnScape();
                     else m_latch_mp_two[inPort]->setLastMissRouted(true);
                  }
	       }
	    }
	    m_latch_mp_two[inPort]=0;
	    continue;
	 }
      }
      else
      {
         if ( m_mp_two_ctrl[inPort]==Escape)
	 {
#ifndef NO_TRAZA
            TPZString texto = txt_comp + " MP->ESCAPE " + m_latch_mp_two[inPort]->asString();
	    texto += TPZString(" OutPort= ") + TPZString((inPort%(m_ports-1))+1);
            TPZWRITE2LOG(texto);
#endif	
	    m_fifo_inj_escape.enqueue(m_latch_mp_two[inPort]);
	    m_latch_mp_two[inPort]=0;
	 }
	 else if ( m_mp_two_ctrl[inPort]==Leave)
	 {
#ifndef NO_TRAZA
            TPZString texto = txt_comp + " MP->OSTAGE " + m_latch_mp_two[inPort]->asString();
	    texto += TPZString(" OutPort= ") + TPZString((inPort%(m_ports-1))+1);
            TPZWRITE2LOG(texto);
#endif	
	    m_fifos_out_turn[(inPort%(m_ports-1))+1].enqueue(m_latch_mp_two[inPort]);
	    if(m_latch_mp_two[inPort]->isTail()) m_clearRingExit[inPort]=true;
	    m_latch_mp_two[inPort]=0;
	 }
	 else
	 {
#ifndef NO_TRAZA
            TPZString texto = txt_comp + " MP->MP " + m_latch_mp_two[inPort]->asString();
	    texto += TPZString(" NextMP= ") + TPZString((inPort%(m_ports-1))+1);
            TPZWRITE2LOG(texto);
#endif	
	    m_fifos_mp_two[(inPort%(m_ports-1))+1].enqueue(m_latch_mp_two[inPort]);
	    if(m_latch_mp_two[inPort]->isTail()) m_clearRingAdvance[inPort]=true;
	    m_latch_mp_two[inPort]=0;
	 }
      }
   }

   //**********************************************************************************
   // Part 3-d: Clear finished connections
   //**********************************************************************************
   for( inPort = 1; inPort < m_ports; inPort++)
   {
      if (m_clearRingExit[inPort]==true) m_ringExitAvailable[inPort]= true;
      if (m_clearRingAdvance[inPort]==true) m_ringAdvanceAvailable[inPort]= true;
   }

   //****************************************************************************************************************
   //****************************************************************************************************************
   // PART 4: INPUT STAGE
   //****************************************************************************************************************
   //****************************************************************************************************************

   //**********************************************************************************
   // Part 4-a: from buffers to latches
   //**********************************************************************************
   for(inPort = 1; inPort <= m_ports; inPort++)
   {
      // If the routing is empty, Take the next message from the corresponding fifo
      if( (! m_routing[inPort] ) && (m_fifos[inPort].numberOfElements()!=0) )
      {
         m_fifos[inPort].dequeue(m_routing[inPort]);
      }
   }
   //**********************************************************************************
   // PART 4-b: Then arbitrate msg access to the next stage
   //**********************************************************************************
   for(inPort = 1; inPort < m_ports; inPort++) //The last port is arbitrated different, is injection
   {
      // If the routing is empty, go to the next
      if( ! m_routing[inPort] ) continue;
 #ifndef NO_TRAZA
      TPZString texto = txt_comp + " LATCH-ISTAGE " + m_routing[inPort]->asString();
      texto += TPZString(" inPort: ") + TPZString(inPort);
      texto += TPZString(" Occupation: ") + TPZString(m_fifos[inPort].numberOfElements());
      TPZWRITE2LOG(texto);
#endif

      if( m_routing[inPort]->isHeader() || m_routing[inPort]->isHeadTail() )
      {
         TPZROUTINGTYPE direction= getOutputDirection(m_routing[inPort]);
	 outPort = extractOutputPortNumber(direction);
	
	 // First we check if it must be consumed
	 if( outPort == m_ports )
	 {
	    if(checkFlowControl(inPort, m_fifos_cons, 1, m_bufferSize)==true)
	    {
#ifndef NO_TRAZA
               TPZString texto = txt_comp + " ISTAGE->CONS " + m_routing[inPort]->asString();
               TPZWRITE2LOG(texto);
#endif
               m_fifos_cons[inPort].enqueue(m_routing[inPort]);
	       m_istage_ctrl[inPort]= Consume;
	       m_routing[inPort]=0;
	    }
	    continue;
	 }
	 //At this point we check inOrder restrictions
	 if( m_routing[inPort]->isOrdered() && m_interfazInOrder[inPort]==true)
	 {
#ifndef NO_TRAZA
            TPZString texto = txt_comp + " STOP-ORDERED " + m_routing[inPort]->asString();
            TPZWRITE2LOG(texto);
#endif 	
	    continue;
	 }
	
	 //Second we try the bypass path
	 if( (outPort == inPort) && (checkFlowControl(outPort, m_fifos_out_byp, 1, m_OSSize)==true) && !m_routing[inPort]->isOnScape() )
	 {
#ifndef NO_TRAZA
            TPZString texto = txt_comp + " ISTAGE->OSTAGE " + m_routing[inPort]->asString();
            TPZWRITE2LOG(texto);
#endif
            m_fifos_out_byp[outPort].enqueue(m_routing[inPort]);
	    m_istage_ctrl[inPort]= Bypass;
	    if(m_routing[inPort]->isOrdered())
	    {
	       m_interfazInOrder[inPort]=true;
	       m_routing[inPort]->setInputInterfaz(inPort);
	    }
	    m_routing[inPort]=0;
	    continue;
	 }
	
	 //Next we try to enter the internal router ring
	 if( checkFlowControl(inPort, m_fifos_mp_one, 1, m_MPSize)==true )
	 {
#ifndef NO_TRAZA
            TPZString texto = txt_comp + " ISTAGE->MP " + m_routing[inPort]->asString();
            TPZWRITE2LOG(texto);
#endif
            m_fifos_mp_one[inPort].enqueue(m_routing[inPort]);
	    m_istage_ctrl[inPort]= Turn;
	    if(m_routing[inPort]->isOrdered())
	    {
	       m_interfazInOrder[inPort]=true;
	       m_routing[inPort]->setInputInterfaz(inPort);
	    }
	    m_routing[inPort]=0;
	    continue;
	 }
	
      }
      else
      {
         if(m_istage_ctrl[inPort]==Bypass)
         {
#ifndef NO_TRAZA
            TPZString texto1 = txt_comp + " ISTAGE->OSTAGE " + m_routing[inPort]->asString();
            TPZWRITE2LOG(texto1);
#endif	
	    m_routing[inPort]->setInputInterfaz(inPort);
	    m_fifos_out_byp[inPort].enqueue(m_routing[inPort]);
	    m_routing[inPort]=0;
	 }
	 else if(m_istage_ctrl[inPort]==Turn)
	 {
#ifndef NO_TRAZA
           TPZString texto2 = txt_comp + " ISTAGE->MP " + m_routing[inPort]->asString();
            TPZWRITE2LOG(texto2);
#endif 	
            m_routing[inPort]->setInputInterfaz(inPort);
	    m_fifos_mp_one[inPort].enqueue(m_routing[inPort]);
	    m_routing[inPort]=0;
	 }
	 else if (m_istage_ctrl[inPort]==Consume)
	 {
#ifndef NO_TRAZA
            TPZString texto3 = txt_comp + " ISTAGE->CONS " + m_routing[inPort]->asString();
            TPZWRITE2LOG(texto3);
#endif 	
	    m_fifos_cons[inPort].enqueue(m_routing[inPort]);
	    m_routing[inPort]=0;
	 }
	 else
	 {
	    TPZString err;
            err.sprintf( "Wrong value of I-Stage control for Body flits");
            EXIT_PROGRAM(err);
	 }
      }
   }
   //****************************************************************************************************************
   //****************************************************************************************************************
   // PART 5: INJECTION
   //****************************************************************************************************************
   //****************************************************************************************************************

   if( m_routing[m_ports] !=0 )
   {
     if( m_routing[m_ports]->isHeader() || m_routing[m_ports]->isHeadTail() )
     {
        //ordered messages are routed through a mesh
	if( m_routing[m_ports]->isOrdered())
	{
	   int deltaX;
           int deltaY;
	   TPZPosition src = getOwnerRouter().getPosition();
	   TPZPosition dst = m_routing[m_ports]->destiny();
	   TPZPosition deltaPos = dst - src;
           deltaX = deltaPos.valueForCoordinate(TPZPosition::X);
           deltaY = deltaPos.valueForCoordinate(TPZPosition::Y);
           deltaX = (deltaX>=0) ? deltaX+1 : deltaX-1;
           deltaY = (deltaY>=0) ? deltaY+1 : deltaY-1;
           m_routing[m_ports]->setDelta(deltaX,0);
           m_routing[m_ports]->setDelta(deltaY,1);
	}
	TPZROUTINGTYPE direction= getInjectionDirection(m_routing[m_ports]);
	outPort= extractOutputPortNumber(direction);
	if (checkFlowControl(outPort, m_fifos_out_inj, 1, m_bufferSize)==true)
	{
#ifndef NO_TRAZA
           TPZString texto = txt_comp + " INJECTION " + m_routing[inPort]->asString();
	   texto += TPZString(" O-PORT: ") + TPZString(outPort);
           TPZWRITE2LOG(texto);
#endif
           m_fifos_out_inj[outPort].enqueue(m_routing[m_ports]);
	   m_injection_ctrl=outPort;
	   m_routing[m_ports]=0;
	}	
     }
     else
     {
        m_fifos_out_inj[m_injection_ctrl].enqueue(m_routing[m_ports]);
        m_routing[m_ports]=0;
     }
   }

   return true;
}
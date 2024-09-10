Boolean TPZConsumerFlowRespTimeSim::stateChange() {
	
	if (m_DataReceived) {
#ifndef NO_TRAZA
		//Log: lectura del buffer: flit a procesar
		TPZString time = getOwnerRouter().getCurrentTime();
		TPZString texto = getComponent().asString() + " BUFFER-READ. TIME = " + time
				+ ".  " + m_InputData->asString();
#endif
		if (m_State == Information && m_InputData->isHeader()) {
			TPZString err;
			err.sprintf(
					"%s : I detect a Header flit before previous message Tail flit: %s",
					(char*) getComponent().asString(),
					(char*) m_InputData->asString());
			EXIT_PROGRAM(err);
		}

		if (m_State == Header) {
			if (m_InputData->isHeadTail())
				m_State = Header;
			else
				m_State = Information;

			if (m_InputData->destiny() != getOwnerRouter().getPosition()
					&& !m_InputData->isMulticast()) {
				TPZString err;
				err.sprintf(ERR_TPZCOFLO_001, (char*) getComponent().asString(),
						(char*) m_InputData->asString());
				EXIT_PROGRAM(err);
			}

			if (m_InputData->isHeadTail()) {
#ifndef NO_TRAZA
				texto += "  PACKET RX";
#endif

				m_InputData->setDestiny(getOwnerRouter().getPosition());
				getOwnerRouter().onPacketReceived(m_InputData);
				uTIME lastTime = getOwnerRouter().getCurrentTime();
				((TPZSimulation*) (getComponent().getSimulation()))->setLastMessage(
						lastTime);

				//Emulacion de contencion en el acceso a L2. Cuando se finaliza el envio del mensaje
                                //(lleva el ultimo flit) se completa la peticion de acceso a memoria, por lo que
                                //hay que esperar a que la memoria "devuelva el dato" (no se envia nada al consumidor hasta
                                //que transcurran t_acceso(L2) ns
				//Cuando el mensaje es 1 solo flit: read request (no lleva dato).
				if (getOwnerRouter().getPosition().valueForCoordinate(
						TPZPosition::Z) == 1){
					m_wasReadNotWrite = true;
					m_stopCycles = 0;
#ifndef NO_TRAZA
					texto += "  (Memory read request)";
#endif
				}

			}

		}

		if (m_InputData->isTail()) {
#ifndef NO_TRAZA
			texto += "  PACKET RX";
#endif
			getOwnerRouter().onPacketReceived(m_InputData);
			m_State = Header;
			uTIME lastTime = getOwnerRouter().getCurrentTime();
			((TPZSimulation*) (getComponent().getSimulation()))->setLastMessage(
					lastTime);

			//Emulacion de contencion en el acceso a L2.
			//Cuando el mensaje es de mas de un flit: write request (lleva dato).
			if (getOwnerRouter().getPosition().valueForCoordinate(
					TPZPosition::Z) == 1){
				m_wasReadNotWrite = false;
				m_stopCycles = 0;
#ifndef NO_TRAZA
				texto += "  (Memory write request)";
#endif								
			}

		}

#ifndef NO_TRAZA
		TPZWRITE2LOG(texto);
#endif
	}
        //emulacion de contencion en acceso a L2, control de flujo
        //se envia una senal de stop emulando el tiempo de acceso a memoria,
        //provocando que los demas mensajes esperen a la finalizacion de la peticion
	if(getOwnerRouter().getPosition().valueForCoordinate(TPZPosition::Z)==1)
        {
                m_stopCycles++; 
                
                if(m_wasReadNotWrite){          
                   if (m_stopCycles < ((TPZConsumer&) getComponent()).getReadLatency()) m_readBuffer = false;
                   else m_readBuffer = true;
                } 
                else {
                   if (m_stopCycles < ((TPZConsumer&) getComponent()).getWriteLatency())m_readBuffer = false;
                   else m_readBuffer = true;
                }
        }
        else
        {
           m_readBuffer = true;
        }
        return true;

}
	virtual void Execute(SActivationInfo *pActInfo)
	{
		bool bResult = false;
		if (udpListener->IsWorking()) {
			if (udpListener->ReceiveLine() != -1) {
				
				int buttons = udpListener->GetTokenCount();
				
				for (int i=0;i<buttons;i++){
					string token = udpListener->GetToken(i);
					//CryLogAlways("%s",token);
					int id = udpListener->GetId(token);
					bool state = udpListener->TokenToBool(token);
					if(id>=12) {
						CryLogAlways("Index array out of bounds");
						break;
					}
					if(tab_state[id] != state){
						tab_state[id] = state;
						ActivateOutput(pActInfo,(id+1),state);
					}
				}
				
				bResult = true;
			}
		}
	
		//if (bResult) ActivateOutput(pActInfo, EOP_Received, true);
		return;
	}
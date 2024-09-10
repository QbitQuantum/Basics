	virtual void Execute(SActivationInfo *pActInfo)
	{
		bool bResult = false;
		if (udpListener->IsWorking()) {
			if (udpListener->ReceiveLine() != -1) {
				
				int analogs = udpListener->GetTokenCount();
				CryLogAlways("Nombre d'event %i",analogs);
				for(int i=0;i<analogs;i++){
					string token = udpListener->GetToken(i);
					float value = udpListener->TokenToFloat(token);
					
					int id = udpListener->GetId(token);
					if(id >= 10) {
						CryLogAlways("Error index out of bounds : token %s ",token);
						return;
					}

					if(current_values[id]!=value){
						current_values[id] = value;
						ActivateOutput(pActInfo,id+1,value);
					}
				}
				bResult = true;
			}
		}
		return;
	}
Bool_t KVSimReader_SMF_asym::ReadHeader(){

	KVString snom;
	Int_t res = ReadLineAndCheck(1," ");
	switch (res){
	case 0:
		return kFALSE; 
	case 1:
		snom.Form("%s",GetReadPar(0).Data());
		snom.ReplaceAll("evt_","");
		//Info("ReadHeader","lecture %d",snom.Atoi());
		nv->SetValue("event_number",snom.Atoi());
		
		break;
	default:
		return kFALSE;	
	}
	
	res = ReadLineAndCheck(1," ");
	switch (res){
	case 0:
		return kFALSE; 
	case 1:
		nv->SetValue("ndes",GetIntReadPar(0));
		ndes = 0;
		
		return kTRUE;
	default:
		return kFALSE;	
	}


}
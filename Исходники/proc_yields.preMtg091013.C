void ProcYields::Proc_hYW(){
	Info("Proc_hYW()", "");
		
	TDirectory* dirhYW = _fout->mkdir("hYW");
	TH1F* hYW[nVARSET];
	
	TDirectory* dirVarset=NULL;
	for(Int_t iVarset=0;iVarset<nVARSET;iVarset++){
		Info("Proc_hYW()","Varset = Varset%d", iVarset+1);
		dirVarset=dirhYW->mkdir(TString::Format("Varset%d",iVarset+1));
		dirVarset->cd();
		hYW[iVarset] = new TH1F("hYW","hYW", _user.nWbins, _user.Wmin, _user.Wmax);
		hYW[iVarset]->SetXTitle("W[GeV]");
		
		//!Loop over Q2W dirs, get h5Ds and their yields
		TIter nextkey(_fout->GetListOfKeys());
		TKey *key;
		while (key = (TKey*)nextkey()) {
			TString Q2Wdirname = key->GetName();
			if(Q2Wdirname.EqualTo("hYW_Dir") || Q2Wdirname.EqualTo("hYW"))continue;
			Info("Proc_hYW()","Q2Wdir = %s", Q2Wdirname.Data());
			TString wrange = Q2Wdirname.Tokenize("_")->At(1)->GetName();
			TString wlow = wrange.Tokenize(",")->At(0)->GetName();
			wlow.Remove(0,1); //remove "["
			//Float_t w = wlow.Atof();
			Double_t w = wlow.Atof();
									
			sprintf(_hname, "%s/hY5D/Varset%d/hY5D_FULL", Q2Wdirname.Data(),iVarset+1);
			THnSparse* hY5D_FULL = (THnSparse*)_fout->Get(_hname);
			if (hY5D_FULL == NULL) cout <<"could not get h5D" << endl;
			//Float_t yield = getIntegral(hY5D_FULL);
			Double_t yield = getIntegral(hY5D_FULL);
			//hYW[iVarset]->Fill(w, yield);
			hYW[iVarset]->SetBinContent(hYW[iVarset]->FindBin(w+_intrinsic.Wbinw), yield);
			Info("Proc_hYW()","W = %f, bin# = %d, yield = %f\n", w, hYW[iVarset]->FindBin(w+_intrinsic.Wbinw), yield);
		}
	}
	Info("Proc_hYW()", "done\n");
}
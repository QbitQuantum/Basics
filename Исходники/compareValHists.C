void cmpLRD(TFile* f1, TFile* f2, const char* dName, const char* patt = 0, unsigned int logmod=0, unsigned int dOpt=1){
  //  std::cout<<"cmpLRD In "<< dName<<std::endl;
  TDirectory* td = gROOT->GetDirectory(dName);
  if (td){
    TList* tkl = td->GetListOfKeys();
    unsigned int tklSize = tkl->GetEntries();
    //    std::cout<<"\t size "<<tklSize<<std::endl;
    for (unsigned int iK=0; iK< tklSize; ++iK){
      //      std::cout<<"at "<<iK<<"\t " <<tkl->At(iK)->GetName()<<std::endl;
      if (TClass(((TKey*)tkl->At(iK))->GetClassName()).InheritsFrom("TDirectory")){
	TDirectory* tdc = (TDirectory*)((TKey*)tkl->At(iK))->ReadObj();
	if (tdc ==0) continue;
	TString tdcPFull(tdc->GetPath());
	TString pRel(tdcPFull.Tokenize(":")->At(1)->GetName());
	//	std::cout<<tdcPFull.Data()<<std::endl;
	
	//now execute compare 
	//	if(pRel.Index("/SiStrip/")>=0) continue; //this takes a huge time in alcareco and is irrelevant
	///DQMData/Run 1/Btag
	if (patt==0 || (patt!=0 && pRel.Index(patt)>=0)){
	  //	  std::cout<<"Comparing in " <<pRel.Data()<<std::endl;
	  compareInDir(f1, f2, pRel.Data(),logmod,dOpt);
	}
	cmpLRD(f1, f2, tdcPFull.Data(), patt,logmod,dOpt);
      }
    }
  }
}
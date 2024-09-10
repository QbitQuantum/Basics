void KVGANILDataReader::SetUserTree(TTree* T, Option_t* opt)
{
   // To fill a TTree with the data in the current file, create a TTree:
   //    TFile* file = new TFile("run1.root","recreate");
   //    TTree* T = new TTree("Run1", "Raw data for Run1");
   // and then call this method: SetUserTree(T)
   // If you read all events of the file, the TTree will be automatically filled
   // with data :
   //    while( runfile->GetNextEvent() ) ;
   //
   // Two different TTree structures are available, depending on the option string:
   //
   //    opt = "arrays": [default]
   //
   // The TTree will have the following structure:
   //
   //    *Br    0 :NbParFired : NbParFired/I    = number of fired parameters in event
   //    *............................................................................*
   //    *Br    1 :ParNum    : ParNum[NbParFired]/i   = array of indices of fired parameters
   //    *............................................................................*
   //    *Br    2 :ParVal    : ParVal[NbParFired]/s   = array of values of fired parameters
   //
   // This structure is the fastest to fill and produces the smallest file sizes.
   // In order to be able to directly access the parameters as if option "leaves" were used
   // (i.e. one branch/leaf for each parameter), we add two aliases for each parameter to
   // the tree:
   //        PARNAME           = value of parameter if present in event
   //        PARNAME_M      = number of times parameter appears in event
   // Assuming that each parameter only appears at most once in each event, i.e. PARNAME_M=0 or 1,
   // then
   //    root[0] T->Draw("PARNAME", "PARNAME_M")
   // will histogram the value of PARNAME for each event in which it is present.
   // (if the selection condition "PARNAME_M" is not used, the histogram will also be filled with a 0
   // for each event in which PARNAME does not appear).
   //          N.B. the PARNAME alias is in fact the sum of the values of PARNAME in each event.
   //          If PARNAME_M>1 in some events, it is not the individual values but their sum which will
   //          be histogrammed in this case.
   //
   // Thus, if the data file has parameters called "PAR_1" and "PAR_2",
   // the following command will work
   //
   //    root[0]  T->Draw("PAR_1:PAR_2", "PAR_1_M&&PAR_2_M", "col")
   //
   // even though no branches "PAR_1" or "PAR_2" exist.
   //
   //
   //
   //    opt = "leaves":
   //
   // The TTree will have a branch/leaf for each parameter. This option is slower and produces
   // larger files.
   //
   // If the option string contains both "arrays" and "leaves", then both structures will be used
   // (in this case there is a high redundancy, as each parameter is stored twice).
   //
   // The full list of parameters is stored in a TObjArray in the list returned by TTree::GetUserInfo().
   // Each parameter is represented by a TNamed object.
   // In order to retrieve the name of the parameter with index 674 (e.g. taken from branch ParNum),
   // do:
   //     TObjArray* parlist = (TObjArray*) T->GetUserInfo()->FindObject("ParameterList");
   //     cout << "Par 674 name = " << (*parlist)[674]->GetName() << endl;
   //
   //
   //  Automatic creation & filling of Scalers TTree
   //
   // give an option string containing "scalers", i.e. "leaves,scalers", or "ARRAYS+SCALERS", etc.
   // a TTree with name 'Scalers' will be created, all scaler buffers will be written in it.


   TString option = opt;
   option.ToUpper();
   make_arrays = option.Contains("ARRAYS");
   make_leaves = option.Contains("LEAVES");
   Bool_t make_scalers = option.Contains("SCALERS");
   if(make_scalers){
   	fGanilData->SetScalerBuffersManagement(GTGanilData::kAutoWriteScaler);
   }

   fUserTree = T;
   if( make_arrays ){
      Int_t maxParFired = GetRawDataParameters()->GetEntries();
      ParVal = new UShort_t[maxParFired];
      ParNum = new UInt_t[maxParFired];
      fUserTree->Branch("NbParFired", &NbParFired, "NbParFired/I");
      fUserTree->Branch("ParNum", ParNum, "ParNum[NbParFired]/i");
      fUserTree->Branch("ParVal", ParVal, "ParVal[NbParFired]/s");
   }
   if( make_leaves ){
      TIter next_rawpar( GetRawDataParameters() );
      KVACQParam* acqpar;
      while( (acqpar = (KVACQParam*)next_rawpar()) ){
         TString leaf;
         leaf.Form("%s/S", acqpar->GetName());
         // for parameters with <=8 bits only use 1 byte for storage
         if(acqpar->GetNbBits()<=8) leaf += "1";
         fUserTree->Branch( acqpar->GetName(), *(acqpar->ConnectData()), leaf.Data() );
      }
   }

#if ROOT_VERSION_CODE > ROOT_VERSION(5,25,4)
#if ROOT_VERSION_CODE < ROOT_VERSION(5,26,1)
   // The TTree::OptimizeBaskets mechanism is disabled, as for ROOT versions < 5.26/00b
   // this lead to a memory leak
   fUserTree->SetAutoFlush(0);
#endif
#endif

   // add list of parameter names in fUserTree->GetUserInfos()
   // and if option="arrays" add aliases for each parameter & its multiplicity
	
	// TObjArray has to be as big as the largest parameter number in the list
	// of raw data parameters. So first loop over parameters to find max param number.
    UInt_t maxpar = 0;
   TIter next(GetRawDataParameters());
   KVACQParam* par;
	while( (par=(KVACQParam*)next()) ) if (par->GetNumber()>maxpar) maxpar=par->GetNumber();
	
   TObjArray *parlist = new TObjArray(maxpar,1);
   parlist->SetName("ParameterList");
	
	next.Reset();
   while( (par = (KVACQParam*)next()) ){
      parlist->AddAt( new TNamed( par->GetName(), Form("index=%d",par->GetNumber()) ), par->GetNumber() );
      if( make_arrays ){
          fUserTree->SetAlias( par->GetName(), Form("Sum$((ParNum==%d)*ParVal)", par->GetNumber() ) );
          fUserTree->SetAlias( Form("%s_M", par->GetName()), Form("Sum$(ParNum==%d)", par->GetNumber() ) );
      }
   }
   fUserTree->GetUserInfo()->Add(parlist);
}
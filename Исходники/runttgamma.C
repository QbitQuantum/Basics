void runttgamma(TString sample="all", TString ExtraOpts= "", int workers=8)
{

  //TProof *proof = getProof("lite://",nwrks);
  TString proofOpt(Form("workers=%i",workers));
  //TProof *proof = TProof::Open(proofOpt);
  //if (!proof) {
  //  Printf("runProof: could not start/attach a PROOF session");
  //  return;
  //}

  //proof->SetLogLevel(2); // verbose

  TChain *chain = new TChain("ggNtuplizer/EventTree");
  StrVecMap::iterator ite;//
  bool foundSample = false;
  for ( ite = vsamples.begin(); ite != vsamples.end(); ++ite) {//
    
    std::string name(sample.Data());
    std::string tmpname = (*ite).first;
    if ( name != "all" && name != tmpname ) continue;
    foundSample = true;
    if ( name == "all" ) name = tmpname;
    StrVector location = vsamples[name];
    cout<< "Input sample: "<< name << endl;
    //StrVecMap::iterator ite;
    //for (ite = location.begin(); ite != location.end(); ++ite) {
    for ( size_t i=0; i < location.size(); ++i ) {
    
      //chain->Add(location.c_str());
      chain->Add( location[i].c_str() );
    }
    cout << "List of files:" << endl;
    chain->ls();
    cout << endl;
    //chain->SetProof(); // to run in PROOF mode
    TString opts(Form("sample=%s",name.c_str()));
    if (ExtraOpts != "" ) opts = ExtraOpts + " " + opts;

    ttgamma3 *myselector = new ttgamma3();

    //chain->Process("ttgamma3.C",opts.Data() );
    chain->Process(myselector, opts.Data() );
    cout << "Process: ttgamma.C done" << endl;

  }
  // logs
  
  //TList *logList = proof->GetManager()->GetSessionLogs()->GetListOfLogs();
  //for (int i=1; i< logList->GetSize(); ++i)
  //  {
  //    TProffLogElem *logElem = ( TProofLogElem* ) logList->At( i );
  //    macro = logElem->GetMacro();
  //    macro->SaveSource("data_muons_"+TString(Form("%i",i))+".stdout");
  //  }
  

  //chain->SetProof(0);
  //chain->Delete();
  //delete chain;
  //proof->ClearInput();
  //proof->ClearData();
  //proof->ClearInputData();
  //delete proof;
  if ( foundSample )
    cout << "runttgamma done"<<endl;
  else
    cout << "Error: No sample found with name: " << sample.Data() << endl;
}
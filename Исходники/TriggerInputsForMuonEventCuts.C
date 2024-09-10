void TriggerInputsForMuonEventCuts ( TString runListFilename, TString selectedInputs="", TString defaultStorage = "raw://" )
{
  AliCDBManager::Instance()->SetDefaultStorage(defaultStorage.Data());
  TObjArray inputsList;
  inputsList.SetOwner();
  
  TObjArray* selectedInputsList = selectedInputs.Tokenize(",");

  // Read input run list
  ifstream inFile(runListFilename.Data());
  TString srun = "";
  if ( inFile.is_open() ) {
    while ( ! inFile.eof() ) {
      srun.ReadLine(inFile,kFALSE);
      if ( ! srun.IsDigit() ) continue;
      
      // For each run, read trigger inputs from OCDB
      Int_t runNumber = srun.Atoi();
      AliCDBManager::Instance()->SetRun(runNumber);
      
      // Get trigger class configuration
      AliCDBEntry* entry = AliCDBManager::Instance()->Get("GRP/CTP/Config");
      if ( ! entry ) continue;
      
      THashList* runInputs = new THashList();
      runInputs->SetOwner();
      runInputs->SetUniqueID((UInt_t)runNumber);
      AliTriggerConfiguration* trigConf = (AliTriggerConfiguration*)entry->GetObject();
      const TObjArray& trigInputsArray = trigConf->GetInputs();
      AliTriggerInput* trigInput = 0x0;
      TIter next(&trigInputsArray);
      while ( ( trigInput = static_cast<AliTriggerInput*>(next()) ) ) {
        if ( selectedInputsList->GetEntriesFast() > 0 && ! selectedInputsList->FindObject(trigInput->GetName()) ) continue;
        Int_t inputId = (Int_t)TMath::Log2(trigInput->GetMask());
        TObjString* currInput = new TObjString(trigInput->GetName());
        currInput->SetUniqueID(inputId);
        runInputs->Add(currInput);
      }
      inputsList.Add(runInputs);
    }
    inFile.close();
  }
  delete selectedInputsList;
  
  // Loop on the trigger inputs
  // and group runs with an equal list of inputs
  Int_t nentries = inputsList.GetEntries();
  TArrayI checkMask(nentries);
  checkMask.Reset(1);
  for ( Int_t irun=0; irun<nentries; irun++ ) {
    if ( checkMask[irun] == 0 ) continue;
    THashList* currList = static_cast<THashList*>(inputsList.At(irun));
    TString runRange = Form("Run range: %u", currList->GetUniqueID());
    for ( Int_t jrun=irun+1; jrun<nentries; jrun++ ) {
      if ( checkMask[jrun] == 0 ) continue;
      THashList* checkList = static_cast<THashList*>(inputsList.At(jrun));
      Bool_t isDifferent = kFALSE;
      for ( Int_t itrig=0; itrig<currList->GetEntries(); itrig++ ) {
        TObjString* currInput = static_cast<TObjString*>(currList->At(itrig));
        TObject* checkInput = checkList->FindObject(currInput->GetName());
        if ( ! checkInput || checkInput->GetUniqueID() != currInput->GetUniqueID() ) {
          isDifferent = kTRUE;
          break;
        }
      } // loop on trigger inputs
      if ( isDifferent ) continue;
      checkMask[jrun] = 0;
      runRange += Form(",%u", checkList->GetUniqueID());
    } // loop on runs
    
    TString outString = "\nSetTrigInputsMap(\"";
    for ( Int_t itrig=0; itrig<currList->GetEntries(); itrig++ ) {
      TObjString* currInput = static_cast<TObjString*>(currList->At(itrig));
      outString += Form("%s:%u,",currInput->GetString().Data(), currInput->GetUniqueID());
    }
    outString.Append("\");\n");
    outString.ReplaceAll(",\"","\"");
    outString += runRange;
    printf("%s\n", outString.Data());
  } // loop on runs
}
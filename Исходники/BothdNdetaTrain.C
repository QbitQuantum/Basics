  /** 
   * Create our tasks.  This uses the interpreter to make the object.
   * 
   * @param mgr 
   */
  void CoupleTrackletCar(AliAnalysisManager* mgr)
  {
    AliAnalysisManager::SetCommonFileName("tracklet_dndeta.root");
    TString fwd(gSystem->Getenv("ANA_SRC"));
    if (fwd.IsNull()) fwd = "$ALICE_PHYSICS/PWGLF/FORWARD/analysis2";
    gROOT->SetMacroPath(Form("%s:%s/dndeta/tracklets3",
			     gROOT->GetMacroPath(), fwd.Data()));
    gSystem->AddIncludePath(Form("-I%s/dndeta/tracklets3", fwd.Data()));
    
    Info("CreateTasks", "Loading code");
    fRailway->LoadSource("FixPaths.C");
    fRailway->LoadSource("AliAODSimpleHeader.C");
    fRailway->LoadSource("AliAODTracklet.C");
    fRailway->LoadSource("AliTrackletWeights.C");
    fRailway->LoadSource("AliTrackletAODUtils.C");
    fRailway->LoadSource("AliTrackletAODdNdeta.C");

    // --- Create the task using interpreter -------------------------
    Bool_t   mc = fOptions.Has("mc");
    if (!mc) mc = fRailway->IsMC();     
    Long_t ret  =
      gROOT->ProcessLine(Form("AliTrackletAODdNdeta::Create(%d,\"%s\")",mc,
			      fOptions.AsString("reweigh")));
    AliAnalysisTaskSE* task = reinterpret_cast<AliAnalysisTaskSE*>(ret);
    if (!task) return;
    
    // --- Figure out the trigger options ----------------------------
    TString trg = fOptions.Get("trig"); trg.ToUpper();
    UInt_t  sel = AliVEvent::kINT7;
    UInt_t  mb  = AliVEvent::kINT1; // AliVEvent::kMB;
    if      (trg.EqualTo("MB"))      sel = mb;
    else if (trg.EqualTo("MBOR"))    sel = mb;
    else if (trg.EqualTo("INEL"))    sel = mb;
    else if (trg.EqualTo("INELGT0")) sel = mb;
    else if (trg.EqualTo("V0AND"))   sel = AliVEvent::kINT7;
    else if (trg.EqualTo("NSD"))     sel = AliVEvent::kINT7;
    else if (trg.EqualTo("V0OR"))    sel = AliVEvent::kCINT5;
    else if (trg.EqualTo("ANY"))     sel = AliVEvent::kAny;
    task->SelectCollisionCandidates(sel);
    Int_t minTrk = trg.EqualTo("INELGT0") ? 1 : 0;

    // --- Figure out calculation mode -------------------------------
    TString calc = fOptions.Get("reweigh-calc"); calc.ToUpper();
    UChar_t mcal = 0;
    if      (calc.BeginsWith("PROD")) mcal = 0;
    else if (calc.BeginsWith("SQ"))   mcal = 1;
    else if (calc.BeginsWith("SUM"))  mcal = 2;
    else if (calc.BeginsWith("AV"))   mcal = 3;
    
    // --- Set various options on task -------------------------------
    const char* defCent = "0-5-10-20-30-40-50-60-70-80-90";
    FromOption(task, "CentralityMethod","cent", 	    "V0M");
    FromOption(task, "CentralityAxis",  "cent-bins",        defCent);
    FromOption(task, "EtaAxis",         "eta-bins",         "r16:2");
    FromOption(task, "IPzAxis",         "ipz-bins",         "u15");
    FromOption(task, "DeltaCut",	"delta-cut",	    1.5);
    FromOption(task, "TailDelta",	"tail-delta",	    5.);
    FromOption(task, "TailMaximum",	"tail-max",	    -1);
    FromOption(task, "MaxDelta",	"max-delta",	    25.);
    FromOption(task, "DPhiShift",	"dphi-shift",	    0.0045);
    FromOption(task, "ShiftedDPhiCut",	"shifted-dphi-cut",-1.);
    FromOption(task, "AbsMinCent",      "abs-min-cent",    -1.);
    FromOption(task, "WeightMask",      "reweigh-mask",     0xFF);
    FromOption(task, "WeightVeto",      "reweigh-veto",     0x0);
    SetOnTask (task, "WeightCalc",                          mcal);
    FromOption(task, "WeightInverse",   "reweigh-inv",      false);
    FromOption(task, "TriggerEff",      "trigEff",          0.);
    SetOnTask (task, "MinEta1",                             minTrk);
    // if (mc && we) {
    //   TUrl wurl(fOptions.AsString("reweight"));
    //   TFile* wfile = TFile::Open(wurl.GetFile());
    //   if (!wfile) {
    // 	Warning("CreateTasks", "Failed to open weights file: %s",
    // 		wurl.GetUrl());
    // 	return;
    //   }
    //   TString wnam(wurl.GetAnchor());
    //   if (wnam.IsNull()) wnam = "weights";
    //   TObject* wobj = wfile->Get(wnam);
    //   if (!wobj) {
    // 	Warning("CreateTasks", "Failed to get weights %s from file %s",
    // 		wnam.Data(), wfile->GetName());
    // 	return;
    //   }
    //   if (!wobj->IsA()->InheritsFrom("AliTrackletWeights")) {
    // 	Warning("CreateTasks", "Object %s from file %s not an "
    // 		"AliTrackletWeights but a %s",
    // 		wnam.Data(), wfile->GetName(), wobj->ClassName());
    // 	return;
    //   }
    //   SetOnTaskGeneric(task, "Weights",
    // 		       Form("((AliTrackletWeights*)%p)", wobj));
    // }
    Printf("Print the generated task");
    task->Print("");    
  }
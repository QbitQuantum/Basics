  /** 
   * Create our tasks.  This uses the interpreter to make the object.
   * 
   * @param mgr 
   */
  void CreateTasks(AliAnalysisManager* mgr)
  {
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
    if      (trg.EqualTo("MB"))    sel = AliVEvent::kMB;
    else if (trg.EqualTo("V0AND")) sel = AliVEvent::kINT7;
    else if (trg.EqualTo("V0OR"))  sel = AliVEvent::kCINT5;
    else if (trg.EqualTo("ANY"))   sel = AliVEvent::kAny;
    task->SelectCollisionCandidates(sel);

    // --- Figure out calculation mode -------------------------------
    TString calc = fOptions.Get("reweigh-calc"); calc.ToUpper();
    UChar_t mcal = 0;
    if      (calc.BeginsWith("PROD")) mcal = 0;
    else if (calc.BeginsWith("SQ"))   mcal = 1;
    else if (calc.BeginsWith("SUM"))  mcal = 2;
    else if (calc.BeginsWith("AV"))   mcal = 3;
    
    // --- Set various options on task -------------------------------
    const char* defCent = DefaultCentBins();
    FromOption(task, "CentralityMethod","cent", 	    "V0M");
    FromOption(task, "CentralityAxis",  "cent-bins",        defCent);
    FromOption(task, "AbsMinCent",      "abs-min-cent",    -1.);
    FromOption(task, "MaxNTracklet",    "max-ntracklet",    6000.);
    FromOption(task, "EtaAxis",         "eta-bins",         "r16:2");
    FromOption(task, "IPzAxis",         "ipz-bins",         "u15");
    FromOption(task, "DeltaCut",	"delta-cut",	    1.5);
    FromOption(task, "TailDelta",	"tail-delta",	    5.);
    FromOption(task, "TailMaximum",	"tail-max",	    -1);
    FromOption(task, "MaxDelta",	"max-delta",	    25.);
    FromOption(task, "DPhiShift",	"dphi-shift",	    0.0045);
    FromOption(task, "ShiftedDPhiCut",	"shifted-dphi-cut",-1.);
    FromOption(task, "WeightMask",      "reweigh-mask",     0xFF);
    FromOption(task, "WeightVeto",      "reweigh-veto",     0x0);
    SetOnTask (task, "WeightCalc",                          mcal);
    FromOption(task, "WeightInverse",   "reweigh-inv",      false);
    task->Print("");    
  }
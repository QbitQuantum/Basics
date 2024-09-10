  /** 
   * Analyse the reweighting option string and set options on task
   * appropriately.  The string is a comma or space separated list of
   * what to reweigh and how to do it. 
   *
   * What to reweigh can be specfied using one or more of the strings 
   *
   * - pt  Reweight in pT 
   * - pid Reweight particle abundance of pi, K, proton 
   * - str Reweight particles from strange weak decays 
   *
   * How to reweigh can be specifed as 
   *
   * - + or up   Increase weights (for pt < 0.05 by +30%)
   * - - or down Decrease weights (for pt < 0.05 by -30%)
   * - If none of these are given, then the weights are used as is. 
   * 
   * If pid rewighting is done and one of up or down are given, then
   * one can specify which particle type to reweigh
   *
   * - pi or pion    Reweight (up or down) pions 
   * - K  or kaon    Reweight (up or down) kaons
   * - p  or proton  Reweight (up or down) protons 
   *
   * Note, if PID, with explicit selection of pions, and strangeness
   * reweighting are specified, then the up/down flag applies to both
   * PID reweighting and the strangeness reweighting
   * 
   * @param task The task to modify 
   */
  void SetupReweighting(AliAnalysisTaskSE* task)
  {
    TString sel = fOptions.AsString("reweight");
    sel.ToLower();
    if (sel.IsNull() || sel.BeginsWith("no"))
      return;

    TList       files;
    Int_t       what = 0;
    Int_t       opt  = 0;
    TObjArray*  tokens = sel.Tokenize(", ");
    TIter       next(tokens);
    TObjString* ostr;
    // First find what should be done 
    while ((ostr = static_cast<TObjString*>(next()))) {
      const TString& token = ostr->String();
      
      if      (token.EqualTo("pt"))   {
	what |= 0x1;
	files.Add(new TObjString("REWEIGHTpt.root"));
	Printf("Will reweigh in pT");
      }
      else if (token.EqualTo("pid")) {
	what |= 0x2;
	Printf("Will reweigh particle species");
      }
      else if (token.EqualTo("str"))  {
	what |= 0x4;
	Printf("Will reweight particles from strange weak decays");
      }
    }
    if (what == 0x0) return;
    
    // Now figure out how to do it 
    next.Reset();
    TString part;
    while ((ostr = static_cast<TObjString*>(next()))) {
      const TString& token = ostr->String();
      Int_t aOpt = TMath::Abs(opt);
      if      (token.EqualTo("up")   || token.EqualTo("+")) 
	opt = (aOpt==0 ? +1 : +aOpt); 
      else if (token.EqualTo("down") || token.EqualTo("-"))
	opt = (aOpt==0 ? -1 : -aOpt);
      else if (token.EqualTo("pi")   || token.EqualTo("pion")){
	  opt = 1; part = "pi";
      }
      else if (token.EqualTo("k")    || token.EqualTo("kaon")) {
	opt = 2; part = "ka";
      }
      else if (token.EqualTo("p")    || token.EqualTo("proton")) {	  
	opt = 3; part = "pr";
      }
    }
    if (opt != 0)
      Printf("Will reweigh %s (%c30%% for pT<0.05)",
	     opt < 0 ? "down" : "up", opt < 0 ? '-' : '+');
    if (what & 0x2) {
      if (!part.IsNull()) {
	Printf("Will reweight %s in particular", part.Data());
	part.Prepend("_");
	part.Append(opt < 0 ? "-" : "+");
      }
      files.Add(new TObjString(Form("REWEIGHTpid%s.root", part.Data())));
    }
    if (what & 0x4)
      files.Add(new TObjString(Form("REWEIGHTstr%s.root",
				    opt == -1 ? "-" :
				    opt == +1 ? "+" : "")));
    delete tokens;

    Printf("Setting reweighing flag=0x%x with option=%d", what, opt);
    SetOnTask(task, "ReweightStack", what);
    SetOnTask(task, "ReweightFlag",  opt);

    TIter nextF(&files);
    while ((ostr = static_cast<TObjString*>(nextF()))) {
      Printf("Loading reweighting file %s", ostr->GetName());
      fRailway->LoadAux(ostr->GetName());
    }
  }
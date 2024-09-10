 //_______________________________________________________________________________________________
 //
 // Initialize plugin with all its common values
 //
 Bool_t CreatePlugin()
 {
    // create object
    plugin = new AliAnalysisAlien;
    
    // framework version
    plugin->SetROOTVersion(rootVersion.Data());
    plugin->SetAliROOTVersion(aliVersion.Data());
    
    // additional libraries/includes
    if (addLibs.Length() > 0) plugin->SetAdditionalLibs(addLibs.Data());
    if (addIncludes.Length() > 0) plugin->AddIncludePath(addIncludes.Data());
    
    // runtime tasks
    if (addTaskRuntime.Length() > 0) {
       TObjArray *list = addTaskRuntime.Tokenize(" ");
       TObjArrayIter next(list);
       TObjString *os = 0x0;
       TString sources("");
       while ( (os = (TObjString*)next()) ) {
          const char *taskName = os->GetString().Data();
          addLibs.Append(Form("%s.h %s.cxx", taskName, taskName));
          sources.Append(Form("%s.cxx", taskName));
       }
       plugin->SetAnalysisSource(sources.Data());
    }
    
    // specific setups
    if (targetAlien) {
       ::Info("SetupPlugin::CreatePlugin()", "Setting up for ALIEN");
       return SetupForAlien();
    } else {
       ::Info("SetupPlugin::CreatePlugin()", "Setting up for PROOF");
       return SetupForProof();
    }
 }
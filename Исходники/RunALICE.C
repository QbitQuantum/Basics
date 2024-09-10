Bool_t RunALICE(TString anSrc = "grid",
                TString anMode = "terminate",
                TString input="aod" /*or "esd"*/,
                TString inputMC="" /*or "mc"*/,
                Long64_t nEvents = 1e10,
                Long64_t nSkip = 0,
                TString dsName="",
                TString alirsnliteManagers ="AddAMRsn",
                Bool_t useMultiHandler=kTRUE,
                TString alirsnlitesrc ="$ALICE_ROOT",
                TString alirsnlitetasks =""
               ) {

   // some init work
   anSrc.ToLower(); anMode.ToLower(); input.ToLower(); inputMC.ToLower();

   // loads libs and setup include paths
   if (LoadLibsBase(alirsnlitesrc)) return kFALSE;

   // reset manager if already exists
   AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
   if (mgr) delete mgr;
   mgr = new AliAnalysisManager("AliRsnLiteAM","AliRsnLite Analysis Manager");

   Bool_t useAODOut = kFALSE;
   CreateInputHandlers(input,inputMC,useAODOut,useMultiHandler);

   // add default grid handler
   gROOT->LoadMacro("SetupAnalysisPlugin.C");
   AliAnalysisGrid *analysisPlugin = SetupAnalysisPlugin(anMode.Data());
   if (!analysisPlugin) { Printf("Error : analysisPlugin is null !!!"); return kFALSE; }
   mgr->SetGridHandler(analysisPlugin);
   if (!dsName.IsNull()) {
      if (!anSrc.CompareTo("proof") && !anMode.CompareTo("full")) {
         analysisPlugin->SetProofDataSet(dsName.Data());
         Printf(Form("Using DataSet %s ...",dsName.Data()));
      } else {
         analysisPlugin->SetFileForTestMode(dsName.Data());
         Printf(Form("Using Test file %s ...",dsName.Data()));
      }
   }

   TList *listManagers = CreateListOfManagersFromDir(alirsnliteManagers,alirsnlitetasks);
   if (!listManagers) { Printf("Error : CreateListOfManagersFromDir failed !!!"); return kFALSE;}

   // adds all tasks
   if (!AddAllManagers(listManagers, anSrc, anMode,input,inputMC)) { Printf("Error : AddAllManagers failed !!!"); return kFALSE;}

   gSystem->ListLibraries("ls");

   TStopwatch timer;
   timer.Start();
   // runs analysis
   if (!RunAnalysisManager(anSrc, anMode.Data(), nEvents, nSkip)) { Printf("Error : RunAnalysisManager failed !!!"); return kFALSE;}

   timer.Stop();
   timer.Print();
   Printf("Working directory is %s ...", gSystem->WorkingDirectory());
   Printf("Done OK");
   return kTRUE;

}
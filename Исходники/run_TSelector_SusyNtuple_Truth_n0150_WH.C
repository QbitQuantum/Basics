void run_TSelector_SusyNtuple_Truth_n0150_WH(TString SysUncertType, TString InputPath) {

//  TString options = TString(""); //TString(tag.c_str()) ;
// //     TString outputfile = "test.root";
//     string richtigerString = InputPath;
// //     int Position = richtigerString.find("mc12_8TeV.");
// //     outputfile = "histos_ZTauTau_" +  richtigerString.substr(Position+10,6)  + "_proof.root";
//     
//     int Position = -1;
//     Position = richtigerString.find("45_bg");
//     if (Position>0){
//       outputfile = "histos_test_" +  richtigerString.substr(Position+6,2)  + ".root";
//     }
//     else{
//       Position = richtigerString.find("45_signal");
//       if (Position>0){
//       outputfile = "histos_test_" +  richtigerString.substr(Position+3,2)  + ".root";
//       }
//     }
//     if(outputfile == ""){
//       cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
//       cout << "EMPTY OUPTPUTFILE STRING" << endl;
//       cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
//       abort();
//     }
//     cout << "outputfile= " << outputfile << endl;
    
      cout<<"Have you set up RootCore via  \"source RootCore/scripts/setup.sh\" ?"<<endl;  

      gSystem->Setenv("ROOTCOREDIR", "/data/etp3/jwittkow/analysis_SUSYTools_03_04/RootCore");
      gSystem->SetIncludePath("-I$ROOTCOREDIR/include/");

      gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+"); 

      TString selectorName = "TSelector_SusyNtuple_Truth"; // !!! enter the name of your Selector (without _C.so)

      TChain *ch;
      
      ch = new TChain("susyNt");

      TString processLine = ".L " + selectorName + ".cpp++g";
      TString execLine;

      gROOT->ProcessLine(processLine); // need to add this, or PoD at LRZ will not be able to load the .so
      gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");
      ch->Add(InputPath);
//       ch->Add("/data/etp6/jwittkow/SusyNtuples_n0145_bg_new/WZ_SherpaVVtotautauqq/user.sfarrell.mc12_8TeV.157816.Sherpa_CT10_VVtotautauqq.SusyNt.e1515_s1499_s1504_r3658_r3549_p1512_n0145.130708082025/*");



//       ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0145_data/Egamma/user.sfarrell.group.phys-susy.data12_8TeV.periodA.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0145.130708161315/user.sfarrell.116519._00003.susyNt.root");
//       ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0145_data/Egamma/user.sfarrell.group.phys-susy.data12_8TeV.periodA.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0145.130708161315/*");
// ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0145_data/Egamma/user.sfarrell.group.phys-susy.data12_8TeV.periodA.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0145.130708161341/*");  
// ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0145_data/Egamma/user.sfarrell.group.phys-susy.data12_8TeV.periodA.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0145.130708161402/*");
// ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0145_data/Egamma/user.sfarrell.group.phys-susy.data12_8TeV.periodA.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0145.130708161438/*");
      
//       ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/WH/user.gerbaudo.mc12_8TeV.177501.Herwigpp_sM_wA_noslep_notauhad_WH_2Lep_1.SusyNt.e2149_s1581_s1586_r3658_r3549_p1512_n0150.140109072637/*");
//       ch->Add("/data/etp6/jwittkow/user.gerbaudo.mc12_8TeV.126893.Sherpa_CT10_lllnu_WZ.SusyNt.e1434_s1499_s1504_r3658_r3549_p1512_n0145dev4.131220015824/*");
      
//       ch->Add("/data/etp6/jwittkow/SusyNtuples_n0145_bg_new/ttbar105200/*");

//             ch->Add("/data/etp6/jwittkow/SusyNtuples_n0145_signal_samples/user.gerbaudo.mc12_8TeV.177503.Herwigpp_sM_wA_noslep_notauhad_WH_2Lep_3.SusyNt.e2149_s1581_s1586_r3658_r3549_p1512_n0145.130806161345/user.gerbaudo.023459._00001.susyNt.root");
      
      

	    


      Long64_t nEntries = ch->GetEntries();
      ch->ls();

      cout << "all entries: " << nEntries << endl;


      TSelector_SusyNtuple_Truth* SusyNtupleObject = new TSelector_SusyNtuple_Truth();
//       SusyNtupleObject->buildSumwMap(ch);
//       TString options="NtSys_NOM";
      ch->Process(SusyNtupleObject,SysUncertType);
      delete SusyNtupleObject;
      
      if (ch) {delete ch; ch=0;}

  abort();
  }
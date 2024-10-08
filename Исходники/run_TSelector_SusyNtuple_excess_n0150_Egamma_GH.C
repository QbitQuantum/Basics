void run_TSelector_SusyNtuple_excess_n0150_Egamma_GH() {

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

      gSystem->Setenv("ROOTCOREDIR", "/data/etp3/jwittkow/analysis_SUSYTools_03_04_SusyNt_01_16/RootCore");
      gSystem->SetIncludePath("-I$ROOTCOREDIR/include/");

      gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+"); 

      TString selectorName = "TSelector_SusyNtuple_excess"; // !!! enter the name of your Selector (without _C.so)

      TChain *ch;
      
      ch = new TChain("susyNt");

      TString processLine = ".L " + selectorName + ".cpp++g";
      TString execLine;

      gROOT->ProcessLine(processLine); // need to add this, or PoD at LRZ will not be able to load the .so
      gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");
//       ch->Add(InputPath);
//       ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/WH/user.gerbaudo.mc12_8TeV.177501.Herwigpp_sM_wA_noslep_notauhad_WH_2Lep_1.SusyNt.e2149_s1581_s1586_r3658_r3549_p1512_n0150.140109072637/*");
ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodG.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226165537/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodG.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226165741/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodG.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226165834/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodG.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226165950/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodG.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226212240/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodG.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131231013459/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodG.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131231211711/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodH.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226170049/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodH.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226170139/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodH.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226170414/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodH.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226170511/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodH.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226170703/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodH.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226170845/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodH.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131226211647/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodH.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131231014228/*");
  ch->Add("/nobackup/etp2/Josephine.Wittkowski/SusyNtuples_n0150/Egamma/user.gerbaudo.group.phys-susy.data12_8TeV.periodH.physics_Egamma.PhysCont.SusyNt.repro14_v01_p1542_n0150.131231212508/*");
  
  

  
     

	    


      Long64_t nEntries = ch->GetEntries();
      ch->ls();

      cout << "all entries: " << nEntries << endl;


      TSelector_SusyNtuple_excess* SusyNtupleObject = new TSelector_SusyNtuple_excess();
      SusyNtupleObject->buildSumwMap(ch);
//       TString options="NtSys_NOM";
      ch->Process(SusyNtupleObject);
      delete SusyNtupleObject;
      
      if (ch) {delete ch; ch=0;}

  abort();
  }
void run_root_TSelector_SusySel(TString InputPath) {


    
      cout<<"Have you set up RootCore via  \"source RootCore/scripts/setup.sh\" ?"<<endl;  

      gSystem->Setenv("ROOTCOREDIR", "/data/etp3/jwittkow/analysis_SUSYTools_03_04/RootCore");
      gSystem->SetIncludePath("-I$ROOTCOREDIR/include/");
//       gROOT->ProcessLine("#include <vector>");
      gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+"); 

      TString selectorName = "SusySel"; // !!! enter the name of your Selector (without _C.so)

      TChain *ch;
      ch = new TChain("SusySel");


      TString processLine = ".L " + selectorName + ".C++g";
      TString execLine;

      gROOT->ProcessLine(processLine); // need to add this, or PoD at LRZ will not be able to load the .so
      gROOT->ProcessLine(".x $ROOTCOREDIR/scripts/load_packages.C+");
      ch->Add(InputPath);

//       ch->Add("/data/etp3/jwittkow/analysis_SUSYTools_03_04/WZ_SusySel.root");



      Long64_t nEntries = ch->GetEntries();
      ch->ls();

      cout << "all entries: " << nEntries << endl;
      
      ch->Process("SusySel.C+g");
      
      if (ch) {delete ch; ch=0;}

  abort();
  }
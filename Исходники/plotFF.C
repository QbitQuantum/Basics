void plotFF(char * infname1 = "/net/pstore01/d00/scratch/frankma/hiroot/pythia100_5k_dijet_000777.root",
            char * infname2 = "/net/pstore01/d00/scratch/frankma/hiroot/pyquen100_5k_dijet_000777.root",
	    // -pythia-
	    TString PythiaAnaNJetEtMin = "90",
	    TString PythiaAnaNJetEtMax = "",
	    TString PythiaAnaAJetEtMin = "50",
	    // -pyquen-
	    TString PyquenAnaNJetEtMin = "90",
	    TString PyquenAnaNJetEtMax = "",
	    TString PyquenAnaAJetEtMin = "50",
	    TString JDPhiMin = "3.0",
	    char * plotdir = "plots",
	    const Int_t NXIBIN = 10,
	    const Double_t XIMAX = 9.,
	    const Double_t XIYMAX = 10,
	    Bool_t check = kFALSE
      )
{
   cout << PythiaAnaNJetEtMin << " " << PythiaAnaNJetEtMax << " " << PythiaAnaAJetEtMin << " "
      << PyquenAnaNJetEtMin << " " << PyquenAnaNJetEtMax << " " << PyquenAnaAJetEtMin
      << endl;
   //=== Setup ana cuts ===
   // --Et--
   TString PythiaAnaJetCut;
   if (!PythiaAnaNJetEtMin.IsDigit())
      terminate(Form("PythiaAnaNJetEtMin: %s is not a digit",PythiaAnaNJetEtMin.Data()));
   PythiaAnaJetCut = "npet>"+PythiaAnaNJetEtMin;
   if (!PythiaAnaNJetEtMax.IsNull()) {
      if (!PythiaAnaNJetEtMax.IsDigit())
	 terminate(Form("PythiaAnaNJetEtMax: %s is not a digit",PythiaAnaNJetEtMax.Data()));
      PythiaAnaJetCut += (" && npet<"+PythiaAnaNJetEtMax);
   }
   if (!PythiaAnaAJetEtMin.IsNull()) {
      if (!PythiaAnaAJetEtMin.IsDigit())
	 terminate(Form("PythiaAnaAJetEtMin: %s is not a digit",PythiaAnaAJetEtMin.Data()));
      PythiaAnaJetCut += (" && apet>"+PythiaAnaAJetEtMin);
   }
   //--
   TString PyquenAnaJetCut;
   if (!PyquenAnaNJetEtMin.IsDigit())
      terminate(Form("PyquenAnaNJetEtMin: %s is not a digit",PyquenAnaNJetEtMin.Data()));
   PyquenAnaJetCut = "npet>"+PyquenAnaNJetEtMin;
   if (!PyquenAnaNJetEtMax.IsNull()) {
      if (!PyquenAnaNJetEtMax.IsDigit())
	 terminate(Form("PyquenAnaNJetEtMax: %s is not a digit",PyquenAnaNJetEtMax.Data()));
      PyquenAnaJetCut += (" && npet<"+PyquenAnaNJetEtMax);
   }
   if (!PyquenAnaAJetEtMin.IsNull()) {
      if (!PyquenAnaAJetEtMin.IsDigit())
	 terminate(Form("PyquenAnaAJetEtMin: %s is not a digit",PyquenAnaAJetEtMin.Data()));
      PyquenAnaJetCut += (" && apet>"+PyquenAnaAJetEtMin);
   }
   // --Opening angle--
   TString JDPhiCut = ("apdphi>" + JDPhiMin);
   PythiaAnaJetCut += (" && " + JDPhiCut);
   PyquenAnaJetCut += (" && " + JDPhiCut);
   
   // --Jet constituent--
   TString AnaNPConeCut = "abs(pndphi)<0.5";
   TString AnaAPConeCut = "abs(padphi)<0.5";
   // --Particle pt--
   TString ParticlePtCut = "ppt>0.5";

   TString PythiaNearFFCut = PythiaAnaJetCut + " && " + AnaNPConeCut + " && " + ParticlePtCut;
   TString PythiaAwayFFCut = PythiaAnaJetCut + " && " + AnaAPConeCut + " && " + ParticlePtCut;
   TString PyquenNearFFCut = PyquenAnaJetCut + " && " + AnaNPConeCut + " && " + ParticlePtCut;
   TString PyquenAwayFFCut = PyquenAnaJetCut + " && " + AnaAPConeCut + " && " + ParticlePtCut;

   printf("\n=========================Cuts setup======================\n");
   printf("Near Pythia FF cut: %s\n",PythiaNearFFCut.Data());
   printf("Away Pythia FF cut: %s\n",PythiaAwayFFCut.Data());
   printf("Near Pyquen FF cut: %s\n",PyquenNearFFCut.Data());
   printf("Away Pyquen FF cut: %s\n",PyquenAwayFFCut.Data());

   bool NoNorm = false;

   //=== Get input files ===
   //---pythia---
   TFile * infile = findFile(infname1);
   TNtuple * ntPythia = dynamic_cast<TNtuple*>(infile->Get("NTTruePFF"));
   TNtuple * ntJetPythia = dynamic_cast<TNtuple*>(infile->Get("NTJetFF"));
   TNtuple * ntJetLeadingPythia = dynamic_cast<TNtuple*>(infile->Get("NTJetLeading"));
   //---pyquen---
   TFile * infile2 = findFile(infname2);
   TNtuple * ntPyquen = dynamic_cast<TNtuple*>(infile2->Get("NTTruePFF"));
   TNtuple * ntJetPyquen = dynamic_cast<TNtuple*>(infile2->Get("NTJetFF"));
   TNtuple * ntJetLeadingPyquen = dynamic_cast<TNtuple*>(infile2->Get("NTJetLeading"));

   //---output---
   TFile * outfile = new TFile(Form("%s/FFHistos.root",plotdir),"RECREATE");

   if (check) {
      printf("\n============================Do Checks======================\n");
      printf("%s\n",infname1);
      printf("%s\n",infname2);
      //---- Check dijet properties ----
      //--- inv mass ---
      drawTree(ntJetPythia, "mass>>hMassPPythia","",drsgFF,"hMassPPythia","Pythia: inv mass of dijet",100,0,1800,true,kRed,1,3);
      drawTree(ntJetPyquen, "mass>>hMassPPyquen","",drdbFF,"hMassPPyquen","draw Pyquen: inv mass of dijet",100,0,1800,true,kBlue,1,3);
      //--- Et ---
      // -pythia-
      drawTree(ntJetPythia, "npet>>hNLPartonPPythia",PythiaNearFFCut.Data(),drsgFF,"hNLPartonPPythia","Pythia: leading partons",HJETETBINS,HJETETMIN,HJETETMAX,0,kRed,1,3);
      drawTree(ntJetPythia, "apet>>hALPartonPPythia",PythiaAwayFFCut.Data(),drdbFF,"hALPartonPPythia","Pythia: leading partons",HJETETBINS,HJETETMIN,HJETETMAX,0,kRed,7,3);
      // -pyquen--
      drawTree(ntJetPyquen, "npet>>hNLPartonPPyquen",PyquenNearFFCut.Data(),drdbFF,"hNLPartonPPyquen","Pyquen: leading partons",HJETETBINS,HJETETMIN,HJETETMAX,0,kBlue,1,3);
      drawTree(ntJetPyquen, "apet>>hALPartonPPyquen",PyquenAwayFFCut.Data(),drdbFF,"hALPartonPPyquen","Pyquen: leading partons",HJETETBINS,HJETETMIN,HJETETMAX,0,kBlue,7,3);
   }
   

   //---- Particles ----
   //--- inclusive angular correlations to leading partons---
   // -near-
   drawTree(ntPyquen, "pndphi>>hnPdPhiPyquen","",drsgFF,"hnPdPhiPyquen",";d#phi(particle,Jet);",100,-0.5*PI,1.5*PI,false,kBlue,1,3);
   drawTree(ntPythia, "pndphi>>hnPdPhiPythia","",drdbFF,"hnPdPhiPythia","Pythia: dphi to leading partons",100,-0.5*PI,1.5*PI,false,kRed,1,3);
   drawTree(ntJetPyquen, "pndphi>>hnPdPhiJetPyquen","",drdbFF,"hnPdPhiJetPyquen","JetPyquen: dphi to leading partons",100,-0.5*PI,1.5*PI,false,kBlue,1,3);
   drawTree(ntJetPythia, "pndphi>>hnPdPhiJetPythia","",drdbFF,"hnPdPhiJetPythia","JetPythia: dphi to leading partons",100,-0.5*PI,1.5*PI,false,kRed,1,3);
   // -away-
//   drawTree(ntPyquen, "padphi>>haPdPhiPyquen","",drdbFF,"haPdPhiPyquen","Pyquen: dphi to leading partons",100,-0.5*PI,1.5*PI,false,kBlue,7,3);
//   drawTree(ntPythia, "padphi>>haPdPhiPythia","",drdbFF,"haPdPhiPythia","draw Pythia: dphi to leading partons",100,-0.5*PI,1.5*PI,false,kRed,7,3);

   //--- inclusive Pt ---
   drawTree(ntPythia, "ppt>>hPPtPythia","",drsgFF,"hPPtPythia","Pythia: Pt of final state particles",100,0,50,true,kRed,1,3);
   drawTree(ntPyquen, "ppt>>hPPtPyquen","",drdbFF,"hPPtPyquen","draw Pyquen: Pt of final state particles",100,0,50,true,kBlue,1,3);

   //=== Get Normalizations ===
   //-- copy cuts --
   printf("\n=====================Calc Nomalizations=======================\n");
   TString PythiaNearLeadingCut = PythiaAnaJetCut.ReplaceAll("pet","ljet");
   TString PythiaAwayLeadingCut = PythiaAnaJetCut.ReplaceAll("pet","ljet");
   TString PyquenNearLeadingCut = PyquenAnaJetCut.ReplaceAll("pet","ljet");
   TString PyquenAwayLeadingCut = PyquenAnaJetCut.ReplaceAll("pet","ljet");
   PythiaNearLeadingCut = PythiaAnaJetCut.ReplaceAll("apdphi","jdphi");
   PythiaAwayLeadingCut = PythiaAnaJetCut.ReplaceAll("apdphi","jdphi");
   PyquenNearLeadingCut = PyquenAnaJetCut.ReplaceAll("apdphi","jdphi");
   PyquenAwayLeadingCut = PyquenAnaJetCut.ReplaceAll("apdphi","jdphi");
   printf("Near Pythia FF cut: %s\n",PythiaNearLeadingCut.Data());
   printf("Away Pythia FF cut: %s\n",PythiaAwayLeadingCut.Data());
   printf("Near Pyquen FF cut: %s\n",PyquenNearLeadingCut.Data());
   printf("Away Pyquen FF cut: %s\n",PyquenAwayLeadingCut.Data());
   //-- draw uncut distributions--
   // --comp with AnaJet
   drawNormHist(infile, "hJetEtDist",drsgFF,"","Jet Et [GeV]","#",1,true,2,7,1,1,1);
   drawNormHist(infile, "hLeadJetEtDist",drdbFF,"","Jet Et [GeV]","#",1,true,2,7,3,1,1);
   drawTree(ntJetLeadingPythia, "nljet>>hCheckNearLJetPythia0","",drdbFF,"hCheckNearLJetPythia0",";Et [GeV];",HJETETBINS,HJETETMIN,HJETETMAX,true,kBlack,1,1,1,8);
   // --from jet leading--
   drawTree(ntJetLeadingPythia, "nljet>>hCheckNearLJetPythia","",drsgFF,"hCheckNearLJetPythia",";Et [GeV];",HJETETBINS,HJETETMIN,HJETETMAX,true,kBlack,1,1,1,8);
   drawTree(ntJetLeadingPyquen, "nljet>>hCheckNearLJetPyquen","",drdbFF,"hCheckNearLJetPyquen",";Et [GeV];",HJETETBINS,HJETETMIN,HJETETMAX,true,kBlue,1,1,1,8);
   drawTree(ntJetLeadingPythia, "aljet>>hCheckAwayLJetPythia","",drdbFF,"hCheckAwayLJetPythia",";Et [GeV];",HJETETBINS,HJETETMIN,HJETETMAX,true,kBlack,7,1,1,8);
   drawTree(ntJetLeadingPyquen, "aljet>>hCheckAwayLJetPyquen","",drdbFF,"hCheckAwayLJetPyquen",";Et [GeV];",HJETETBINS,HJETETMIN,HJETETMAX,true,kBlue,7,1,1,8);
   //-- *apply cuts and calc normalization* --
   Float_t nJetPythia = drawTree(ntJetLeadingPythia, "nljet>>hCheckCutNearLJetPythia",PythiaNearLeadingCut.Data(),drdbFF,"hCheckCutNearLJetPythia",";Et [GeV];",HJETETBINS,HJETETMIN,HJETETMAX,true,kBlack,1,3,1,8);
   Float_t nJetPyquen = drawTree(ntJetLeadingPyquen, "nljet>>hCheckCutNearLJetPyquen",PyquenNearLeadingCut.Data(),drdbFF,"hCheckCutNearLJetPyquen",";Et [GeV];",HJETETBINS,HJETETMIN,HJETETMAX,true,kBlue,1,3,1,8);
   //-- draw also the away side after cut --
   drawTree(ntJetLeadingPythia, "aljet>>hCheckCutAwayLJetPythia",PythiaAwayLeadingCut.Data(),drdbFFE,"hCheckCutAwayLJetPythia",";Et [GeV];",HJETETBINS,HJETETMIN,HJETETMAX,true,kBlack,1,3,1,4);
   drawTree(ntJetLeadingPyquen, "aljet>>hCheckCutAwayLJetPyquen",PyquenAwayLeadingCut.Data(),drdbFFE,"hCheckCutAwayLJetPyquen",";Et [GeV];",HJETETBINS,HJETETMIN,HJETETMAX,true,kBlue,1,3,1,4);
   float nJetPythiaNorm = 1./nJetPythia;
   if (NoNorm) nJetPythiaNorm = 1.;
   printf("nJetPythias: %f,  jnorm: %f\n",nJetPythia,nJetPythiaNorm);
   float nJetPyquenNorm = 1./nJetPyquen;
   if (NoNorm) nJetPyquenNorm = 1.;
   printf("nJetPyquens: %f,  jnorm: %f\n",nJetPyquen,nJetPyquenNorm);

   //=== Finally: plot fragmentation properties ===
   printf("\n===================== Plot FF =======================\n");
   // -near-
   drawTree(ntJetPythia, "log(1/zn)>>hXiNearJetPythia",PythiaNearFFCut.Data(),drsgFFE,"hXiNearJetPythia",";(near) #xi=ln(E_{t}^{Jet}/E_{t}^{Particle});",NXIBIN,0,XIMAX,0,kBlack,1,3,1,8,nJetPythiaNorm,XIYMAX);
   drawTree(ntJetPyquen, "log(1/zn)>>hXiNearJetPyquen",PyquenNearFFCut.Data(),drdbFFE,"hXiNearJetPyquen","JetPyquen: FF of near parton",NXIBIN,0,XIMAX,0,kBlue,1,3,1,8,nJetPyquenNorm,XIYMAX);
   drawTree(ntPyquen, "log(1/zn)>>hXiNearPyquen",PyquenNearFFCut.Data(),drdbFF,"hXiNearPyquen",";(near) #xi=ln(E_{t}^{Jet}/E_{t}^{Particle})",NXIBIN,0,XIMAX,0,kRed-2,1,3,0,0,nJetPyquenNorm,XIYMAX);
   drawTree(ntPythia, "log(1/zn)>>hXiNearPythia",PythiaNearFFCut.Data(),drdbFF,"hXiNearPythia",";#xi=ln(E_{t}^{Jet}/E_{t}^{Particle};",NXIBIN,0,XIMAX,0,kRed,1,3,0,0,nJetPythiaNorm,XIYMAX);
   // -away-
   drawTree(ntJetPythia, "log(1/za)>>hXiAwayJetPythia",PythiaAwayFFCut.Data(),drsgFFE,"hXiAwayJetPythia",";(away) #xi=ln(E_{t}^{Jet}/E_{t}^{Particle});",NXIBIN,0,XIMAX,0,kBlack,1,3,1,8,nJetPythiaNorm,XIYMAX);
   drawTree(ntJetPyquen, "log(1/za)>>hXiAwayJetPyquen",PyquenAwayFFCut.Data(),drdbFFE,"hXiAwayJetPyquen","JetPyquen: FF of near parton",NXIBIN,0,XIMAX,0,kBlue,1,3,1,8,nJetPyquenNorm,XIYMAX);
   drawTree(ntPyquen, "log(1/za)>>hXiAwayPyquen",PyquenAwayFFCut.Data(),drdbFF,"hXiAwayPyquen",";(away) #xi=ln(E_{t}^{Jet}/E_{t}^{Particle})",NXIBIN,0,XIMAX,0,kRed-2,1,3,0,0,nJetPyquenNorm,XIYMAX);
   drawTree(ntPythia, "log(1/za)>>hXiAwayPythia",PythiaAwayFFCut.Data(),drdbFF,"hXiAwayPythia",";#xi=ln(E_{t}^{Jet}/E_{t}^{Particle};",NXIBIN,0,XIMAX,0,kRed,1,3,0,0,nJetPythiaNorm,XIYMAX);

   //---FF ratio2---
   // -parton-
   drawDivHist("hXiNearPyquen","hXiNearPythia",drsgFF,"hNearFFRatio",";#xi_{pyquen}/#xi_{pythia};",NXIBIN,0,XIMAX,0,kRed-2,1,3,0,0,3.);
   drawDivHist("hXiAwayPyquen","hXiAwayPythia",drdbFF,"hAwayFFRatio","draw Away FF ratio: Pyquen/Pythia",NXIBIN,0,XIMAX,0,kRed-2,7,3,1,4);
   // -Jet-
   drawDivHist("hXiNearJetPyquen","hXiNearJetPythia",drdbFFE,"hNearJetFFRatio",";#xi_{pyquen}/#xi_{pythia};",NXIBIN,0,XIMAX,0,kBlue,1,3,1,8);
   drawDivHist("hXiAwayJetPyquen","hXiAwayJetPythia",drdbFFE,"hAwayJetFFRatio","draw Away FF ratio: Pyquen/Pythia",NXIBIN,0,XIMAX,0,kBlue,7,3,1,4);

   //=== Save and exit ===
   printAllCanvases(plotdir);
   outfile->Write();
   outfile->Close();
}
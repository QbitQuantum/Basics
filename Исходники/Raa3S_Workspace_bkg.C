void Raa3S_Workspace(const char* name_pbpb="chad_ws_fits/centFits/ws_PbPbData_262548_263757_0cent10_0.0pt50.0_0.0y2.4.root", const char* name_pp="chad_ws_fits/centFits/ws_PPData_262157_262328_-1cent1_0.0pt50.0_0.0y2.4.root", const char* name_out="fitresult_combo.root"){

   //TFile File(filename);

   //RooWorkspace * ws = test_combine(name_pbpb, name_pp);

   TFile *f = new TFile("fitresult_combo_333.root") ;
   RooWorkspace * ws1 = (RooWorkspace*) f->Get("wcombo");

   //File.GetObject("wcombo", ws);
   ws1->Print();
   RooAbsData * data = ws1->data("data"); //dataOS, dataSS

   // RooDataSet * US_data = (RooDataSet*) data->reduce( "QQsign == QQsign::PlusMinus");
   // US_data->SetName("US_data");
   // ws->import(* US_data);
   // RooDataSet * hi_data = (RooDataSet*) US_data->reduce("dataCat == dataCat::hi");
   // hi_data->SetName("hi_data");
   // ws->import(* hi_data);
   // hi_data->Print();

   RooRealVar* raa3 = new RooRealVar("raa3","R_{AA}(#Upsilon (3S))",0.5,-1,1);
   RooRealVar* leftEdge = new RooRealVar("leftEdge","leftEdge",0);
   RooRealVar* rightEdge = new RooRealVar("rightEdge","rightEdge",1);
   RooGenericPdf step("step", "step", "(@0 >= @1) && (@0 < @2)", RooArgList(*raa3, *leftEdge, *rightEdge));
   ws1->import(step);
   ws1->factory( "Uniform::flat(raa3)" );

   //pp Luminosities, Taa and efficiency ratios Systematics

   ws1->factory( "Taa_hi[5.662e-9]" );
   ws1->factory( "Taa_kappa[1.062]" ); // was 1.057
   ws1->factory( "expr::alpha_Taa('pow(Taa_kappa,beta_Taa)',Taa_kappa,beta_Taa[0,-5,5])" );
   ws1->factory( "prod::Taa_nom(Taa_hi,alpha_Taa)" );
   ws1->factory( "Gaussian::constr_Taa(beta_Taa,glob_Taa[0,-5,5],1)" );

   ws1->factory( "lumipp_hi[5.4]" );
   ws1->factory( "lumipp_kappa[1.037]" ); // was 1.06
   ws1->factory( "expr::alpha_lumipp('pow(lumipp_kappa,beta_lumipp)',lumipp_kappa,beta_lumipp[0,-5,5])" );
   ws1->factory( "prod::lumipp_nom(lumipp_hi,alpha_lumipp)" );
   ws1->factory( "Gaussian::constr_lumipp(beta_lumipp,glob_lumipp[0,-5,5],1)" );

   // ws->factory( "effRat1[1]" );
   // ws->factory( "effRat2[1]" );
   ws1->factory( "effRat3_hi[0.95]" );
   ws1->factory( "effRat_kappa[1.054]" );
   ws1->factory( "expr::alpha_effRat('pow(effRat_kappa,beta_effRat)',effRat_kappa,beta_effRat[0,-5,5])" );
   // ws->factory( "prod::effRat1_nom(effRat1_hi,alpha_effRat)" );
   ws1->factory( "Gaussian::constr_effRat(beta_effRat,glob_effRat[0,-5,5],1)" );
   // ws->factory( "prod::effRat2_nom(effRat2_hi,alpha_effRat)" );
   ws1->factory( "prod::effRat3_nom(effRat3_hi,alpha_effRat)" );
   //  
   ws1->factory("Nmb_hi[1.161e9]");
   ws1->factory("prod::denominator(Taa_nom,Nmb_hi)");
   ws1->factory( "expr::lumiOverTaaNmbmodified('lumipp_nom/denominator',lumipp_nom,denominator)");
   RooAbsReal *lumiOverTaaNmbmodified = ws1->function("lumiOverTaaNmbmodified"); //RooFormulaVar *lumiOverTaaNmbmodified = ws->function("lumiOverTaaNmbmodified");
   //  
   //  RooRealVar *raa1 = ws->var("raa1");
   //  RooRealVar* nsig1_pp = ws->var("nsig1_pp");
   //  RooRealVar* effRat1 = ws->function("effRat1_nom");
   //  RooRealVar *raa2 = ws->var("raa2");
   //  RooRealVar* nsig2_pp = ws->var("nsig2_pp");
   //  RooRealVar* effRat2 = ws->function("effRat2_nom");
   RooRealVar* nsig3_pp = ws1->var("R_{#frac{3S}{1S}}_pp"); //RooRealVar* nsig3_pp = ws->var("N_{#Upsilon(3S)}_pp");
   cout << nsig3_pp << endl;
   RooAbsReal* effRat3 = ws1->function("effRat3_nom"); //RooRealVar* effRat3 = ws->function("effRat3_nom");
   //  
   //  RooFormulaVar nsig1_hi_modified("nsig1_hi_modified", "@0*@1*@3/@2", RooArgList(*raa1, *nsig1_pp, *lumiOverTaaNmbmodified, *effRat1));
   //  ws->import(nsig1_hi_modified);
   //  RooFormulaVar nsig2_hi_modified("nsig2_hi_modified", "@0*@1*@3/@2", RooArgList(*raa2, *nsig2_pp, *lumiOverTaaNmbmodified, *effRat2));
   //  ws->import(nsig2_hi_modified);
   RooFormulaVar nsig3_hi_modified("nsig3_hi_modified", "@0*@1*@3/@2", RooArgList(*raa3, *nsig3_pp, *lumiOverTaaNmbmodified, *effRat3));
   ws1->import(nsig3_hi_modified);

   //  // background yield with systematics
   ws1->factory( "nbkg_hi_kappa[1.10]" );
   ws1->factory( "expr::alpha_nbkg_hi('pow(nbkg_hi_kappa,beta_nbkg_hi)',nbkg_hi_kappa,beta_nbkg_hi[0,-5,5])" );
   ws1->factory( "SUM::nbkg_hi_nom(alpha_nbkg_hi*bkgPdf_hi)" );
   ws1->factory( "Gaussian::constr_nbkg_hi(beta_nbkg_hi,glob_nbkg_hi[0,-5,5],1)" );
   RooAbsPdf* sig1S_hi = ws1->pdf("sig1S_hi"); //RooAbsPdf* sig1S_hi = ws->pdf("cbcb_hi");
   RooAbsPdf* sig2S_hi = ws1->pdf("sig2S_hi");
   RooAbsPdf* sig3S_hi = ws1->pdf("sig3S_hi");
   RooAbsPdf* LSBackground_hi = ws1->pdf("nbkg_hi_nom");
   RooRealVar* nsig1_hi = ws1->var("N_{#Upsilon(1S)}_hi");
   RooRealVar* nsig2_hi = ws1->var("R_{#frac{2S}{1S}}_hi");
   RooAbsReal* nsig3_hi = ws1->function("nsig3_hi_modified"); //RooFormulaVar* nsig3_hi = ws->function("nsig3_hi_modified");
   cout << nsig1_hi << " " << nsig2_hi << " " << nsig3_pp << endl;
   RooRealVar* norm_nbkg_hi = ws1->var("n_{Bkgd}_hi");

   RooArgList pdfs_hi( *sig1S_hi,*sig2S_hi,*sig3S_hi, *LSBackground_hi);
   RooArgList norms_hi(*nsig1_hi,*nsig2_hi,*nsig3_hi, *norm_nbkg_hi);

   ////////////////////////////////////////////////////////////////////////////////

   ws1->factory( "nbkg_pp_kappa[1.03]" );
   ws1->factory( "expr::alpha_nbkg_pp('pow(nbkg_pp_kappa,beta_nbkg_pp)',nbkg_pp_kappa,beta_nbkg_pp[0,-5,5])" );
   ws1->factory( "SUM::nbkg_pp_nom(alpha_nbkg_pp*bkgPdf_pp)" );
   ws1->factory( "Gaussian::constr_nbkg_pp(beta_nbkg_pp,glob_nbkg_pp[0,-5,5],1)" );
   RooAbsPdf* sig1S_pp = ws1->pdf("sig1S_pp"); //RooAbsPdf* sig1S_pp = ws1->pdf("cbcb_pp");
   RooAbsPdf* sig2S_pp = ws1->pdf("sig2S_pp");
   RooAbsPdf* sig3S_pp = ws1->pdf("sig3S_pp");
   RooAbsPdf* LSBackground_pp = ws1->pdf("nbkg_pp_nom");
   RooRealVar* nsig1_pp = ws1->var("N_{#Upsilon(1S)}_pp");
   RooRealVar* nsig2_pp = ws1->var("R_{#frac{2S}{1S}}_pp"); //RooRealVar* nsig2_pp = ws1->var("N_{#Upsilon(2S)}_pp");
   // RooRealVar* nsig3_pp = ws1->var("N_{#Upsilon(3S)}_pp");
   RooRealVar* norm_nbkg_pp = ws1->var("n_{Bkgd}_pp");

   RooArgList pdfs_pp( *sig1S_pp,*sig2S_pp,*sig3S_pp, *LSBackground_pp);
   RooArgList norms_pp( *nsig1_pp,*nsig2_pp,*nsig3_pp,*norm_nbkg_pp);

   RooAddPdf model_num("model_num", "model_num", pdfs_hi,norms_hi); 
   ws1->import(model_num);
   ws1->factory("PROD::model_hi(model_num, constr_nbkg_hi,constr_lumipp,constr_Taa,constr_effRat)");

   RooAddPdf model_den("model_den", "model_den", pdfs_pp,norms_pp); 
   ws1->import(model_den);
   ws1->factory("PROD::model_pp(model_den, constr_nbkg_pp)");

   ws1->factory("SIMUL::joint(dataCat,hi=model_hi,pp=model_pp)");



   /////////////////////////////////////////////////////////////////////
   RooRealVar * pObs = ws1->var("invariantMass"); // get the pointer to the observable
   RooArgSet obs("observables");
   obs.add(*pObs);
   obs.add( *ws1->cat("dataCat"));    
   //  /////////////////////////////////////////////////////////////////////
   ws1->var("glob_lumipp")->setConstant(true);
   ws1->var("glob_Taa")->setConstant(true);
   ws1->var("glob_effRat")->setConstant(true);
   ws1->var("glob_nbkg_pp")->setConstant(true);
   ws1->var("glob_nbkg_hi")->setConstant(true);
   RooArgSet globalObs("global_obs");
   globalObs.add( *ws1->var("glob_lumipp") );
   globalObs.add( *ws1->var("glob_Taa") );
   globalObs.add( *ws1->var("glob_effRat") );
   globalObs.add( *ws1->var("glob_nbkg_hi") );
   globalObs.add( *ws1->var("glob_nbkg_pp") );
   cout << "66666" << endl;

   // ws1->Print();

   RooArgSet poi("poi");
   poi.add( *ws1->var("raa3") );



   cout << "77777" << endl;
   // create set of nuisance parameters
   RooArgSet nuis("nuis");
   nuis.add( *ws1->var("beta_lumipp") );
   nuis.add( *ws1->var("beta_nbkg_hi") );
   nuis.add( *ws1->var("beta_nbkg_pp") );
   nuis.add( *ws1->var("beta_Taa") );
   nuis.add( *ws1->var("beta_effRat") );

   cout << "88888" << endl;
   ws1->var("#alpha_{CB}_hi")->setConstant(true);
   ws1->var("#alpha_{CB}_pp")->setConstant(true);
   ws1->var("#sigma_{CB1}_hi")->setConstant(true);
   ws1->var("#sigma_{CB1}_pp")->setConstant(true);
   ws1->var("#sigma_{CB2}/#sigma_{CB1}_hi")->setConstant(true);
   ws1->var("#sigma_{CB2}/#sigma_{CB1}_pp")->setConstant(true);
   //ws1->var("Centrality")->setConstant(true); //delete
   ws1->var("N_{#varUpsilon(1S)}_hi")->setConstant(true);
   ws1->var("N_{#varUpsilon(1S)}_pp")->setConstant(true);
   //ws1->var("N_{#Upsilon(2S)}_hi")->setConstant(true);
   //ws1->var("N_{#Upsilon(2S)}_pp")->setConstant(true);
   //ws1->var("N_{#Upsilon(3S)}_pp")->setConstant(true);

   ws1->var("R_{#frac{2S}{1S}}_hi")->setConstant(true); //new
   ws1->var("R_{#frac{2S}{1S}}_pp")->setConstant(true); //new
   ws1->var("R_{#frac{3S}{1S}}_hi")->setConstant(true); //new
   ws1->var("R_{#frac{3S}{1S}}_pp")->setConstant(true); //new

   ws1->var("Nmb_hi")->setConstant(true);
   // ws1->var("QQsign")->setConstant(true);
   ws1->var("Taa_hi")->setConstant(true);
   ws1->var("Taa_kappa")->setConstant(true);
   // ws1->var("beta_Taa")->setConstant(true);
   // ws1->var("beta_effRat")->setConstant(true);
   // ws1->var("beta_lumipp")->setConstant(true);
   // ws1->var("beta_nbkg_hi")->setConstant(true);
   // ws1->var("beta_nbkg_pp")->setConstant(true);
   // ws1->var("dataCat")->setConstant(true);
   ws1->var("decay_hi")->setConstant(true);
   ws1->var("decay_pp")->setConstant(true);
   ws1->var("effRat3_hi")->setConstant(true);
   ws1->var("effRat_kappa")->setConstant(true);
   // ws1->var("glob_Taa")->setConstant(true);
   // ws1->var("glob_effRat")->setConstant(true);
   // ws1->var("glob_lumipp")->setConstant(true);
   // ws1->var("glob_nbkg_hi")->setConstant(true);
   // ws1->var("glob_nbkg_pp")->setConstant(true);
   // ws1->var("invariantMass")->setConstant(true);
   ws1->var("leftEdge")->setConstant(true);
   ws1->var("lumipp_hi")->setConstant(true);
   ws1->var("lumipp_kappa")->setConstant(true);
   ws1->var("m_{ #varUpsilon(1S)}_hi")->setConstant(true); //ws1->var("mass1S_hi")->setConstant(true);
   ws1->var("m_{ #varUpsilon(1S)}_pp")->setConstant(true); //ws1->var("mass1S_pp")->setConstant(true);
   ws1->var("muMinusPt")->setConstant(true);
   ws1->var("muPlusPt")->setConstant(true);
   ws1->var("n_{Bkgd}_hi")->setConstant(true);
   ws1->var("n_{Bkgd}_pp")->setConstant(true);
   ws1->var("nbkg_hi_kappa")->setConstant(true);
   ws1->var("nbkg_pp_kappa")->setConstant(true);
   //ws1->var("n_{CB}")->setConstant(true); //ws1->var("n_{CB}")->setConstant(true); //ws1->var("npow")->setConstant(true);
   ws1->var("n_{CB}_hi")->setConstant(true); //ws1->var("n_{CB}")->setConstant(true); //ws1->var("npow")->setConstant(true);
   ws1->var("n_{CB}_pp")->setConstant(true); //ws1->var("n_{CB}")->setConstant(true); //ws1->var("npow")->setConstant(true);
   // ws1->var("raa3")->setConstant(true);
   ws1->var("rightEdge")->setConstant(true);
   ws1->var("sigmaFraction_hi")->setConstant(true);
   ws1->var("sigmaFraction_pp")->setConstant(true);
   ws1->var("turnOn_hi")->setConstant(true);
   ws1->var("turnOn_pp")->setConstant(true);
   ws1->var("dimuPt")->setConstant(true); //ws1->var("upsPt")->setConstant(true);
   ws1->var("dimuRapidity")->setConstant(true); //ws1->var("upsRapidity")->setConstant(true);
   ws1->var("vProb")->setConstant(true);
   ws1->var("width_hi")->setConstant(true);
   ws1->var("width_pp")->setConstant(true);
   // ws1->var("x3raw")->setConstant(true);
   //  RooArgSet fixed_again("fixed_again");
   //  fixed_again.add( *ws1->var("leftEdge") );
   //  fixed_again.add( *ws1->var("rightEdge") );
   //  fixed_again.add( *ws1->var("Taa_hi") );
   //  fixed_again.add( *ws1->var("Nmb_hi") );
   //  fixed_again.add( *ws1->var("lumipp_hi") );
   //  fixed_again.add( *ws1->var("effRat1_hi") );
   //  fixed_again.add( *ws1->var("effRat2_hi") );
   //  fixed_again.add( *ws1->var("effRat3_hi") );
   //  fixed_again.add( *ws1->var("nsig3_pp") );
   //  fixed_again.add( *ws1->var("nsig1_pp") );
   //  fixed_again.add( *ws1->var("nbkg_hi") );
   //  fixed_again.add( *ws1->var("alpha") );
   //  fixed_again.add( *ws1->var("nbkg_kappa") );
   //  fixed_again.add( *ws1->var("Taa_kappa") );
   //  fixed_again.add( *ws1->var("lumipp_kappa") );
   // fixed_again.add( *ws1->var("mean_hi") );
   // fixed_again.add( *ws1->var("mean_pp") );
   // fixed_again.add( *ws1->var("width_hi") );
   // fixed_again.add( *ws1->var("turnOn_hi") );
   // fixed_again.add( *ws1->var("bkg_a1_pp") );
   // fixed_again.add( *ws1->var("bkg_a2_pp") );
   // fixed_again.add( *ws1->var("decay_hi") );
   // fixed_again.add( *ws1->var("raa1") );
   // fixed_again.add( *ws1->var("raa2") );
   //  fixed_again.add( *ws1->var("nsig2_pp") );
   // fixed_again.add( *ws1->var("sigma1") );
   //  fixed_again.add( *ws1->var("nbkg_pp") );
   // fixed_again.add( *ws1->var("npow") );
   // fixed_again.add( *ws1->var("muPlusPt") );
   // fixed_again.add( *ws1->var("muMinusPt") );
   // fixed_again.add( *ws1->var("mscale_hi") );
   // fixed_again.add( *ws1->var("mscale_pp") );
   //  
   // ws1->Print();
   cout << "99999" << endl;

   // create signal+background Model Config
   RooStats::ModelConfig sbHypo("SbHypo");
   sbHypo.SetWorkspace( *ws1 );
   sbHypo.SetPdf( *ws1->pdf("joint") );
   sbHypo.SetObservables( obs );
   sbHypo.SetGlobalObservables( globalObs );
   sbHypo.SetParametersOfInterest( poi );
   sbHypo.SetNuisanceParameters( nuis );
   sbHypo.SetPriorPdf( *ws1->pdf("step") ); // this is optional

   // ws1->Print();
   /////////////////////////////////////////////////////////////////////
   RooAbsReal * pNll = sbHypo.GetPdf()->createNLL( *data,NumCPU(10) );
   cout << "111111" << endl;
   RooMinuit(*pNll).migrad(); // minimize likelihood wrt all parameters before making plots
   cout << "444444" << endl;
   RooPlot *framepoi = ((RooRealVar *)poi.first())->frame(Bins(10),Range(0.,0.2),Title("LL and profileLL in raa3"));
   cout << "222222" << endl;
   pNll->plotOn(framepoi,ShiftToZero());
   cout << "333333" << endl;
   
   RooAbsReal * pProfile = pNll->createProfile( globalObs ); // do not profile global observables
   pProfile->getVal(); // this will do fit and set POI and nuisance parameters to fitted values
   pProfile->plotOn(framepoi,LineColor(kRed));
   framepoi->SetMinimum(0);
   framepoi->SetMaximum(3);
   TCanvas *cpoi = new TCanvas();
   cpoi->cd(); framepoi->Draw();
   cpoi->SaveAs("cpoi.pdf");

   ((RooRealVar *)poi.first())->setMin(0.);
   RooArgSet * pPoiAndNuisance = new RooArgSet("poiAndNuisance");
   // pPoiAndNuisance->add(*sbHypo.GetNuisanceParameters());
   // pPoiAndNuisance->add(*sbHypo.GetParametersOfInterest());
   pPoiAndNuisance->add( nuis );
   pPoiAndNuisance->add( poi );
   sbHypo.SetSnapshot(*pPoiAndNuisance);

   RooPlot* xframeSB = pObs->frame(Title("SBhypo"));
   data->plotOn(xframeSB,Cut("dataCat==dataCat::hi"));
   RooAbsPdf *pdfSB = sbHypo.GetPdf();
   RooCategory *dataCat = ws1->cat("dataCat");
   pdfSB->plotOn(xframeSB,Slice(*dataCat,"hi"),ProjWData(*dataCat,*data));
   TCanvas *c1 = new TCanvas();
   c1->cd(); xframeSB->Draw();
   c1->SaveAs("c1.pdf");

   delete pProfile;
   delete pNll;
   delete pPoiAndNuisance;
   ws1->import( sbHypo );
   /////////////////////////////////////////////////////////////////////
   RooStats::ModelConfig bHypo = sbHypo;
   bHypo.SetName("BHypo");
   bHypo.SetWorkspace(*ws1);
   pNll = bHypo.GetPdf()->createNLL( *data,NumCPU(2) );
   RooArgSet poiAndGlobalObs("poiAndGlobalObs");
   poiAndGlobalObs.add( poi );
   poiAndGlobalObs.add( globalObs );
   pProfile = pNll->createProfile( poiAndGlobalObs ); // do not profile POI and global observables
   ((RooRealVar *)poi.first())->setVal( 0 );  // set raa3=0 here
   pProfile->getVal(); // this will do fit and set nuisance parameters to profiled values
   pPoiAndNuisance = new RooArgSet( "poiAndNuisance" );
   pPoiAndNuisance->add( nuis );
   pPoiAndNuisance->add( poi );
   bHypo.SetSnapshot(*pPoiAndNuisance);

   RooPlot* xframeB = pObs->frame(Title("Bhypo"));
   data->plotOn(xframeB,Cut("dataCat==dataCat::hi"));
   RooAbsPdf *pdfB = bHypo.GetPdf();
   pdfB->plotOn(xframeB,Slice(*dataCat,"hi"),ProjWData(*dataCat,*data));
   TCanvas *c2 = new TCanvas();
   c2->cd(); xframeB->Draw();
   c2->SaveAs("c2.pdf");

   delete pProfile;
   delete pNll;
   delete pPoiAndNuisance;

   // import model config into workspace
   bHypo.SetWorkspace(*ws1);
   ws1->import( bHypo );
   /////////////////////////////////////////////////////////////////////
   ws1->Print();
   bHypo.Print();
   sbHypo.Print();

   // save workspace to file
   ws1 -> SaveAs(name_out);

   return;
}
/*
 * Prepares the workspace to be used by the hypothesis test calculator
 */
void workspace_preparer(char *signal_file_name, char *signal_hist_name_in_file, char *background_file_name, char *background_hist_name_in_file, char *data_file_name, char *data_hist_name_in_file, char *config_file) {

    // Include the config_reader class.
    TString path = gSystem->GetIncludePath();
    path.Append(" -I/home/max/cern/cls/mario");
    gSystem->SetIncludePath(path);
    gROOT->LoadMacro("config_reader.cxx");

    // RooWorkspace used to store values.
    RooWorkspace * pWs = new RooWorkspace("ws");

    // Create a config_reader (see source for details) to read the config
    // file.
    config_reader reader(config_file, pWs);

    // Read MR and RR bounds from the config file.
    double MR_lower = reader.find_double("MR_lower");
    double MR_upper = reader.find_double("MR_upper");
    double RR_lower = reader.find_double("RR_lower");
    double RR_upper = reader.find_double("RR_upper");
    double MR_initial = (MR_lower + MR_upper)/2;
    double RR_initial = (RR_lower + RR_upper)/2;

    // Define the Razor Variables
    RooRealVar MR = RooRealVar("MR", "MR", MR_initial, MR_lower, MR_upper);
    RooRealVar RR = RooRealVar("RSQ", "RSQ", RR_initial, RR_lower, RR_upper);

    // Argument lists
    RooArgList pdf_arg_list(MR, RR, "input_args_list");
    RooArgSet pdf_arg_set(MR, RR, "input_pdf_args_set");



    /***********************************************************************/
    /* PART 1: IMPORTING SIGNAL AND BACKGROUND HISTOGRAMS                  */
    /***********************************************************************/

    /*
     * Get the signal's unextended pdf by converting the TH2D in the file
     * into a RooHistPdf
     */
    TFile *signal_file = new TFile(signal_file_name);
    TH2D *signal_hist = (TH2D *)signal_file->Get(signal_hist_name_in_file);
    RooDataHist *signal_RooDataHist = new RooDataHist("signal_roodatahist",
            "signal_roodatahist",
            pdf_arg_list,
            signal_hist);

    RooHistPdf *unextended_sig_pdf = new RooHistPdf("unextended_sig_pdf",
            "unextended_sig_pdf",
            pdf_arg_set,
            *signal_RooDataHist);

    /*
     * Repeat this process for the background.
     */
    TFile *background_file = new TFile(background_file_name);
    TH2D *background_hist =
        (TH2D *)background_file->Get(background_hist_name_in_file);
    RooDataHist *background_RooDataHist =
        new RooDataHist("background_roodatahist", "background_roodatahist",
                        pdf_arg_list, background_hist);
    RooHistPdf *unextended_bkg_pdf = new RooHistPdf("unextended_bkg_pdf",
            "unextended_bkg_pdf",
            pdf_arg_set,
            *background_RooDataHist);

    /*
     * Now, we want to create the bprime variable, which represents the
     * integral over the background-only sample.  We will perform the
     * integral automatically (that's why this is the only nuisance
     * parameter declared in this file - its value can be determined from
     * the input histograms).
     */
    ostringstream bprime_string;
    ostringstream bprime_pdf_string;
    bprime_string << "bprime[" << background_hist->Integral() << ", 0, 999999999]";
    bprime_pdf_string << "Poisson::bprime_pdf(bprime, " << background_hist->Integral() << ")";
    pWs->factory(bprime_string.str().c_str());
    pWs->factory(bprime_pdf_string.str().c_str());


    /*
     * This simple command will create all values from the config file
     * with 'make:' at the beginning and a delimiter at the end (see config
     * _reader if you don't know what a delimiter is).  In other
     * words, the luminosity, efficiency, transfer factors, and their pdfs
     * are created from this command.  The declarations are contained in the
     * config file to be changed easily without having to modify this code.
     */
    reader.factory_all();


    /*
     * Now, we want to create the extended pdfs from the unextended pdfs, as
     * well as from the S and B values we manufactured in the config file.
     * S and B are the values by which the signal and background pdfs,
     * respectively, are extended.  Recall that they were put in the
     * workspace in the reader.facotry_all() command.
     */
    RooAbsReal *S = pWs->function("S");
    RooAbsReal *B = pWs->function("B");

    RooExtendPdf *signalpart = new RooExtendPdf("signalpart", "signalpart",
            *unextended_sig_pdf, *S);
    RooExtendPdf *backgroundpart =
        new RooExtendPdf("backgroundpart", "backgroundpart",
                         *unextended_bkg_pdf, *B);

    RooArgList *pdf_list = new RooArgList(*signalpart, *backgroundpart,
                                          "list");
    // Add the signal and background pdfs to make a TotalPdf
    RooAddPdf *TotalPdf = new RooAddPdf("TotalPdf", "TotalPdf", *pdf_list);

    RooArgList *pdf_prod_list = new RooArgList(*TotalPdf,
            *pWs->pdf("lumi_pdf"),
            *pWs->pdf("eff_pdf"),
            *pWs->pdf("rho_pdf"),
            *pWs->pdf("bprime_pdf"));
    // This creates the final model pdf.
    RooProdPdf *model = new RooProdPdf("model", "model", *pdf_prod_list);

    /*
     * Up until now, we have been using the workspace pWs to contain all of
     * our values.  Now, all of our values that we require are in use in the
     * RooProdPdf called "model".  So, we need to import "model" into a
     * RooWorkspace.  To avoid recopying values into the rooworkspace, when
     * the values may already be present (which can cause problems), we will
     * simply create a new RooWorkspace to avoid confusion and problems.  The
     * new RooWorkspace is created here.
     */
    RooWorkspace *newworkspace = new RooWorkspace("newws");
    newworkspace->import(*model);

    // Immediately delete pWs, so we don't accidentally use it again.
    delete pWs;

    // Show off the newworkspace
    newworkspace->Print();

    // observables
    RooArgSet obs(*newworkspace->var("MR"), *newworkspace->var("RSQ"), "obs");

    // global observables
    RooArgSet globalObs(*newworkspace->var("nom_lumi"), *newworkspace->var("nom_eff"), *newworkspace->var("nom_rho"));

    //fix global observables to their nominal values
    newworkspace->var("nom_lumi")->setConstant();
    newworkspace->var("nom_eff")->setConstant();
    newworkspace->var("nom_rho")->setConstant();

    //Set Parameters of interest
    RooArgSet poi(*newworkspace->var("sigma"), "poi");


    //Set Nuisnaces

    RooArgSet nuis(*newworkspace->var("prime_lumi"), *newworkspace->var("prime_eff"), *newworkspace->var("prime_rho"), *newworkspace->var("bprime"));

    // priors (for Bayesian calculation)
    newworkspace->factory("Uniform::prior_signal(sigma)"); // for parameter of interest
    newworkspace->factory("Uniform::prior_bg_b(bprime)"); // for data driven nuisance parameter
    newworkspace->factory("PROD::prior(prior_signal,prior_bg_b)"); // total prior


    //Observed data is pulled from histogram.
    //TFile *data_file = new TFile(data_file_name);
    TFile *data_file = new TFile(data_file_name);
    TH2D *data_hist = (TH2D *)data_file->Get(data_hist_name_in_file);
    RooDataHist *pData = new RooDataHist("data", "data", obs, data_hist);
    newworkspace->import(*pData);

    // Now, we will draw our data from a RooDataHist.
    /*TFile *data_file = new TFile(data_file_name);
    TTree *data_tree = (TTree *) data_file->Get(data_hist_name_in_file);
    RooDataSet *pData = new RooDataSet("data", "data", data_tree, obs);
    newworkspace->import(*pData);*/


    // Craft the signal+background model
    ModelConfig * pSbModel = new ModelConfig("SbModel");
    pSbModel->SetWorkspace(*newworkspace);
    pSbModel->SetPdf(*newworkspace->pdf("model"));
    pSbModel->SetPriorPdf(*newworkspace->pdf("prior"));
    pSbModel->SetParametersOfInterest(poi);
    pSbModel->SetNuisanceParameters(nuis);
    pSbModel->SetObservables(obs);
    pSbModel->SetGlobalObservables(globalObs);

    // set all but obs, poi and nuisance to const
    SetConstants(newworkspace, pSbModel);
    newworkspace->import(*pSbModel);


    // background-only model
    // use the same PDF as s+b, with sig=0
    // POI value under the background hypothesis
    // (We will set the value to 0 later)

    Double_t poiValueForBModel = 0.0;
    ModelConfig* pBModel = new ModelConfig(*(RooStats::ModelConfig *)newworkspace->obj("SbModel"));
    pBModel->SetName("BModel");
    pBModel->SetWorkspace(*newworkspace);
    newworkspace->import(*pBModel);

    // find global maximum with the signal+background model
    // with conditional MLEs for nuisance parameters
    // and save the parameter point snapshot in the Workspace
    //  - safer to keep a default name because some RooStats calculators
    //    will anticipate it
    RooAbsReal * pNll = pSbModel->GetPdf()->createNLL(*pData);
    RooAbsReal * pProfile = pNll->createProfile(RooArgSet());
    pProfile->getVal(); // this will do fit and set POI and nuisance parameters to fitted values
    RooArgSet * pPoiAndNuisance = new RooArgSet();
    if(pSbModel->GetNuisanceParameters())
        pPoiAndNuisance->add(*pSbModel->GetNuisanceParameters());
    pPoiAndNuisance->add(*pSbModel->GetParametersOfInterest());
    cout << "\nWill save these parameter points that correspond to the fit to data" << endl;
    pPoiAndNuisance->Print("v");
    pSbModel->SetSnapshot(*pPoiAndNuisance);
    delete pProfile;
    delete pNll;
    delete pPoiAndNuisance;


    // Find a parameter point for generating pseudo-data
    // with the background-only data.
    // Save the parameter point snapshot in the Workspace
    pNll = pBModel->GetPdf()->createNLL(*pData);
    pProfile = pNll->createProfile(poi);
    ((RooRealVar *)poi.first())->setVal(poiValueForBModel);
    pProfile->getVal(); // this will do fit and set nuisance parameters to profiled values
    pPoiAndNuisance = new RooArgSet();
    if(pBModel->GetNuisanceParameters())
        pPoiAndNuisance->add(*pBModel->GetNuisanceParameters());
    pPoiAndNuisance->add(*pBModel->GetParametersOfInterest());
    cout << "\nShould use these parameter points to generate pseudo data for bkg only" << endl;
    pPoiAndNuisance->Print("v");
    pBModel->SetSnapshot(*pPoiAndNuisance);
    delete pProfile;
    delete pNll;
    delete pPoiAndNuisance;

    // save workspace to file
    newworkspace->writeToFile("ws_twobin.root");

    // clean up
    delete newworkspace;
    delete pData;
    delete pSbModel;
    delete pBModel;


} // ----- end of tutorial ----------------------------------------
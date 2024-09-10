void LHFit()
{
    
    double lorange = 100.;
    double hirange = 140.;
    
    // Import data
    TFile *file = new TFile("/atlas/data18a/yupan/HZZ4l2012/MiniTree/MiniTree_2013Moriond/v03/MC12a/JHUPythia8_AU2CTEQ6L1_ggH125_Spin0p_ZZ4lep.root");
    TTree *tree = (TTree*)file->Get("tree_incl_4mu");
    
    // Define variables
    float m4l = 0;
    float m34 = 0;
    float m4lerr = 0;
    float wgt = 0;
    
    // Get the number of entries in the tree
    int nevents = tree->GetEntries();
    
    tree->SetBranchStatus("*",0);
    tree->SetBranchStatus("m4l_unconstrained",1);
    tree->SetBranchStatus("mZ2_unconstrained",1);
    tree->SetBranchStatus("m4lerr_unconstrained",1);
    tree->SetBranchStatus("weight_corr",1);
    
    tree->SetBranchAddress("m4l_unconstrained",&m4l);
    tree->SetBranchAddress("mZ2_unconstrained",&m34);
    tree->SetBranchAddress("m4lerr_unconstrained",&m4lerr);
    tree->SetBranchAddress("weight_corr",&wgt);
    
    
    ///////////////
    // Build pdfs
    //////////////
    RooRealVar* mass = new RooRealVar("m4l","mass",lorange,hirange,"GeV");
    RooRealVar* mZ2 = new RooRealVar("m34","mZ2",10.,60.,"GeV");
    RooRealVar merr("m4lerr","mass err",0.1,5.0,"GeV");
    RooRealVar weight("weight","weight",0,10);

    
    float totalwgt(0);
    for (Int_t i=0; i<nevents; i++) {
        tree->GetEntry(i);
        totalwgt+=wgt;
    }
    std::cout<<"total weight = "<<totalwgt<<std::endl;
    
    
    //////////////////
    // Create ND dataset
    /////////////////
    RooDataSet signal("signal","signal",RooArgSet(*mass,*mZ2,merr,weight),"weight");
    
    std::cout<<"Reading in events from signal minitree"<<std::endl;
    for (int i=0; i<nevents; i++) {
        tree->GetEntry(i);
        mass->setVal(m4l);
        mZ2->setVal(m34);
        merr.setVal(m4lerr);
        weight.setVal(wgt/totalwgt);
        signal.add(RooArgSet(*mass,*mZ2,merr),wgt/totalwgt);
    }
    
    // Create 1D kernel estimation for signal mass
    RooKeysPdf kestmass("kestmass","kestmass",*mass,signal);
    // Create histogram of 1D kernel estimation pdf for mass
    TH1* hm = kestmass.createHistogram("hm",*mass);
    // Create mass pdf from the 1D kernel histogram
    RooDataHist* dmass = new RooDataHist("dmass","dmass",RooArgSet(*mass),hm);
    RooHistPdf* masspdf = new RooHistPdf("masspdf","masspdf",*mass,*dmass,2);
    
    
    
    //////////////////////////////
    // Construct plain likelihood
    /////////////////////////////
    
    // construct unbinned likelihood
    RooAbsReal *nll = masspdf->createNLL(signal,NumCPU(2));
    
    // Minimize likelihood w.r.t all parameters before making plots
    RooMinuit(*nll).migrad();
    
    // Plot likelihood scan mass
    RooPlot* frame1 = mass->frame(Bins(10),Title("LL and profileLL in mass"));
    
    // Construct profile likelihood in mass
    RooAbsReal *pll_mass = nll->createProfile(*mass);
    
    // Plot the profile likelihood in mass
    pll_mass->plotOn(frame1,LineColor(kRed));
    

    
    
    TCanvas *c = new TCanvas("c","c",800,600);
    gPad->SetLeftMargin(0.15);
    frame1->GetYaxis()->SetTitleOffset(1.4);
    frame1->Draw();
    c->SaveAs("testProLL.png");

    
    
    
    
}
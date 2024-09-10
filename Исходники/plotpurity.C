void plotpurity()
{

 Bool_t dolines = kFALSE;
 //Bool_t dolines = kTRUE;
 TString lines = "";

 TString xn = "";
 //TString xn = "_onlyQCD";
 //TString xn = "_onlyGJ";
 //TString xn = "_denominator";
 if(dolines){lines="/lines";}

 std::vector<TString> rebins;
 rebins.push_back("");
// rebins.push_back("rebin1");
// rebins.push_back("rebin2");
// rebins.push_back("rebin3");
// rebins.push_back("rebin4");
// rebins.push_back("rebin5");

 std::vector<TString> ptranges;
// ptranges.push_back("90to120");
// ptranges.push_back("120to155");
// ptranges.push_back("155to175");
 ptranges.push_back("175to190");
 ptranges.push_back("190to250");
 ptranges.push_back("250to400");
 ptranges.push_back("400to700");
 ptranges.push_back("700to1000");
 ptranges.push_back("175to1000");
 //ptranges.push_back("250to1000");
 //ptranges.push_back("400to1000");

 std::vector<TString> isovars;
 //isovars.push_back("wchiso");
 isovars.push_back("chiso");
// isovars.push_back("sieieF5x5");
// isovars.push_back("sieipF5x5");
// isovars.push_back("sipipF5x5");
// isovars.push_back("rho");
// isovars.push_back("nVtx");
// isovars.push_back("phoet");
// isovars.push_back("pfMET");

 std::vector<TString> cuts;
 cuts.push_back("a_idnc");
 cuts.push_back("b_idnc_mL30");
 cuts.push_back("c_idnc_trig");
 cuts.push_back("d_idnc_mL30_trig");
 cuts.push_back("e_idnc_t175");
 cuts.push_back("f_idnc_mL30_t175");
 cuts.push_back("g_idnc_t250");
 cuts.push_back("h_idnc_mL30_t250");
 cuts.push_back("i_idnc_mL30_allt");
// cuts.push_back("oldj");

 TString inpath = "/afs/hep.wisc.edu/cms/tperry/LoneG_slc6_491_CMSSW_7_4_14/src/LoneGamma/qcdStudy/gitignore/Lire/analyzed";
 TString outpath = "/afs/hep.wisc.edu/cms/tperry/LoneG_slc6_491_CMSSW_7_4_14/src/LoneGamma/qcdStudy/gitignore/Lire/plots";
 TString wwwpath = "/afs/hep.wisc.edu/home/tperry/www/MonoPhoton/qcdPlots/Lire/purity";

 TString inname_GJ  = inpath+"/purity_GJets_Merged.root";
 TString inname_QCD = inpath+"/purity_QCD_Merged.root";
// TString inname_GJ  = inpath+"/purity_mrg4bins_GJets.root";
// TString inname_QCD = inpath+"/purity_mrg4bins_QCD.root";
 //TString inname_GJ  = inpath+"/purity_mrg3bins_GJets.root";
 //TString inname_QCD = inpath+"/purity_mrg3bins_QCD.root";
 
 TFile *infile_GJ  = new TFile(inname_GJ);
 TFile *infile_QCD = new TFile(inname_QCD);
 
 ofstream log;
 ofstream log_latex;
 log.open (outpath+"/Purity_log"+xn+".txt");
 log_latex.open (outpath+"/Purity_log_latex"+xn+".txt");

 Int_t fillcolor = 3;
 gStyle->SetOptStat(0);
 gStyle->SetOptTitle(0);
 gStyle->SetFrameLineWidth(3);
 gStyle->SetLineWidth(2);

 TCanvas* canvas = new TCanvas("canvas","canvas",900,100,500,500);
 gStyle->SetOptStat(0);
 gPad->SetTickx();
 gPad->SetTicky();
 gStyle->SetLineWidth(3);


 TText* title = new TText(1,1,"") ;
 title->SetTextSize(0.07);
 title->SetTextColor(kBlack);
 title->SetTextAlign(13);
 title->SetTextFont(62);

 TText* extra = new TText(1,1,"") ;
 extra->SetTextSize(0.05);
 extra->SetTextColor(kBlack);
 extra->SetTextAlign(13);
 extra->SetTextFont(52);

 TText* lumi = new TText(1,1,"") ;
 lumi->SetTextSize(0.05);
 lumi->SetTextColor(kBlack);
 lumi->SetTextAlign(31);
 lumi->SetTextFont(42);

 int c_sig = 4;
 int c_bkg = 2;
 int c_den = 8;
 int ls_cmb = 1;
 int ls_gj  = 2;
 int ls_qcd = 3;

 //for(std::vector<TString>::iterator it = ptranges.begin(); it != ptranges.end(); ++it) {
 for(unsigned i=0; i<ptranges.size(); i++) {
  for(unsigned j=0; j<isovars.size(); j++) {
   for(unsigned k=0; k<cuts.size(); k++) {
    for(unsigned l=0; l<rebins.size(); l++) {

     TString ptrange = ptranges.at(i);
     TString isovar = isovars.at(j);
     TString cut = cuts.at(k);
     TString rebin = rebins.at(l);

     TString cutname;
     if(cut=="idnc"){cutname="ID";}
     if(cut=="idnc_mL30"){cutname="ID+MET";}
     if(cut=="idnc_trig"){cutname="ID+Trigger";}
     if(cut=="idnc_mL30_trig"){cutname="ID+MET+Trigger";}

     TString bwidth;
     if(rebin=="rebin1"){bwidth="width=0.5";}
     if(rebin=="rebin2"){bwidth="width=1.0";}
     if(rebin=="rebin3"){bwidth="width=1.5";}
     if(rebin=="rebin4"){bwidth="width=2.0";}
     if(rebin=="rebin5"){bwidth="width=2.5";}

     std::cout<<boost::format("%8s %15s %7s %7s ") % ptrange % cut % isovar % rebin<<std::endl;

     //Signal purity
     TH1F* h_Nsig_GJ  = (TH1F*)infile_GJ->Get("h_Nsig_"+isovar+"_"+ptrange+"_"+cut);
     TH1F* h_Nsig_QCD = (TH1F*)infile_QCD->Get("h_Nsig_"+isovar+"_"+ptrange+"_"+cut);
     h_Nsig_GJ->Rebin(3); h_Nsig_QCD->Rebin(3); //h_Nsig_GJ->Rebin(l+1); h_Nsig_QCD->Rebin(l+1);
             //TH1F* h_Nsig  = (TH1F*)h_Nsig_QCD->Clone("h_Nsig");
     TH1F* h_Nsig  = (TH1F*)h_Nsig_GJ->Clone("h_Nsig");
     h_Nsig->Add(h_Nsig_QCD);
     h_Nsig->SetLineColor(c_sig); h_Nsig_GJ->SetLineColor(c_sig); h_Nsig_QCD->SetLineColor(c_sig);
     h_Nsig->SetLineStyle(ls_cmb); h_Nsig_GJ->SetLineStyle(ls_gj); h_Nsig_QCD->SetLineStyle(ls_qcd);
     h_Nsig->SetLineWidth(2); h_Nsig_GJ->SetLineWidth(2); h_Nsig_QCD->SetLineWidth(2);
     //Background purity
     TH1F* h_Nbkg_GJ  = (TH1F*)infile_GJ->Get("h_Nbkg_"+isovar+"_"+ptrange+"_"+cut);
     TH1F* h_Nbkg_QCD = (TH1F*)infile_QCD->Get("h_Nbkg_"+isovar+"_"+ptrange+"_"+cut);
     h_Nbkg_GJ->Rebin(3); h_Nbkg_QCD->Rebin(3);
             //TH1F* h_Nbkg  = (TH1F*)h_Nbkg_QCD->Clone("h_Nbkg");
     TH1F* h_Nbkg  = (TH1F*)h_Nbkg_GJ->Clone("h_Nbkg");
     h_Nbkg->Add(h_Nbkg_QCD);
     h_Nbkg->SetLineColor(c_bkg); h_Nbkg_GJ->SetLineColor(c_bkg); h_Nbkg_QCD->SetLineColor(c_bkg);
     h_Nbkg->SetLineStyle(ls_cmb); h_Nbkg_GJ->SetLineStyle(ls_gj); h_Nbkg_QCD->SetLineStyle(ls_qcd);
     h_Nbkg->SetLineWidth(2); h_Nbkg_GJ->SetLineWidth(2); h_Nbkg_QCD->SetLineWidth(2);

     //Denominator
     TH1F* h_Deno_GJ  = (TH1F*)h_Nsig_GJ->Clone("h_Deno_GJ");
     h_Deno_GJ->Add(h_Nbkg_GJ);

     TH1F* h_Deno_QCD  = (TH1F*)h_Nsig_QCD->Clone("h_Deno_QCD");
     h_Deno_QCD->Add(h_Nbkg_QCD);

//     TH1F* h_Deno_GJ  = (TH1F*)infile_GJ->Get("h_Deno_"+isovar+"_"+ptrange+"_"+cut);
//     TH1F* h_Deno_QCD = (TH1F*)infile_QCD->Get("h_Deno_"+isovar+"_"+ptrange+"_"+cut);
//     h_Deno_GJ->Rebin(3); h_Deno_QCD->Rebin(3);
//             //TH1F* h_Deno  = (TH1F*)h_Deno_QCD->Clone("h_Deno");
     TH1F* h_Deno  = (TH1F*)h_Deno_GJ->Clone("h_Deno");
     h_Deno->Add(h_Deno_QCD);

     h_Deno->SetLineColor(c_den); h_Deno_GJ->SetLineColor(c_den); h_Deno_QCD->SetLineColor(c_den);
     h_Deno->SetLineStyle(ls_cmb); h_Deno_GJ->SetLineStyle(ls_gj); h_Deno_QCD->SetLineStyle(ls_qcd);
     h_Deno->SetLineWidth(1); h_Deno_GJ->SetLineWidth(1); h_Deno_QCD->SetLineWidth(1);

     // should probably add these as last bin..
     h_Nsig->ClearUnderflowAndOverflow();
     h_Nbkg->ClearUnderflowAndOverflow();
     h_Deno->ClearUnderflowAndOverflow();
     
     //Define purity
     TGraphAsymmErrors *purity_signal     = new TGraphAsymmErrors(h_Nsig,h_Deno,"n");
     purity_signal->SetLineWidth(2);
     purity_signal->SetLineColor(4);
     purity_signal->SetMarkerColor(4);
     purity_signal->SetMarkerStyle(20);
     
     TGraphAsymmErrors *purity_background = new TGraphAsymmErrors(h_Nbkg,h_Deno,"n");
     purity_background->SetLineWidth(2);
     purity_background->SetLineColor(2);
     purity_background->SetMarkerColor(2);
     purity_background->SetMarkerStyle(24);

     //-----------------------------------------------------
     // Calculations
     log<<boost::format("%8s %15s %7s %7s ") % ptrange % cut % isovar % rebin  ;

     // Start lower bound calculation
     Int_t nbins;
     nbins = purity_background->GetN();
     log<<boost::format("(%2i bins) \n") % nbins ; 

     std::vector<Double_t> thresholds, xsatthresh, ysatthresh, xsatqt, avgpur;
     std::vector<Int_t> batthresh, batqt;

     thresholds.clear(); // purity thresholds
     xsatthresh.clear(); // x st. f(x) > thresh
     ysatthresh.clear(); // y = f(x)x at thresh
     batthresh.clear();  // bin corresponding to x

     batqt.clear();      // bin at upper threshold
     xsatqt.clear();     // x value at upper thresh

     avgpur.clear();     // average purity over range

     thresholds.push_back(0.50);
     thresholds.push_back(0.55);
     thresholds.push_back(0.60);
     thresholds.push_back(0.65);
     thresholds.push_back(0.70);
     Int_t nthreshs;
     nthreshs = thresholds.size();

     // find purity lower bounds = x st. f(x)>thresh
     Double_t pointx, pointy;     
     for(int m=0; m<nbins; ++m){
      purity_background->GetPoint(m, pointx, pointy);
      //log<<boost::format(" %2i %2.2f %2.2f \n") % i % pointx % pointy;
      
      for(int n=0; n<nthreshs; ++n){
       if(pointy > thresholds.at(n) && ysatthresh.size()==n ){
        ysatthresh.push_back(pointy);
        xsatthresh.push_back(pointx);
        batthresh.push_back(h_Nsig->FindBin(pointx));
       }
      }
     }

     // for thresholds never reached, fill with content of xmax
     purity_background->GetPoint(nbins-1,pointx,pointy);
     Int_t nrnpassthresh = 0;
     nrnpassthresh = nthreshs - ysatthresh.size();
     for(int n=0; n<nrnpassthresh; ++n){
       ysatthresh.push_back(pointy);
       xsatthresh.push_back(pointx);
       batthresh.push_back(h_Nsig->FindBin(pointx));
     }

     //// dump lower bound threshold info
     //for(int n=0; n<nthreshs; ++n){
     // log<<boost::format("  Threshold: %.2f  %2i (%2.2f, %0.2f)\n")
     //  % thresholds.at(n) % batthresh.at(n) % xsatthresh.at(n) % ysatthresh.at(n) ;
     //}

     log<<boost::format("   Threshold bin (xx.x,yy.y) TotalSize   above|below\n");
     // Start upper bound calculation
     Double_t fullsize = h_Nbkg->Integral(0,-1);
     for(int n=0; n<nthreshs; ++n){
      Double_t sizedown = h_Nbkg->Integral(0,batthresh.at(n)-1);
      Double_t sizeup =   h_Nbkg->Integral(batthresh.at(n),-1);
      log<<boost::format("    %7.2f %3i (%2.1f,%1.2f)    %4.1f  %6.1f|%6.1f \n")
       % thresholds.at(n) % batthresh.at(n) % xsatthresh.at(n) % ysatthresh.at(n)    
       % fullsize % sizeup % sizedown ;
     }

     // upper bound calculation 
     // keep adding contents of bins starting at threshbin 
      // until sum > fraction (1/4) of full integral
     Double_t goalsize = fullsize / 4.;

     for(int n=0; n<nthreshs; ++n){
      Double_t thissize = 0.;
      int thisbin = batthresh.at(n);
      while( thisbin < nbins+1 ){
       thissize += h_Nbkg->GetBinContent(thisbin); 
       if(thissize > goalsize){
        break;
        }
       thisbin++;
      }
      batqt.push_back(thisbin);
      xsatqt.push_back(h_Nbkg->GetBinCenter(thisbin));
     }

    log<<"       Target Eventcount: "<<goalsize<<" = fullsize/4 = "<<fullsize<<"/4 \n";
     log<<boost::format("   Threshold blo bhi (xlo,xhi) Int(blo,bhi) Int(blo,bhi+1) Int(blo,bhi-1)\n");

    // find average purity over range
    // must weight each purity bin by nr. events in bin
    for(int n=0; n<nthreshs; ++n){
     int nbins = batqt.at(n) - batthresh.at(n);
     //std::cout<<nbins<<" "<<batthresh.at(n)<<" "<<batqt.at(n)<<std::endl;
     Double_t sumpurs, sumweights;
     sumpurs = 0.;
     sumweights = 0.;
     for(int o=0; o<nbins+1; ++o){
      int thisbin = batthresh.at(n) + o;
      int thispoint = thisbin - 1;  // bin nr = point nr + 1
      purity_background->GetPoint(thispoint, pointx,pointy);
      sumpurs += pointy*h_Nbkg->GetBinContent(thisbin);
      sumweights += h_Nbkg->GetBinContent(thisbin);
      //std::cout<<" "<<thispoint<<"|"<<pointy<<"|"<<h_Nbkg->GetBinContent(thisbin)<<" "<<std::endl;;
     }
     //std::cout<<std::endl;
     //std::cout<<sumpurs/sumweights<<std::endl<<std::endl;;
     avgpur.push_back( sumpurs/sumweights );
    }
     log_latex<<"\\begin{tabular}{r|r|r|r|r|r|r|r}\n";
     log_latex<<boost::format("\\multicolumn{2}{c|}{%8s} & \\multicolumn{2}{c|}{%15s} & \\multicolumn{2}{c|}{%7s} & \\multicolumn{2}{c|}{%7s} \\\\ \\hline \\hline  \n") % ptrange % cutname % isovar % bwidth  ;
     log_latex<<boost::format("   %10s & %5s & %5s & %10s & %5s & %8s & %15s & %10s  \\\\  \\hline \n")
      % "Threshold" 
      % "x lo" % "x hi" 
      % "avg purity"
      % "err \\%" 
      % "evts. tot." 
      % "evts. > x lo" 
      % "evts in rng." ;

     ///log_latex<<"\\begin{tabular}{r|r|r|r|r}\n";
     ///log_latex<<boost::format("%8s & \\multicolumn{2}{c}{%15s} & %7s & %7s \\\\  \n \\hline \\hline \n") % ptrange % cutname % isovar % bwidth  ;
     ///log_latex<<boost::format("   %10s & %5s & %5s & %10s & %5s \\\\ \n \\hline \n")
     /// % "Threshold" 
     /// % "x lo" % "x hi" 
     /// % "avg purity"
     /// % "err \\%" ;
    for(int n=0; n<nthreshs; ++n){
     log<<boost::format("    %7.2f %3i %3i (%2.1f,%1.2f) %10.2f %10.2f %10.2f  \n")
      % thresholds.at(n) % batthresh.at(n) %batqt.at(n)
      % xsatthresh.at(n) % xsatqt.at(n) 
      % h_Nbkg->Integral(batthresh.at(n),batqt.at(n))
      % h_Nbkg->Integral(batthresh.at(n),batqt.at(n)+1)
      % h_Nbkg->Integral(batthresh.at(n),batqt.at(n)-1) ;

     Double_t nrevents, errevents, pcterr;
     nrevents = h_Nbkg->IntegralAndError(batthresh.at(n),batqt.at(n),errevents);
     pcterr = errevents/nrevents;
     log_latex<<boost::format("   %10.2f & %5.2f & %5.2f & %10.4f &  %5.2f &  %8.1f & %15.1f & %10.1f  \\\\  \n")
      % thresholds.at(n) 
      % h_Nbkg->GetBinLowEdge(h_Nbkg->FindBin(xsatthresh.at(n))) % h_Nbkg->GetBinLowEdge(h_Nbkg->FindBin(xsatqt.at(n) ))
      //% xsatthresh.at(n) % xsatqt.at(n) 
      % avgpur.at(n)
      % (pcterr*100) 
      % fullsize 
      % h_Nbkg->Integral(batthresh.at(n),-1)
      % h_Nbkg->Integral(batthresh.at(n),batqt.at(n));

     ///log_latex<<boost::format("   %10.2f & %5.2f & %5.2f & %7.3f &  %5.2f  \\\\  \n")
     /// % thresholds.at(n) 
     /// % xsatthresh.at(n) % xsatqt.at(n) 
     /// % avgpur.at(n)
     /// % (pcterr*100) ;
    }
     log_latex<<"\\hline \n  \\end{tabular}\n";

     //-----------------------------------------------------
     // all set, now to start thinking about plotting
     //Make lower bound lines (purity)
     Double_t frac = 1./nthreshs;
     TLine *lgb_lo0 = new TLine(xsatthresh.at(0), 0*frac, xsatthresh.at(0), 1*frac);
     TLine *lgb_lo1 = new TLine(xsatthresh.at(1), 1*frac, xsatthresh.at(1), 2*frac);
     TLine *lgb_lo2 = new TLine(xsatthresh.at(2), 2*frac, xsatthresh.at(2), 3*frac);
     TLine *lgb_lo3 = new TLine(xsatthresh.at(3), 3*frac, xsatthresh.at(3), 4*frac);
     TLine *lgb_lo4 = new TLine(xsatthresh.at(4), 4*frac, xsatthresh.at(4), 5*frac);
     TLine *lgc_lo0 = new TLine(xsatthresh.at(0), 0*frac, xsatthresh.at(0), 1*frac);
     TLine *lgc_lo1 = new TLine(xsatthresh.at(1), 1*frac, xsatthresh.at(1), 2*frac);
     TLine *lgc_lo2 = new TLine(xsatthresh.at(2), 2*frac, xsatthresh.at(2), 3*frac);
     TLine *lgc_lo3 = new TLine(xsatthresh.at(3), 3*frac, xsatthresh.at(3), 4*frac);
     TLine *lgc_lo4 = new TLine(xsatthresh.at(4), 4*frac, xsatthresh.at(4), 5*frac);

     lgb_lo0->SetLineColor(1);
     lgb_lo1->SetLineColor(1);
     lgb_lo2->SetLineColor(1);
     lgb_lo3->SetLineColor(1);
     lgb_lo4->SetLineColor(1);
     lgc_lo0->SetLineColor(2);
     lgc_lo1->SetLineColor(3);
     lgc_lo2->SetLineColor(4);
     lgc_lo3->SetLineColor(5);
     lgc_lo4->SetLineColor(6);

     lgb_lo0->SetLineWidth(4);
     lgb_lo1->SetLineWidth(4);
     lgb_lo2->SetLineWidth(4);
     lgb_lo3->SetLineWidth(4);
     lgb_lo4->SetLineWidth(4);
     lgc_lo0->SetLineWidth(2);
     lgc_lo1->SetLineWidth(2);
     lgc_lo2->SetLineWidth(2);
     lgc_lo3->SetLineWidth(2);
     lgc_lo4->SetLineWidth(2);

     //Make upper bound lines (purity)
     TLine *lgb_hi0 = new TLine(xsatqt.at(0), 0*frac, xsatqt.at(0), 1*frac);
     TLine *lgb_hi1 = new TLine(xsatqt.at(1), 1*frac, xsatqt.at(1), 2*frac);
     TLine *lgb_hi2 = new TLine(xsatqt.at(2), 2*frac, xsatqt.at(2), 3*frac);
     TLine *lgb_hi3 = new TLine(xsatqt.at(3), 3*frac, xsatqt.at(3), 4*frac);
     TLine *lgb_hi4 = new TLine(xsatqt.at(4), 4*frac, xsatqt.at(4), 5*frac);
     TLine *lgc_hi0 = new TLine(xsatqt.at(0), 0*frac, xsatqt.at(0), 1*frac);
     TLine *lgc_hi1 = new TLine(xsatqt.at(1), 1*frac, xsatqt.at(1), 2*frac);
     TLine *lgc_hi2 = new TLine(xsatqt.at(2), 2*frac, xsatqt.at(2), 3*frac);
     TLine *lgc_hi3 = new TLine(xsatqt.at(3), 3*frac, xsatqt.at(3), 4*frac);
     TLine *lgc_hi4 = new TLine(xsatqt.at(4), 4*frac, xsatqt.at(4), 5*frac);

     lgb_hi0->SetLineColor(1);
     lgb_hi1->SetLineColor(1);
     lgb_hi2->SetLineColor(1);
     lgb_hi3->SetLineColor(1);
     lgb_hi4->SetLineColor(1);
     lgc_hi0->SetLineColor(2);
     lgc_hi1->SetLineColor(3);
     lgc_hi2->SetLineColor(4);
     lgc_hi3->SetLineColor(5);
     lgc_hi4->SetLineColor(6);

     lgb_hi0->SetLineWidth(4);
     lgb_hi1->SetLineWidth(4);
     lgb_hi2->SetLineWidth(4);
     lgb_hi3->SetLineWidth(4);
     lgb_hi4->SetLineWidth(4);
     lgc_hi0->SetLineWidth(2);
     lgc_hi1->SetLineWidth(2);
     lgc_hi2->SetLineWidth(2);
     lgc_hi3->SetLineWidth(2);
     lgc_hi4->SetLineWidth(2);

     lgc_hi0->SetLineStyle(2);
     lgc_hi1->SetLineStyle(2);
     lgc_hi2->SetLineStyle(2);
     lgc_hi3->SetLineStyle(2);
     lgc_hi4->SetLineStyle(2);

     //Make avg purity horizontal lines
     TLine *lgb_pur0 = new TLine(xsatthresh.at(0), avgpur.at(0), xsatqt.at(0), avgpur.at(0));
     TLine *lgb_pur1 = new TLine(xsatthresh.at(1), avgpur.at(1), xsatqt.at(1), avgpur.at(1));
     TLine *lgb_pur2 = new TLine(xsatthresh.at(2), avgpur.at(2), xsatqt.at(2), avgpur.at(2));
     TLine *lgb_pur3 = new TLine(xsatthresh.at(3), avgpur.at(3), xsatqt.at(3), avgpur.at(3));
     TLine *lgb_pur4 = new TLine(xsatthresh.at(4), avgpur.at(4), xsatqt.at(4), avgpur.at(4));
     TLine *lgc_pur0 = new TLine(xsatthresh.at(0), avgpur.at(0), xsatqt.at(0), avgpur.at(0));
     TLine *lgc_pur1 = new TLine(xsatthresh.at(1), avgpur.at(1), xsatqt.at(1), avgpur.at(1));
     TLine *lgc_pur2 = new TLine(xsatthresh.at(2), avgpur.at(2), xsatqt.at(2), avgpur.at(2));
     TLine *lgc_pur3 = new TLine(xsatthresh.at(3), avgpur.at(3), xsatqt.at(3), avgpur.at(3));
     TLine *lgc_pur4 = new TLine(xsatthresh.at(4), avgpur.at(4), xsatqt.at(4), avgpur.at(4));

     lgb_pur0->SetLineColor(1);
     lgb_pur1->SetLineColor(1);
     lgb_pur2->SetLineColor(1);
     lgb_pur3->SetLineColor(1);
     lgb_pur4->SetLineColor(1);
     //lgb_pur0->SetLineColor(2);
     //lgb_pur1->SetLineColor(3);
     //lgb_pur2->SetLineColor(4);
     //lgb_pur3->SetLineColor(5);
     //lgb_pur4->SetLineColor(6);
     lgc_pur0->SetLineColor(2);
     lgc_pur1->SetLineColor(3);
     lgc_pur2->SetLineColor(4);
     lgc_pur3->SetLineColor(5);
     lgc_pur4->SetLineColor(6);

     lgb_pur0->SetLineWidth(4);
     lgb_pur1->SetLineWidth(4);
     lgb_pur2->SetLineWidth(4);
     lgb_pur3->SetLineWidth(4);
     lgb_pur4->SetLineWidth(4);
     lgc_pur0->SetLineWidth(2);
     lgc_pur1->SetLineWidth(2);
     lgc_pur2->SetLineWidth(2);
     lgc_pur3->SetLineWidth(2);
     lgc_pur4->SetLineWidth(2);

     //lgc_pur0->SetLineStyle(2);
     //lgc_pur1->SetLineStyle(2);
     //lgc_pur2->SetLineStyle(2);
     //lgc_pur3->SetLineStyle(2);
     //lgc_pur4->SetLineStyle(2);

     //-----------------------------------------------------
     Double_t themax = 0 ;
     themax = std::max(themax, h_Nsig->GetMaximum());
     themax = std::max(themax, h_Nbkg->GetMaximum());
     themax = std::max(themax, h_Deno->GetMaximum());

     //Make lower bound lines (hist)
     Double_t logmax;
     Double_t logmin;
     logmax = std::log(themax);
     logmin = std::log(1);
     Double_t spacing = (logmax-logmin)/nthreshs;
     //std::cout<<spacing<<std::endl;

     //Double_t fifmax = themax/5.;
     TLine *lhb_lo0 = new TLine(xsatthresh.at(0), exp(logmin+0*spacing), xsatthresh.at(0), exp(logmin+1*spacing));
     TLine *lhb_lo1 = new TLine(xsatthresh.at(1), exp(logmin+1*spacing), xsatthresh.at(1), exp(logmin+2*spacing));
     TLine *lhb_lo2 = new TLine(xsatthresh.at(2), exp(logmin+2*spacing), xsatthresh.at(2), exp(logmin+3*spacing));
     TLine *lhb_lo3 = new TLine(xsatthresh.at(3), exp(logmin+3*spacing), xsatthresh.at(3), exp(logmin+4*spacing));
     TLine *lhb_lo4 = new TLine(xsatthresh.at(4), exp(logmin+4*spacing), xsatthresh.at(4), exp(logmin+5*spacing));
     TLine *lhc_lo0 = new TLine(xsatthresh.at(0), exp(logmin+0*spacing), xsatthresh.at(0), exp(logmin+1*spacing));
     TLine *lhc_lo1 = new TLine(xsatthresh.at(1), exp(logmin+1*spacing), xsatthresh.at(1), exp(logmin+2*spacing));
     TLine *lhc_lo2 = new TLine(xsatthresh.at(2), exp(logmin+2*spacing), xsatthresh.at(2), exp(logmin+3*spacing));
     TLine *lhc_lo3 = new TLine(xsatthresh.at(3), exp(logmin+3*spacing), xsatthresh.at(3), exp(logmin+4*spacing));
     TLine *lhc_lo4 = new TLine(xsatthresh.at(4), exp(logmin+4*spacing), xsatthresh.at(4), exp(logmin+5*spacing));

     lhb_lo0->SetLineColor(1);
     lhb_lo1->SetLineColor(1);
     lhb_lo2->SetLineColor(1);
     lhb_lo3->SetLineColor(1);
     lhb_lo4->SetLineColor(1);
     lhc_lo0->SetLineColor(2);
     lhc_lo1->SetLineColor(3);
     lhc_lo2->SetLineColor(4);
     lhc_lo3->SetLineColor(5);
     lhc_lo4->SetLineColor(6);

     lhb_lo0->SetLineWidth(4);
     lhb_lo1->SetLineWidth(4);
     lhb_lo2->SetLineWidth(4);
     lhb_lo3->SetLineWidth(4);
     lhb_lo4->SetLineWidth(4);
     lhc_lo0->SetLineWidth(2);
     lhc_lo1->SetLineWidth(2);
     lhc_lo2->SetLineWidth(2);
     lhc_lo3->SetLineWidth(2);
     lhc_lo4->SetLineWidth(2);

     //Make upper bound lines (hist)
     TLine *lhb_hi0 = new TLine(xsatqt.at(0), exp(logmin+0*spacing), xsatqt.at(0), exp(logmin+1*spacing));
     TLine *lhb_hi1 = new TLine(xsatqt.at(1), exp(logmin+1*spacing), xsatqt.at(1), exp(logmin+2*spacing));
     TLine *lhb_hi2 = new TLine(xsatqt.at(2), exp(logmin+2*spacing), xsatqt.at(2), exp(logmin+3*spacing));
     TLine *lhb_hi3 = new TLine(xsatqt.at(3), exp(logmin+3*spacing), xsatqt.at(3), exp(logmin+4*spacing));
     TLine *lhb_hi4 = new TLine(xsatqt.at(4), exp(logmin+4*spacing), xsatqt.at(4), exp(logmin+5*spacing));
     TLine *lhc_hi0 = new TLine(xsatqt.at(0), exp(logmin+0*spacing), xsatqt.at(0), exp(logmin+1*spacing));
     TLine *lhc_hi1 = new TLine(xsatqt.at(1), exp(logmin+1*spacing), xsatqt.at(1), exp(logmin+2*spacing));
     TLine *lhc_hi2 = new TLine(xsatqt.at(2), exp(logmin+2*spacing), xsatqt.at(2), exp(logmin+3*spacing));
     TLine *lhc_hi3 = new TLine(xsatqt.at(3), exp(logmin+3*spacing), xsatqt.at(3), exp(logmin+4*spacing));
     TLine *lhc_hi4 = new TLine(xsatqt.at(4), exp(logmin+4*spacing), xsatqt.at(4), exp(logmin+5*spacing));

     lhb_hi0->SetLineColor(1);
     lhb_hi1->SetLineColor(1);
     lhb_hi2->SetLineColor(1);
     lhb_hi3->SetLineColor(1);
     lhb_hi4->SetLineColor(1);
     lhc_hi0->SetLineColor(2);
     lhc_hi1->SetLineColor(3);
     lhc_hi2->SetLineColor(4);
     lhc_hi3->SetLineColor(5);
     lhc_hi4->SetLineColor(6);

     lhb_hi0->SetLineWidth(4);
     lhb_hi1->SetLineWidth(4);
     lhb_hi2->SetLineWidth(4);
     lhb_hi3->SetLineWidth(4);
     lhb_hi4->SetLineWidth(4);
     lhc_hi0->SetLineWidth(2);
     lhc_hi1->SetLineWidth(2);
     lhc_hi2->SetLineWidth(2);
     lhc_hi3->SetLineWidth(2);
     lhc_hi4->SetLineWidth(2);

     lhc_hi0->SetLineStyle(2);
     lhc_hi1->SetLineStyle(2);
     lhc_hi2->SetLineStyle(2);
     lhc_hi3->SetLineStyle(2);
     lhc_hi4->SetLineStyle(2);
     //-----------------------------------------------------


     //-----------------------------------------------------
     //Draw Histograms
     TLegend *meg = new TLegend(0.4,0.6,0.88,0.88);
     //meg->SetTextSize(0.04) ;
     meg->SetFillColor(0); meg->SetShadowColor(0);meg->SetBorderSize(2);
     meg->SetTextFont(22.);
     meg->AddEntry(h_Nsig,"Signal","l");
     meg->AddEntry(h_Nsig_GJ,"Signal (GJ MC)","l");
     meg->AddEntry(h_Nsig_QCD,"Signal (QCD MC)","l");
     meg->AddEntry(h_Nbkg,"Background","l");
     meg->AddEntry(h_Nbkg_GJ,"Background (GJ MC)","l");
     meg->AddEntry(h_Nbkg_QCD,"Background (QCD MC)","l");
     meg->AddEntry(h_Deno,"Denominator","l");
     meg->AddEntry(h_Deno_GJ,"Denominator (GJ MC)","l");
     meg->AddEntry(h_Deno_QCD,"Denominator (QCD MC)","l");
     
     TString leg_h0;  leg_h0.Form("Purity > %0.2f (%2.1f-%2.1f)", thresholds.at(0), xsatthresh.at(0), xsatqt.at(0));
     TString leg_h1;  leg_h1.Form("Purity > %0.2f (%2.1f-%2.1f)", thresholds.at(1), xsatthresh.at(1), xsatqt.at(1));
     TString leg_h2;  leg_h2.Form("Purity > %0.2f (%2.1f-%2.1f)", thresholds.at(2), xsatthresh.at(2), xsatqt.at(2));
     TString leg_h3;  leg_h3.Form("Purity > %0.2f (%2.1f-%2.1f)", thresholds.at(3), xsatthresh.at(3), xsatqt.at(3));
     TString leg_h4;  leg_h4.Form("Purity > %0.2f (%2.1f-%2.1f)", thresholds.at(4), xsatthresh.at(4), xsatqt.at(4));

     TLegend *neg = new TLegend(0.15,0.5,0.4,0.75);
     //meg->SetTextSize(0.04) ;
     neg->SetFillColor(0); neg->SetShadowColor(0);neg->SetBorderSize(2);
     neg->SetTextFont(22.);
     neg->AddEntry(lhc_lo0,leg_h0,"l");
     neg->AddEntry(lhc_lo1,leg_h1,"l");
     neg->AddEntry(lhc_lo2,leg_h2,"l");
     neg->AddEntry(lhc_lo3,leg_h3,"l");
     neg->AddEntry(lhc_lo4,leg_h4,"l");

     h_Nsig->SetTitle(cut);
     h_Nsig->SetXTitle(h_Nsig->GetTitle());
     h_Nsig->SetYTitle("Events ");
     h_Nsig->SetMaximum(1000*themax);
     h_Nsig->SetMinimum(1);

     h_Nsig->Draw("hist");
     h_Nsig_GJ->Draw("hist,same");
     h_Nsig_QCD->Draw("hist,same");
     h_Nbkg->Draw("hist,same");
     h_Nbkg_GJ->Draw("hist,same");
     h_Nbkg_QCD->Draw("hist,same");
     h_Deno->Draw("hist,same");
     h_Deno_GJ->Draw("hist,same");
     h_Deno_QCD->Draw("hist,same");

     meg->SetHeader("photon p_{T}: "+ptrange);
     meg->Draw();
     if(dolines){
      neg->Draw();
     }
     title->DrawTextNDC(0.17,0.87,"CMS");
     extra->DrawTextNDC(0.17,0.81,"Preliminary");
     lumi->DrawTextNDC(0.9,0.91,"2.32 /fb (13 TeV)");

     if(dolines){
      lhb_lo0->Draw();
      lhb_lo1->Draw();
      lhb_lo2->Draw();
      lhb_lo3->Draw();
      lhb_lo4->Draw();
      
      lhb_hi0->Draw();
      lhb_hi1->Draw();
      lhb_hi2->Draw();
      lhb_hi3->Draw();
      lhb_hi4->Draw();

      lhc_lo0->Draw();
      lhc_lo1->Draw();
      lhc_lo2->Draw();
      lhc_lo3->Draw();
      lhc_lo4->Draw();
      
      lhc_hi0->Draw();
      lhc_hi1->Draw();
      lhc_hi2->Draw();
      lhc_hi3->Draw();
      lhc_hi4->Draw();
     }

     gPad->SetLogy();

     canvas->SaveAs(outpath+"/Histos_"+isovar+"_"+ptrange+"_"+cut+rebin+xn+".pdf");
     canvas->SaveAs(wwwpath+"/pdf/"+ptrange+"/"+isovar+"/"+cut+lines+"/Histos_"+isovar+"_"+ptrange+"_"+cut+rebin+xn+".pdf");
     canvas->SaveAs(wwwpath+"/png/"+ptrange+"/"+isovar+"/"+cut+lines+"/Histos_"+isovar+"_"+ptrange+"_"+cut+rebin+xn+".png");
     canvas->Clear();
     gPad->SetLogy(kFALSE);
     //-----------------------------------------------------
     //-----------------------------------------------------
     //Draw Purity
     TLegend *leg = new TLegend(0.5,0.75,0.88,0.88);
     leg->SetTextSize(0.04) ;
     leg->SetFillColor(0); leg->SetShadowColor(0);leg->SetBorderSize(0);
     leg->SetTextFont(22.);
     leg->AddEntry(purity_signal,"Signal","lep");
     leg->AddEntry(purity_background,"Background","lep");

     float xmin ; //= 0.;
     float xmax ; //= 25.;
     xmin = h_Nsig->GetXaxis()->GetXmin();
     xmax = h_Nsig->GetXaxis()->GetXmax();
     TLine *lowline = new TLine(xmin,0,xmax,0);
     TLine *hiline = new TLine(xmin,1,xmax,1);
     lowline->SetLineWidth(1); lowline->SetLineColor(1); lowline->SetLineStyle(3);         
     hiline->SetLineWidth(1); hiline->SetLineColor(1); hiline->SetLineStyle(3);         

     TH1F *hframe = canvas->DrawFrame(xmin,-0.05,xmax,1.4,"");
     lowline->Draw();
     hiline->Draw();
     title->DrawTextNDC(0.17,0.87,"CMS");
     extra->DrawTextNDC(0.17,0.81,"Preliminary");
     lumi->DrawTextNDC(0.9,0.91,"2.32 /fb (13 TeV)");
     hframe->SetTitle(cut);
     hframe->SetXTitle(isovar);
     hframe->SetYTitle("Purity");
     
     // draw points
     purity_signal->Draw("P");
     purity_background->Draw("P");
     leg->SetHeader("photon p_{T}: "+ptrange);
     leg->Draw();

     //canvas->SaveAs(outpath+"/Purity_"+isovar+"_"+ptrange+"_"+cut+"_"+rebin+xn+".pdf");

     if(dolines){
      lgb_lo0->Draw();
      lgb_lo1->Draw();
      lgb_lo2->Draw();
      lgb_lo3->Draw();
      lgb_lo4->Draw();
      
      lgb_hi0->Draw();
      lgb_hi1->Draw();
      lgb_hi2->Draw();
      lgb_hi3->Draw();
      lgb_hi4->Draw();
      
      lgc_lo0->Draw();
      lgc_lo1->Draw();
      lgc_lo2->Draw();
      lgc_lo3->Draw();
      lgc_lo4->Draw();
      
      lgc_hi0->Draw();
      lgc_hi1->Draw();
      lgc_hi2->Draw();
      lgc_hi3->Draw();
      lgc_hi4->Draw();

      lgb_pur0->Draw();
      lgb_pur1->Draw();
      lgb_pur2->Draw();
      lgb_pur3->Draw();
      lgb_pur4->Draw();
      lgc_pur0->Draw();
      lgc_pur1->Draw();
      lgc_pur2->Draw();
      lgc_pur3->Draw();
      lgc_pur4->Draw();
     }
     
     canvas->SaveAs(outpath+"/Purity_"+isovar+"_"+ptrange+"_"+cut+rebin+xn+".pdf");
     canvas->SaveAs(wwwpath+"/pdf/"+ptrange+"/"+isovar+"/"+cut+lines+"/Purity_"+isovar+"_"+ptrange+"_"+cut+rebin+xn+".pdf");
     canvas->SaveAs(wwwpath+"/png/"+ptrange+"/"+isovar+"/"+cut+lines+"/Purity_"+isovar+"_"+ptrange+"_"+cut+rebin+xn+".png");

     canvas->Clear();
     //-----------------------------------------------------

     // clean your room!
     h_Nsig->Delete();
     h_Nsig_GJ->Delete();
     h_Nsig_QCD->Delete();
     h_Nbkg->Delete();
     h_Nbkg_GJ->Delete();
     h_Nbkg_QCD->Delete();
     h_Deno->Delete();
     h_Deno_GJ->Delete();
     h_Deno_QCD->Delete();
    }
   log<<"--------------------------------------\n";
   log_latex<<"--------------------------------------\n";
   }
  }
 }
 log.close();
 log_latex.close();
}
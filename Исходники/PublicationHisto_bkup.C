void PublicationHisto(TString config=""){
    //gROOT->SetStyle("Plain"); gROOT->ForceStyle();
    gROOT->ProcessLine(".x /home/aran/.rootlogon.C");
    gStyle->SetPadBottomMargin(.160); // Need this for subscripts
    gStyle->SetPadTopMargin(.08);
    
    TEnv *params = new TEnv("PubHisto");
    params->ReadFile (config, kEnvChange);

    TString type=params->GetValue("Histo.Type", "PublicationHisto");
    if (type != "PublicationHisto"){
	printf(" Must have Histo.Type: PublicationHisto in config file");
	return;
    }
    // Fetch the histos from the different files:
    TString hname=params->GetValue("Histo.Name", "BOGUSNAME");
    TObjArray sameHistos;
    if (hname == "3"){// ok this means we want to add 3 histos
	TString h1=params->GetValue("Histo.1.Name", "BOGUS_H1");
	TString h2=params->GetValue("Histo.2.Name", "BOGUS_H2");
	TString h3=params->GetValue("Histo.3.Name", "BOGUS_H3");
	printf("Adding histos: %s, %s, %s \n",h1.Data(),h2.Data(), h3.Data());
	TObjArray sameHistos = GetThreeSameHistos(h1,h2,h3,params);
    } else {// normal case
	TObjArray sameHistos = GetSameHistos(hname,params);    
    }

    // Plot them:
    printf (" Found %3i histos \n",sameHistos.GetEntriesFast());
    TCanvas *c1 = new TCanvas("c1","PubHist");
    PlotPubHisto(sameHistos,params);
    TString outfile=params->GetValue("Output.File", "dummy.eps");
    c1->SaveAs(outfile.Data());
}
	void CreateDrawAndSaveHistogramFWHM(TH1* &histo, TString outputdir, TString outputname, bool saveoutput, bool close, bool log=false){

		/** @brief  saves Histogramm as *.root and *.png and if wanted closes the histograms at the end
		*	@details This mehtod create a histogramm and save it as root and png file. If you choose close, the canvas is closed after the histogram was saved
		*/

		setPandaStyle();

//		gStyle->SetOptStat(1111);
		TString name = TString(histo->GetName());
		TString title = TString(histo->GetTitle());



		TCanvas * canvas = new TCanvas("c_"+name, title, 0,0,1500,1000);


		histo->Draw();

		//***** FWHM ******

		double max = histo->GetMaximum();

		int bin1 = histo->FindFirstBinAbove(max/2);
		int bin2 = histo->FindLastBinAbove(max/2);

		double lowerbin =  histo->GetBinCenter(bin1);
		double upperbin = histo->GetBinCenter(bin2) ;

		double FWHM =  upperbin - lowerbin;


		TPaveText * text = new TPaveText(0.2,1500,1,3500);
		TString name = TString::Format("FWHM  %.4f", FWHM);
		text->InsertText(name);
		text->SetFillColor(kWhite);
		text->SetTextFont(4);
		text->SetTextSize(30);
		text->SetTextAlign(12);
		text->Draw("SAME");

		if(log) canvas->SetLogy();

		PandaSmartLabel("L");


		if (saveoutput){
			canvas->Print(outputdir + "root-files/" + outputname + ".root");
			canvas->Print(outputdir + "png-files/" + outputname + ".png");
			canvas->Print(outputdir + "pdf-files/" + outputname + ".pdf");
		}

		if (close) canvas->Close();


	}
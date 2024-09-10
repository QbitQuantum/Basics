void ratioPlots( TCanvas* c1, TH1* h_r, TH1* h_i, 
		 string xTitle, string yTitle, 	string savePath, 
		 double fitMin=-100000, double fitMax=100000, bool doubleColFit=0 ){

	double xMaximum = h_r->GetXaxis()->GetBinUpEdge(h_r->GetXaxis()->GetLast());
	double xMinimum = h_r->GetXaxis()->GetBinLowEdge(h_r->GetXaxis()->GetFirst());
	double yMaximum;
	double yMinimum;

	h_i->Sumw2();
	h_r->Sumw2();

	TLine* line1 = new TLine(xMinimum,1,xMaximum,1);
	line1->SetLineColor(1);
	line1->SetLineWidth(2);
	line1->SetLineStyle(7);
	
	TF1* fpol1  = new TF1("fpol1", "pol1", fitMin, fitMax);	
	fpol1->SetLineColor(2);
	fpol1->SetLineWidth(3);
	fpol1->SetLineStyle(7);
	
	TH1* hRatio = (TH1*)h_r->Clone("clone_record");
	hRatio->Divide(h_i);
	yMaximum = hRatio->GetMaximum();
	yMinimum = hRatio->GetMinimum(0);
	hRatio->GetYaxis()->SetRangeUser(yMinimum/2.5,yMaximum+yMaximum/5);
	hRatio->SetXTitle(xTitle.c_str());
	hRatio->SetYTitle(yTitle.c_str());
	hRatio->SetLineColor(9); 
	hRatio->SetLineWidth(2); 
	hRatio->SetMarkerStyle(8); 
	hRatio->Draw("e");
	hRatio->Fit("fpol1", "L");
	line1->Draw("SAME");
	
	if(doubleColFit){
		double p0=fpol1->GetParameter(0);
		double p1=fpol1->GetParameter(1);
		double endPoint=double(fitMax*p1)+p0;
		double p1new=(endPoint-1)/(fitMax-fitMin);
		char fun[100], text[100];
		sprintf(fun,"x*(%f)+1",p1new);	
		sprintf(text,"Tangent: %f",p1new);	
		TF1* fnew = new TF1("fnew", fun, fitMin, fitMax);
		fnew->SetLineColor(2);
		fnew->SetLineWidth(3);
		fnew->Draw("SAME");
	
			
		TText* Title = new TText( fitMax/12, yMinimum, text);
		Title->SetTextColor(2);
		Title->SetTextSize(0.035);
		Title->Draw("SAME");
	}

	c1->SaveAs(savePath.c_str());
	c1->cd();
}
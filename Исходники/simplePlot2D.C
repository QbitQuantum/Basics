void decorate(TCanvas *can,TH2D &h, bool addLHC=true){

	TLatex * tex = new TLatex();
	tex->SetNDC();
	tex->SetTextFont(42);
	tex->SetLineWidth(2);
	tex->SetTextSize(0.03);
	tex->DrawLatex(0.32,0.93,"4.9 fb^{-1} (7 TeV) + 19.7 fb^{-1} (8 TeV) + 2.3 fb^{-1} (13 TeV)");
  	tex->SetTextFont(42);
	tex->SetTextSize(0.06);
	//if (!addLHC){
	//        tex->SetTextSize(0.04);
	//	tex->SetTextColor(kWhite);
  //		if (isPrelim)	tex->DrawLatex(0.155, 0.85, "#bf{CMS} #it{Preliminary}");
  //		else	tex->DrawLatex(0.155, 0.85, "#bf{CMS}");
	//} else {
		if (isPrelim)	{ 
	        	tex->SetTextSize(0.04);
			tex->DrawLatex(0.155, 0.85, "#bf{CMS} #it{Preliminary}");
		}
		else	tex->DrawLatex(0.14, 0.93, "#bf{CMS}");
	//}


	TGraph *SM = new TGraph();
	SM->SetPoint(0,1,1);
	SM->SetMarkerColor(kOrange);
	SM->SetMarkerStyle(33);
	SM->SetMarkerSize(4);
	SM->Draw("Psame");	

	TLegend *leg;
	if (addLHC) {
	  if (isPrelim) leg = new TLegend(0.14,0.56,0.4,0.83);
	  else leg = new TLegend(0.14,0.62,0.4,0.89);
	}
	else leg = new TLegend(0.52,0.84,0.78,0.89);
	leg->SetTextSize(0.042);
	leg->SetFillStyle(0);
	leg->SetTextColor(kWhite);
	leg->SetBorderSize(0);
	TGraph *gr = new TGraph(); gr->SetLineWidth(2); gr->SetMarkerStyle(34); gr->SetLineColor(kWhite); gr->SetMarkerColor(kWhite);
	TGraph *gr2 = new TGraph(); gr2->SetLineWidth(2); gr2->SetLineColor(kWhite); gr2->SetLineStyle(2); 
	gr->SetMarkerSize(2);
	if (addLHC){
	  leg->AddEntry(SM,"SM production","P");
	  leg->AddEntry(gr,"LHC best fit","P");
	  leg->AddEntry(gr, "68% CL","L");
	  leg->AddEntry(gr2,"95% CL","L");
	  leg->Draw();
	} else {
	  TLatex *lat = new TLatex();
	  lat->SetTextSize(0.04);
	  lat->SetTextColor(kWhite);
	  lat->DrawLatex(1.05,1.05,"SM production");
	}
	can->SetTicky();
	can->SetTickx();
	can->RedrawAxis();
}
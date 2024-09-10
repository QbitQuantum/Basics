void cmsPrel(double intLumi=-1, bool wide = false, long int sqrtS = 7) {

  TLatex *latex = new TLatex();
  latex->SetNDC();
  latex->SetTextSize(0.045);
  double wideLeftOffset = 0.19; //for JMEStyle, was 0.15 by default;
  
  latex->SetTextAlign(31); // align right
  latex->DrawLatex(wide ? 0.98 : 0.95, 0.96, ((TString)"#sqrt{s} = "+ sqrtS)+ " TeV");
  if (intLumi > 0.) {
    latex->SetTextAlign(11); // align left
    //latex->DrawLatex(wideLeftOffset,0.96,Form("CMS preliminary, %.2g nb^{-1}",intLumi));
    latex->DrawLatex(wide ? 0.06 : wideLeftOffset, 0.96,
		     //    Form(" ",intLumi));
		     //		     Form("CMS, %.2g pb^{-1}",intLumi));
		     //was		     Form("CMS preliminary, %.2g pb^{-1}",intLumi));
    Form("CMS preliminary, %.2g fb^{-1}",intLumi));
  }
  else if (intLumi==0) { // simulation
    latex->SetTextAlign(11); // align left
    latex->DrawLatex(wide ? 0.06 : wideLeftOffset, 0.96, "CMS simulation (Su12 QCD)");
  }
  else {
    latex->SetTextAlign(11); // align left
    //    latex->DrawLatex(wideLeftOffset,0.96,"CMS preliminary");
        latex->DrawLatex(wide ? 0.06 : wideLeftOffset,0.96,"CMS work in progress");
  }
} // cmsPrel
void cmsPrelim( double intLumi ){  TLatex latex;
	latex.SetNDC();
	latex.SetTextSize(0.04);

	latex.SetTextAlign(31); // align right
	latex.DrawLatex(0.9,0.96,Form("%.1f fb^{-1}, #sqrt{s} = 8 TeV",intLumi/1000));
	//  if (intLumi > 0.) {
	//    latex.SetTextAlign(31); // align right
	//    latex.DrawLatex(0.9,0.9,Form("#int #font[12]{L} dt = %.1f fb^{-1}",intLumi));
	//  }

	latex.SetTextAlign(11); // align left
	latex.DrawLatex(0.25,0.96,"CMS preliminary");
}
//	Originally Written by Conor Fitzpatrick
TPaveText* addLHCbLabel(TString footer, bool DATA){
	//
	TPaveText * label = new TPaveText(0.18, 0.73, 0.18, 0.88,"BRNDC");
	label->SetFillStyle(0);         //Transparent i.e. Opacity of 0 :D
	label->SetBorderSize(0);
	label->SetTextAlign(11);
	label->SetTextSize(Float_t(0.04));
	TText * labeltext = 0;
	TString labeltstring( "LHC#font[12]{b} 2011" );
	if( DATA ) labeltstring.Append( " Data" );
	if( !DATA ) labeltstring.Append( " Simulation" );
	labeltext = label->AddText( labeltstring );
	labeltext = label->AddText("#sqrt{s} = 7TeV");
	labeltext = label->AddText(footer);
	(void) labeltext;
	return label;
}
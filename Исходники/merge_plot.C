TPaveText* addLHCbLabel(TString footer){
	TPaveText * label = new TPaveText(0.70,0.12,0.9,0.32,"BRNDC");
	//TPaveText * label = new TPaveText(0.12, 0.58, 0.12, 0.43,"BRNDC");
	//label->SetFillColor(0);
	label->SetFillStyle(0);
	label->SetBorderSize(0);
	label->SetTextAlign(11);
	label->SetTextSize(Float_t(0.04));
	TText * labeltext = 0;
	labeltext = label->AddText("LHC#font[12]{b} 2011 Data");
	labeltext = label->AddText("#sqrt{s} = 7TeV");
	labeltext = label->AddText(footer);
	return label;
}
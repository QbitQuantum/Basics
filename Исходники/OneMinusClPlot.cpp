///
/// Draw a horizontal line at given p-value, put a
/// label on top of it stating the corresponding CL.
///
void OneMinusClPlot::drawCLguideLine(float pvalue)
{
	m_mainCanvas->cd();
	m_mainCanvas->Update();
	float ymin = gPad->GetUymin();
	float ymax = gPad->GetUymax();
	float xmin = gPad->GetUxmin();
	float xmax = gPad->GetUxmax();

	float labelPos = xmin+(xmax-xmin)*0.10;
	if ( arg->isQuickhack(2) ) labelPos = xmin+(xmax-xmin)*0.55;
  if ( arg->isQuickhack(23) ) labelPos = xmin+(xmax-xmin)*0.8;
	float labelPosYmin = 0;
	float labelPosYmax = 0;

	if ( arg->plotlog ) {
		labelPosYmin = pvalue;
		labelPosYmax = labelPosYmin * 2.;
	}
	else {
		labelPosYmin = pvalue + 0.02;
		labelPosYmax = labelPosYmin + 0.05;
	}

	TPaveText *t = new TPaveText(labelPos, labelPosYmin, labelPos+(xmax-xmin)*0.5, labelPosYmax, "BR");
	t->SetBorderSize(0);
	t->SetFillStyle(0);
	t->SetTextAlign(12);
	t->SetTextFont(font);
	t->SetTextSize(labelsize);
	t->AddText(Form("%.1f%%",(1.-pvalue)*100.));
	t->Draw();

	TLine* l = new TLine(xmin, pvalue, xmax, pvalue);
	l->SetLineWidth(1);
	l->SetLineColor(kBlack);
	l->SetLineStyle(kDotted);
	l->Draw();
}
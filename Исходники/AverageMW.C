void MakeLabels( TH2F* frame )
{
   // write labels
   TString labels[] = { "CDF-I", "D0-I", "CDF-II", "LEP-II", "NuTeV" };

   TLatex* text = new TLatex;
   text->SetTextAlign( 32 );
   text->SetTextSize( frame->GetLabelSize( "Y" ) );
   Float_t dy = (frame->GetYaxis()->GetXmax() - frame->GetYaxis()->GetXmin())/5.;
   Float_t dx = frame->GetXaxis()->GetXmax() - frame->GetXaxis()->GetXmin();
   Float_t yy = frame->GetYaxis()->GetXmin() - 0.5*dy;
   for (Int_t i=5-1; i>=0; i--) {
      text->SetTextColor( 1 );
      text->DrawLatex( frame->GetXaxis()->GetXmin(), yy += dy, labels[i] + "  " );
   }
   
   frame->AppendPad();
}
void PaintOverflow(TH1 *h)
{
   // This function paint the histogram h with an extra bin for overflows

   char* name  = h->GetName();
   char* title = h->GetTitle();
   Int_t nx    = h->GetNbinsX()+1;
   Double_t x1 = h->GetBinLowEdge(1);
   Double_t bw = h->GetBinWidth(nx);
   Double_t x2 = h->GetBinLowEdge(nx)+bw;

   // Book a temporary histogram having ab extra bin for overflows
   TH1F *htmp = new TH1F(name, title, nx, x1, x2);

   // Fill the new hitogram including the extra bin for overflows
   for (Int_t i=1; i<=nx; i++) {
      htmp->Fill(htmp->GetBinCenter(i), h->GetBinContent(i));
   }

   // Fill the underflows
   htmp->Fill(x1-1, h->GetBinContent(0));

   // Restore the number of entries
   htmp->SetEntries(h->GetEntries());

   // Draw the temporary histogram
   htmp->Draw();
   TText *t = new TText(x2-bw/2,h->GetBinContent(nx),"Overflow");
   t->SetTextAngle(90);
   t->SetTextAlign(12);
   t->SetTextSize(0.03);;
   t->Draw();
}
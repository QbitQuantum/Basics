//________________________________________________________
void GFHistManager::ColourStatsBoxes(GFHistArray *hists) const
{
  // colours stats boxes like hists' line colors and moves the next to each other
  if (!hists) return;
  Double_t x1 = fStatsX1, x2 = fStatsX2, y1 = fStatsY1, y2 = fStatsY2;
  for (Int_t iH = 0; iH < hists->GetEntriesFast(); ++iH) {
    TH1 *h = hists->At(iH);
    if (!h) continue;
    TObject *statObj = h->GetListOfFunctions()->FindObject("stats");
    if (statObj && statObj->InheritsFrom(TPaveStats::Class())) {
      TPaveStats *stats = static_cast<TPaveStats*>(statObj);
      stats->SetLineColor(hists->At(iH)->GetLineColor());
      stats->SetTextColor(hists->At(iH)->GetLineColor());
      stats->SetX1NDC(x1);
      stats->SetX2NDC(x2);
      stats->SetY1NDC(y1);
      stats->SetY2NDC(y2);
      y2 = y1 - 0.005; // shift down 2
      y1 = y2 - (fStatsY2 - fStatsY1); // shift down 1
      if (y1 < 0.) {
	y1 = fStatsY1; y2 = fStatsY2; // restart y-positions
	x2 = x1 - 0.005; // shift left 2
	x1 = x2 - (fStatsX2 - fStatsX1); // shift left 1
	if (x1 < 0.) { // give up, start again:
	  x1 = fStatsX1, x2 = fStatsX2, y1 = fStatsY1, y2 = fStatsY2;
	}
      }
    } else if (gStyle->GetOptStat() != 0) { // failure in case changed in list via TExec....
      this->Warning("ColourStatsBoxes", "No stats found for %s", hists->At(iH)->GetName());
    }
  }
}
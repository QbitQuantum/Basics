void TDSPMultiEcho::Draw(Option_t *o, Double_t x0, Double_t x1, UInt_t num) {
  TString opt = o;
  opt.ToLower();

  Ssiz_t pos;

  if ((pos = opt.Index("multi"))!= kNPOS) {
    opt.Remove(pos,5);
    TMultiGraph *m = MultiGraph(NULL,x0,x1,num);
    m->Draw(o);
    m->GetXaxis()->SetTitle("#tau / #mu s");
    gPad->Update();
    return;
  }
  TGraph *a = Graph(NULL,x0,x1,num);
  a->Draw(o);
  a->GetXaxis()->SetTitle("#tau / #mu s");
  gPad->Update();
}
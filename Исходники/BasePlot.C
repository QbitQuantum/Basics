void BasePlot::DrawLegend(Float_t x1, Float_t y1, TH1F*   hist, TString label, TString option) {
    TLegend* legend = new TLegend(x1, y1, x1 + _xoffset, y1 + _yoffset);

    legend->SetBorderSize(     0);
    legend->SetFillColor (     0);
    legend->SetTextAlign (    12);
    legend->SetTextFont  (_labelFont);
    legend->SetTextSize  (_legendTextSize);

    legend->AddEntry(hist, label.Data(), option.Data());

    legend->Draw();
}
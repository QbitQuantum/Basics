void DrawTree::setLegend(float xmin, float ymin, float xsize, float ysize,char* header) {
    _legend = new TLegend(xmin,ymin,xmin+xsize,ymin+ysize);
    _legend->SetTextAlign(12);
    _legend->SetTextColor(1);
    _legend->SetTextSize(0.03);
    _legend->SetFillStyle(0);
    _legend->SetFillColor(0);
    _legend->SetBorderSize(0);

    _legend->SetHeader(header);

}
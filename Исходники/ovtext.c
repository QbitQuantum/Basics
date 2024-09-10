TextOvComp::TextOvComp(istream& in, OverlayComp* parent) 
: OverlayComp(nil, parent) {
    _valid = GetParamList()->read_args(in, this); 

    /* correct font vertical position */
    PSFont* f = _gr->GetFont();
    float sep = 1 - (f ? f->GetLineHt() : 0);
    Transformer* t = _gr->GetTransformer();
    float dx = 0., dy = sep;

    if (t != nil) {
        float x0, y0, x1, y1;
        t->Transform(0., 0., x0, y0);
        t->Transform(0., sep, x1, y1);
        dx = x1 - x0;
        dy = y1 - y0;
    }
    _gr->Translate(dx, dy);
}
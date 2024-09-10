void TVizMapContext::PaintEmpty(PGks Gks) {
    Gks->SetBrush(TGksBrush::New(ColorLandscapeAbove));
    Gks->FillRect(-1, -1, Gks->GetWidth()+1, Gks->GetHeight()+1);
}
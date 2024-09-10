void __fastcall TEditTiffForm::Fog1Paint(TObject *Sender) {
//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
    TCanvas *c = Fog1->Canvas;
    c->Brush->Style = bsSolid;
    c->Brush->Color = clBtnFace;
    c->Rectangle(0, 0, Fog1->Width, Fog1->Height);

    // ti->DrawCenter(Fog1->Canvas, Fog1->Width / 2, Fog1->Height / 2, Fog1->Width - 4, Fog1->Height - 4);
    tb->DrawCenter(Fog1->Canvas, Fog1->Width / 2, Fog1->Height / 2, Fog1->Width - 4, Fog1->Height - 4);
}
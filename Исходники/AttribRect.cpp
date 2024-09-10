AttribRect::AttribRect ()
    : AttribView (BRect (0, 0, 148, 90), lstring (31, "Rectangles"))
{
    SetViewColor (LightGrey);
    lSlid = new Slider (BRect (8, 8, 140, 26), 60, lstring (310, "Pen Size"), 1, 50, 1, new BMessage ('ALpc'));
    AddChild (lSlid);
    fType = RECT_OUTFILL;
    fPenSize = 1;
    BBox *type = new BBox (BRect (18, 32, 130, 82), "type");
    type->SetLabel (lstring (311, "Type"));
    AddChild (type);
    BRect shape = BRect (3, 5, 27, 25);

    BWindow *picWindow = new BWindow (BRect (0, 0, 100, 100), "Temp Pic Window", B_BORDERED_WINDOW, uint32 (NULL), uint32 (NULL));
    BView *bg = new BView (BRect (0, 0, 100, 100), "Temp Pic View", uint32 (NULL), uint32 (NULL));
    picWindow->AddChild (bg);

    BPicture *p10;
    bg->BeginPicture (new BPicture);
    bg->SetLowColor (LightGrey);
    bg->FillRect (BRect (0, 0, 32, 32), B_SOLID_LOW);
    bg->SetLowColor (White);
    bg->FillRect (shape, B_SOLID_LOW);
    bg->StrokeRect (shape);
    p10 = bg->EndPicture();

    BPicture *p20;
    bg->BeginPicture (new BPicture);
    bg->SetLowColor (LightGrey);
    bg->FillRect (BRect (0, 0, 32, 32), B_SOLID_LOW);
    bg->SetHighColor (Black);
    bg->SetLowColor (White);
    bg->FillRect (shape, B_SOLID_LOW);
    p20 = bg->EndPicture();

    BPicture *p30;
    bg->BeginPicture (new BPicture);
    bg->SetLowColor (LightGrey);
    bg->FillRect (BRect (0, 0, 32, 32), B_SOLID_LOW);
    bg->SetHighColor (Black);
    bg->SetLowColor (White);
    bg->StrokeRect (shape);
    p30 = bg->EndPicture();

    BPicture *p11;
    bg->BeginPicture (new BPicture);
    bg->SetLowColor (DarkGrey);
    bg->FillRect (BRect (0, 0, 32, 32), B_SOLID_LOW);
    bg->SetHighColor (Black);
    bg->SetLowColor (White);
    bg->FillRect (shape, B_SOLID_LOW);
    bg->StrokeRect (shape);
    p11 = bg->EndPicture();

    BPicture *p21;
    bg->BeginPicture (new BPicture);
    bg->SetLowColor (DarkGrey);
    bg->FillRect (BRect (0, 0, 32, 32), B_SOLID_LOW);
    bg->SetHighColor (Black);
    bg->SetLowColor (White);
    bg->FillRect (shape, B_SOLID_LOW);
    p21 = bg->EndPicture();

    BPicture *p31;
    bg->BeginPicture (new BPicture);
    bg->SetLowColor (DarkGrey);
    bg->FillRect (BRect (0, 0, 32, 32), B_SOLID_LOW);
    bg->SetHighColor (Black);
    bg->SetLowColor (White);
    bg->StrokeRect (shape);
    p31 = bg->EndPicture();

    SetViewColor (LightGrey);
    delete picWindow;

    pT1 = new BPictureButton (BRect (4, 15, 34, 45), "APVt1", p10, p11, new BMessage ('pvT1'), B_TWO_STATE_BUTTON);
    pT2 = new BPictureButton (BRect (40, 15, 70, 45), "APVt2", p20, p21, new BMessage ('pvT2'), B_TWO_STATE_BUTTON);
    pT3 = new BPictureButton (BRect (76, 15, 106, 45), "APVt3", p30, p31, new BMessage ('pvT3'), B_TWO_STATE_BUTTON);
    type->AddChild (pT1);
    type->AddChild (pT2);
    type->AddChild (pT3);
    pT1->SetValue (B_CONTROL_ON);
    fCurrentProperty = 0;
}
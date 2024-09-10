BBitmap *bitmap (char *title)
{
	strcpy (title, "Grabbed");
	BBitmap *b = new BBitmap (BRect (0, 0, 127, 127), B_RGB_32_BIT, true);
	BView *v = new BView (BRect (0, 0, 127, 127), "bg", 0, 0);
	b->Lock();
	b->AddChild (v);
	rgb_color fg, bg;
	fg.red = 255; fg.green = 255; fg.blue = 255; fg.alpha = 255;
	bg.red = 0;   bg.green = 0;   bg.blue = 0;   bg.alpha = 127;
	v->SetHighColor (fg);
	v->SetLowColor (bg);
	v->FillRect (BRect (0, 0, 127, 127), B_MIXED_COLORS);
	v->Sync();
	b->RemoveChild (v);
	b->Unlock();
	delete v;
	return (b);
}
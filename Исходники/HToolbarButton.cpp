/***********************************************************
 * Make disable state picture.
 ***********************************************************/
BPicture*
HToolbarButton::MakeDisablePicture(BBitmap *in)
{
	HToolbar *toolbar = cast_as(Parent(),HToolbar);
	BRect buttonRect = toolbar->ButtonRect();
	
	BView *view = new BView(BRect(0,0,buttonRect.Width(),buttonRect.Height())
							,"offview",0,0);
	BBitmap *bitmap = new BBitmap(view->Bounds(), in->ColorSpace(), true);
	BPicture *pict;
	bitmap->AddChild(view);
	bitmap->Lock();

	view->BeginPicture(new BPicture); 
	view->SetHighColor(bgcolor);
	view->FillRect(view->Bounds());
	
	DrawString(view,fName.String(),false,false);
	
	view->SetDrawingMode(B_OP_BLEND); 
	
	DrawBitmap(view,in);
	
	pict = view->EndPicture();
	bitmap->Unlock();
	delete bitmap;
	return pict;
}
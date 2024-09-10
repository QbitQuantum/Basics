BBitmap* MainView::CreateIcon(const rgb_color colorIn)
{
	BRect rect(0, 0, 15, 15);
	BBitmap* toReturn = new BBitmap(rect, B_CMAP8, true);
	BView* drawing = new BView(rect, 
								"drawer", 
								B_FOLLOW_LEFT | B_FOLLOW_TOP,
								B_WILL_DRAW);
	if (!drawing || !toReturn) { return NULL; }	
	toReturn->AddChild(drawing);
	if (toReturn->Lock()) {
		drawing->SetHighColor(kWhite);
		drawing->FillRect(rect);
		drawing->SetHighColor(kBlack);
		drawing->SetPenSize(1);
		drawing->StrokeRect(rect);
		drawing->SetHighColor(colorIn);
		drawing->FillRect(rect.InsetBySelf(1, 1));
		drawing->Sync();
		toReturn->Unlock();			
	}
	toReturn->RemoveChild(drawing);
	delete drawing;
	return toReturn;
}
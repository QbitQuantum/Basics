/**
	Draws all spliters.	
*/
void SplitView::Draw(BRect update)
{
	BView *child;	
	for (int i = 0; i < CountChildren() -1; i++) {
		child = ChildAt(i);
		BRect frame = child->Frame();
		if (fLayout.Mode() == B_HORIZONTAL) {
			frame.left = frame.right+1;
			frame.right = frame.left + fLayout.Spacing().x-2;
		}
		else {
			frame.top = frame.bottom+1;
			frame.bottom = frame.top + fLayout.Spacing().y-2;
		}
		if (frame.Intersects(update))
			DrawSplitter(frame, child == fSelected && fDragged);		
	}
}
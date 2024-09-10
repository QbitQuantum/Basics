void TElementsSorter::Draw(BRect updateRect)
{
	PushState();

	//  Draw dummy header to the right of our rightmost TSorter
	TSorterContainer* sorter = static_cast<TSorterContainer*>(fSorterList->ItemAt( fSorterList->CountItems()-1) );
	if (sorter) {
		BRect bounds    = Bounds();
		bounds.bottom   = bounds.top + kSorterHeight;
		bounds.left     = sorter->Frame().right;

		if (updateRect.Intersects(bounds) ) {
			// Fill background
			SetHighColor(kBeGrey);
			FillRect(bounds);

			// Frame it
			BPoint endPt;
			SetHighColor(kWhite);
			MovePenTo(bounds.left, bounds.top+1);
			endPt.Set( bounds.right, bounds.top+1 );
			StrokeLine(endPt);

			SetHighColor(kMediumGrey);
			MovePenTo(bounds.left, bounds.bottom-1);
			endPt.Set( bounds.right, bounds.bottom-1 );
			StrokeLine(endPt);

			SetHighColor(kBlack);
			MovePenTo(bounds.left, bounds.top);
			endPt.Set( bounds.right, bounds.top );
			StrokeLine(endPt);
			MovePenTo(bounds.left, bounds.bottom);
			endPt.Set( bounds.right, bounds.bottom );
			StrokeLine(endPt);
		}
	}

	PopState();

}
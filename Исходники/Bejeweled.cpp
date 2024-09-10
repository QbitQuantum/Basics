void Bejeweled::Click(int x,int y) {
	if(!selectiona) { // start action
		selectiona = grid[x][y];
		selector->SetTranslation(float3(2*x,2*y,0.1));
	} else { // end action
		selectionb = grid[x][y];
		HideCaret();
		if(SwapAllowed(selectiona,selectionb)) {
			Swap(selectiona,selectionb);
		} else {
			SwapSwap(selectiona,selectionb);
		}
		Deselect();
	}
}
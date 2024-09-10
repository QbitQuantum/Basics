void BitmapMenuItem::Draw(void)
{
	BMenu* menu = Menu();
	if (menu) {
		BRect itemFrame = Frame();
		BRect bitmapFrame = itemFrame;
		bitmapFrame.InsetBy(2, 2); // account for 2-pixel margin
		
		menu->SetDrawingMode(B_OP_COPY);
		menu->SetHighColor(BKG_GREY);
		menu->FillRect(itemFrame);
		menu->DrawBitmap(&m_bitmap, bitmapFrame);
		
		if (IsSelected()) {
			// a nonstandard but simple way to draw highlights
			menu->SetDrawingMode(B_OP_INVERT);
			menu->SetHighColor(0,0,0);
			menu->FillRect(itemFrame);
		}
	}
}
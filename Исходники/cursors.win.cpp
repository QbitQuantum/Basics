Cursor::Cursor(fs::path imgPath, float hotSpotX, float hotSpotY) {
	sf::Image gif;
	if(!gif.loadFromFile(imgPath.string())) {
		std::string error = "Error loading cursor from " + imgPath.string();
		throw error;
	}
	// Calculate the AND and XOR masks
	HBITMAP cursorAnd = CreateCompatibleBitmap(GetDC(NULL), gif.getSize().x, gif.getSize().y);
	HBITMAP cursorXor = CreateCompatibleBitmap(GetDC(NULL), gif.getSize().x, gif.getSize().y);
	GetMaskBitmaps(gif, cursorAnd, cursorXor);

	ICONINFO iconinfo = {0};
	iconinfo.fIcon = FALSE;
	iconinfo.xHotspot = hotSpotX;
	iconinfo.yHotspot = hotSpotY;
	iconinfo.hbmMask = cursorAnd;
	iconinfo.hbmColor = cursorXor;

	HCURSOR hCursor = CreateIconIndirect(&iconinfo);
	if(hCursor == NULL) {
		std::string error = "Error creating cursor from " + imgPath.string();
		error += " (error code " + std::to_string(GetLastError()) + ")";
		throw error;
	}
	ptr = hCursor;
	DeleteObject(cursorAnd);
	DeleteObject(cursorXor);
}
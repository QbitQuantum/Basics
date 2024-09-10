void CGDALContainer::DrawImage(HDC hDC, double dWorldOriginX, double dWorldOriginY, uint index) {
	
	if (hDC == NULL) return;
	int		length	= geoTiffs.size();
	HDC		hDCMem	= CreateCompatibleDC(hDC);
	HBITMAP hMemBitmap;
	HBITMAP hbMask;
	HGDIOBJ oldObject = NULL;


	// have we got a device context?
	if (hDCMem) {
		// are we in range?
		if (index >= 0 && index < geoTiffs.size()) {
			
			// draw only if layer is uptodate
			if (geoTiffs[index]->isUptodate) {

				int currentBufferSize = geoTiffs[index]->getBufferSize();
				
				// create new DIBSection for drawing the layer in
				hMemBitmap = ::CreateDIBSection(hDCMem, geoTiffs[index]->getBitmapInfo(), DIB_RGB_COLORS, (void **)&buffer, NULL, 0);
				if (hMemBitmap) {
					
					// copy the layer data into the DIBSection
					// memcpy_s(void *dest, size_t numberOfElements, const void *src, size_t count);
					memcpy_s(this->buffer, currentBufferSize, geoTiffs[index]->getBytes(), currentBufferSize);
					
					// select the DIBSection into temp dc
					oldObject = SelectObject(hDCMem, hMemBitmap);

					// get the mask of the layer
					geoTiffs[index]->getMask(hbMask);

					// blt the drawn layer through the mask onto our real device context
					MaskBlt(hDC, geoTiffs[index]->getRelativeX(), geoTiffs[index]->getRelativeY(), width, height,
						hDCMem, 0, 0, hbMask, 0, 0,
						MAKEROP4(geoTiffs[index]->getRasterOperation(), 0x00AA0029)); // 0x00AA0029 == Destination
					
					// Select old object back into dc (one can not delete an object if it is in the dc)
					SelectObject(hDCMem, oldObject);

					// delete the now unselected object
					DeleteObject(hMemBitmap);
				}
			}
		}
		DeleteDC(hDCMem);
	}
}
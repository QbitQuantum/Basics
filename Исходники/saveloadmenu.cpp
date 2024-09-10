SaveDataWidget::SaveDataWidget(int slot, Gfx::Driver *gfx, SaveLoadMenuScreen *screen) :
		StaticLocationWidget(nullptr, nullptr, nullptr),
		_slot(slot),
		_screen(screen),
		_thumbWidth(StarkUserInterface->kThumbnailWidth),
		_thumbHeight(StarkUserInterface->kThumbnailHeight),
		_texture(gfx->createTexture()),
		_outline(gfx->createTexture()),
		_surfaceRenderer(gfx->createSurfaceRenderer()),
		_textDesc(gfx),
		_textTime(gfx),
		_isMouseHovered(false),
		_hasSave(false),
		_name() {
	// Load from the save data
	loadSaveDataElements();

	_textDesc.setColor(_textColor);
	_textDesc.setFont(FontProvider::kCustomFont, 3);

	_textTime.setColor(_textColor);
	_textTime.setFont(FontProvider::kCustomFont, 3);

	Graphics::PixelFormat pixelFormat = Gfx::Driver::getRGBAPixelFormat();
	uint32 outlineColor = pixelFormat.ARGBToColor(
			_outlineColor.a, _outlineColor.r, _outlineColor.g, _outlineColor.b
	);

	// Create the outline texture
	Graphics::Surface lineSurface;
	lineSurface.create(_thumbWidth, _thumbHeight, pixelFormat);
	lineSurface.drawThickLine(0, 0, _thumbWidth - 1, 0, 2, 2, outlineColor);
	lineSurface.drawThickLine(0, 0, 0, _thumbHeight - 1, 2, 2, outlineColor);
	lineSurface.drawThickLine(_thumbWidth - 2, 0, _thumbWidth - 2, _thumbHeight - 2, 2, 2, outlineColor);
	lineSurface.drawThickLine(0, _thumbHeight - 2, _thumbWidth - 2, _thumbHeight - 2, 2, 2, outlineColor);

	_outline->update(&lineSurface);
	lineSurface.free();

	// Set the position
	_thumbPos.x = 41 + (_slot % SaveLoadMenuScreen::_slotPerRow) * (_thumbWidth + 39);
	_thumbPos.y = 61 + (_slot % SaveLoadMenuScreen::_slotPerPage / SaveLoadMenuScreen::_slotPerColumn) * (_thumbHeight + 38);

	_textDescPos.x = _thumbPos.x;
	_textDescPos.y = _thumbPos.y + _thumbHeight + 2;

	_textTimePos.x = _thumbPos.x;
	_textTimePos.y = _textDescPos.y + 12;
}
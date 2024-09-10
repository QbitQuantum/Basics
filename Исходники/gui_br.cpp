	QuitDialogInputState_BR(Parallaction_br *vm, MenuInputHelper *helper) : MenuInputState("quitdialog", helper), _vm(vm) {
		_font = _vm->_dialogueFont;

		const char *question = "Do you really want to quit ?";
		const char *option = "Yes No";

		int questionW = _font->getStringWidth(question);
		int optionW = _font->getStringWidth(option);
		int w = MAX(questionW, optionW) + 30;

		_x = (640 - w) / 2;
		_y = 90;

		Graphics::Surface *surf = new Graphics::Surface;
		surf->create(w, 110, Graphics::PixelFormat::createFormatCLUT8());
		surf->fillRect(Common::Rect(0, 0, w, 110), 12);
		surf->fillRect(Common::Rect(10, 10, w-10, 100), 15);

		_font->setColor(0);
		int x = (w - questionW)/2;
		int y = 13;
		_font->drawString((byte *)surf->getBasePtr(x, y), surf->pitch, question);
		x = (w - optionW)/2;
		y = 13 + _font->height()*2;
		_font->drawString((byte *)surf->getBasePtr(x,y), surf->pitch, option);

		_obj = new GfxObj(kGfxObjTypeMenu, new SurfaceToFrames(surf), "quitdialog");
		assert(_obj);
	}
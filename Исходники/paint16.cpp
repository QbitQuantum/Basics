reg_t GfxPaint16::kernelDisplay(const char *text, int argc, reg_t *argv) {
	reg_t displayArg;
	TextAlignment alignment = SCI_TEXT16_ALIGNMENT_LEFT;
	int16 colorPen = -1, colorBack = -1, width = -1, bRedraw = 1;
	bool doSaveUnder = false;
	Common::Rect rect;
	reg_t result = NULL_REG;

	// Make a "backup" of the port settings (required for some SCI0LATE and
	// SCI01+ only)
	Port oldPort = *_ports->getPort();

	// setting defaults
	_ports->penMode(0);
	_ports->penColor(0);
	_ports->textGreyedOutput(false);
	// processing codes in argv
	while (argc > 0) {
		displayArg = argv[0];
		if (displayArg.getSegment())
			displayArg.setOffset(0xFFFF);
		argc--; argv++;
		switch (displayArg.getOffset()) {
		case SCI_DISPLAY_MOVEPEN:
			_ports->moveTo(argv[0].toUint16(), argv[1].toUint16());
			argc -= 2; argv += 2;
			break;
		case SCI_DISPLAY_SETALIGNMENT:
			alignment = argv[0].toSint16();
			argc--; argv++;
			break;
		case SCI_DISPLAY_SETPENCOLOR:
			colorPen = argv[0].toUint16();
			_ports->penColor(colorPen);
			argc--; argv++;
			break;
		case SCI_DISPLAY_SETBACKGROUNDCOLOR:
			colorBack = argv[0].toUint16();
			argc--; argv++;
			break;
		case SCI_DISPLAY_SETGREYEDOUTPUT:
			_ports->textGreyedOutput(!argv[0].isNull());
			argc--; argv++;
			break;
		case SCI_DISPLAY_SETFONT:
			_text16->SetFont(argv[0].toUint16());
			argc--; argv++;
			break;
		case SCI_DISPLAY_WIDTH:
			width = argv[0].toUint16();
			argc--; argv++;
			break;
		case SCI_DISPLAY_SAVEUNDER:
			doSaveUnder = true;
			break;
		case SCI_DISPLAY_RESTOREUNDER:
			bitsGetRect(argv[0], &rect);
			rect.translate(-_ports->getPort()->left, -_ports->getPort()->top);
			bitsRestore(argv[0]);
			kernelGraphRedrawBox(rect);
			// finishing loop
			argc = 0;
			break;
		case SCI_DISPLAY_DONTSHOWBITS:
			bRedraw = 0;
			break;

		// The following three dummy calls are not supported by the Sierra SCI
		// interpreter, but are erroneously called in some game scripts.
		case SCI_DISPLAY_DUMMY1:	// Longbow demo (all rooms) and QFG1 EGA demo (room 11)
		case SCI_DISPLAY_DUMMY2:	// Longbow demo (all rooms)
		case SCI_DISPLAY_DUMMY3:	// QFG1 EGA demo (room 11) and PQ2 (room 23)
			if (!(g_sci->getGameId() == GID_LONGBOW && g_sci->isDemo()) &&
				!(g_sci->getGameId() == GID_QFG1    && g_sci->isDemo()) &&
				!(g_sci->getGameId() == GID_PQ2))
				error("Unknown kDisplay argument %d", displayArg.getOffset());

			if (displayArg.getOffset() == SCI_DISPLAY_DUMMY2) {
				if (!argc)
					error("No parameter left for kDisplay(115)");
				argc--; argv++;
			}
			break;
		default:
			SciTrackOriginReply originReply;
			SciWorkaroundSolution solution = trackOriginAndFindWorkaround(0, kDisplay_workarounds, &originReply);
			if (solution.type == WORKAROUND_NONE)
				error("Unknown kDisplay argument (%04x:%04x) from method %s::%s (script %d, localCall %x)",
						PRINT_REG(displayArg), originReply.objectName.c_str(), originReply.methodName.c_str(),
						originReply.scriptNr, originReply.localCallOffset);
			assert(solution.type == WORKAROUND_IGNORE);
			break;
		}
	}

	// now drawing the text
	_text16->Size(rect, text, -1, width);
	rect.moveTo(_ports->getPort()->curLeft, _ports->getPort()->curTop);
	// Note: This code has been found in SCI1 middle and newer games. It was
	// previously only for SCI1 late and newer, but the LSL1 interpreter contains
	// this code.
	if (getSciVersion() >= SCI_VERSION_1_MIDDLE) {
		int16 leftPos = rect.right <= _screen->getWidth() ? 0 : _screen->getWidth() - rect.right;
		int16 topPos = rect.bottom <= _screen->getHeight() ? 0 : _screen->getHeight() - rect.bottom;
		_ports->move(leftPos, topPos);
		rect.moveTo(_ports->getPort()->curLeft, _ports->getPort()->curTop);
	}

	if (doSaveUnder)
		result = bitsSave(rect, GFX_SCREEN_MASK_VISUAL);
	if (colorBack != -1)
		fillRect(rect, GFX_SCREEN_MASK_VISUAL, colorBack, 0, 0);
	_text16->Box(text, false, rect, alignment, -1);
	if (_screen->_picNotValid == 0 && bRedraw)
		bitsShow(rect);
	// restoring port and cursor pos
	Port *currport = _ports->getPort();
	uint16 tTop = currport->curTop;
	uint16 tLeft = currport->curLeft;
	if (!g_sci->_features->usesOldGfxFunctions()) {
		// Restore port settings for some SCI0LATE and SCI01+ only.
		//
		// The change actually happened inbetween .530 (hoyle1) and .566 (heros
		// quest). We don't have any detection for that currently, so we are
		// using oldGfxFunctions (.502). The only games that could get
		// regressions because of this are hoyle1, kq4 and funseeker. If there
		// are regressions, we should use interpreter version (which would
		// require exe version detection).
		//
		// If we restore the port for whole SCI0LATE, at least sq3old will get
		// an issue - font 0 will get used when scanning for planets instead of
		// font 600 - a setfont parameter is missing in one of the kDisplay
		// calls in script 19. I assume this is a script bug, because it was
		// added in sq3new.
		*currport = oldPort;
	}
	currport->curTop = tTop;
	currport->curLeft = tLeft;
	return result;
}
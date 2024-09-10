reg_t kScrollWindowAdd(EngineState *s, int argc, reg_t *argv) {
	ScrollWindow *scrollWindow = g_sci->_gfxControls32->getScrollWindow(argv[0]);

	const Common::String text = s->_segMan->getString(argv[1]);
	const GuiResourceId fontId = argv[2].toSint16();
	const int16 color = argv[3].toSint16();
	const TextAlign alignment = (TextAlign)argv[4].toSint16();
	const bool scrollTo = argc > 5 ? (bool)argv[5].toUint16() : true;

	return scrollWindow->add(text, fontId, color, alignment, scrollTo);
}
static void
set_font_flags(void* _canvas, uint32 flags)
{
	Canvas* const canvas = reinterpret_cast<Canvas*>(_canvas);
	ServerFont font;
	font.SetFlags(flags);
	canvas->CurrentState()->SetFont(font, B_FONT_FLAGS);
}
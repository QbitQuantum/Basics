void hgeGUIText::printf(const char *format, ...)
{
	vsprintf(text, format, (char *)&format+sizeof(format));
}
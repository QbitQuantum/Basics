sText::sText(std::string Fontfile, unsigned int size, const char *fmt, ...)
{
	char text[1024];
	va_list ap;

	if(fmt == NULL) return;

	va_start(ap, fmt);
	vsnprintf_s(text,1024,1024, fmt, ap);
	va_end(ap);

	FontObject.loadFromFile(std::string("Media/").append(Fontfile));
	
	textObject.setFont(FontObject);
	
	textObject.setCharacterSize(size);

	textObject.setString(text);
}
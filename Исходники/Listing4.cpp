char* Rus(const char* text)
{
	CharToOemA(text, bufRus);
	return bufRus;
}
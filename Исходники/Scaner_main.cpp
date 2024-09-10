string Tooem(const char* str) //нужно для распознавания русского названия файлов из консоли
{
	vector<char> buffer(strlen(str) + 1);
	CharToOemA(str, &buffer[0]); //конвертация char в string 
	return string(&buffer[0], buffer.size()-1);
}
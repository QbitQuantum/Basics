void CStaticText::setText(int init)
{
	char* temp = IntToChar(init);
	itsText = temp;
	delete[] temp;
}
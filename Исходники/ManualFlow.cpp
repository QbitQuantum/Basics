std::string AFManualFlow::RetriveStdStringFromCWindow(CWindow &TempWindow)
{
	int TestLength = TempWindow.GetWindowTextLengthW()+1;
	wchar_t* buffer = new wchar_t[TestLength+1];

	TempWindow.GetWindowTextW(buffer,TestLength);
	std::string SimpString=CW2A(buffer);

	delete[] buffer;
	return SimpString;
}
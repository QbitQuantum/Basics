// create a guid-like unique name for what have you
// this is suitable as a generic helper
TString CConsolePipe::UGHGetUniqueName() 
{
	GUID gui;
	// here i use GUIDs; other techniques include getting GetTickCount with Thread ID etc
	HRESULT hr = CoCreateGuid(&gui); // $TSEK this don't requires CoInitialize

	LPOLESTR ole = NULL;
	hr = StringFromIID(gui, &ole); // this includes enclosing {braces}

	TString str = W2TConvert(ole); // converts as necessary
	if(ole)
		CoTaskMemFree(ole);

	return str;
}
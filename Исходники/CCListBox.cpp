void LIST_COLUMN::Set(PCWSTR wszTitle, DWORD Orientation, int Size)
{
	wcscpy(this->Title, wszTitle);
	this->Orientation = Orientation;
	this->Size = Size;
}
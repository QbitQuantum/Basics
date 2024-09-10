	Win32_Cursor::~Win32_Cursor()
	{
		if (this->cursor != NULL)
		{
			DestroyCursor(this->cursor);
			this->cursor = NULL;
		}
	}
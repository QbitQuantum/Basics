void WindowsConsoleLogger::write()
{
	if (this->stdOut != NULL) {
		DWORD check;
		WriteConsoleW(this->stdOut, (void*)this->buffer, this->size, &check, NULL);
	}
}
file_error win_close_ptty(osd_file *file)
{
	FlushFileBuffers(file->handle);
	DisconnectNamedPipe(file->handle);
	CloseHandle(file->handle);
	return FILERR_NONE;
}
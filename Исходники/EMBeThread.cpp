status_t EMBeThread::ThreadEntry(void* obj)
{
	if(!obj)
		return B_ERROR;

	// Each thread must set the new handler individually
	// The new handler manages the reserve memory buffers
	// that are released when the system has run out of RAM
	set_new_handler(&(EMExceptionHandler::NewHandler));

	((EMBeThread*) obj)	-> Run();
	return B_OK;
}
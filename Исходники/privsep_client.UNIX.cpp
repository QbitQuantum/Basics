bool
privsep_get_switchboard_response(FILE* err_fp, MyString *response)
{
	// first read everything off the error pipe and close
	// the error pipe
	//
	MyString err;
	while (err.readLine(err_fp, true)) { }
	fclose(err_fp);
	
	// if this is passed in, assume the caller will handle any
	// error propagation, and we just succeed.
	if (response) {
		*response = err;
		return true;
	}

	// if there was something there, print it out here (since no one captured
	// the error message) and return false to indicate something went wrong.
	if (err.Length() != 0) {
		dprintf(D_ALWAYS,
		        "privsep_get_switchboard_response: error received: %s",
			err.Value());
		return false;
	}

	// otherwise, indicate that everything's fine
	//
	return true;
}
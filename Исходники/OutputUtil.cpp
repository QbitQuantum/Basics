status_t
HeaderGuard(const SString &in, SString &out, bool system)
{
	// Do some validity checking
	if (!isalpha(in.ByteAt(0)))
	{
		berr << "filename must start with a letter " << in << endl;
		return B_ERROR;
	}
	
	char * p;
	int l;
	
	// Header Guard define name

	out = in;
	out.ToUpper();
	l = out.Length();
	p = out.LockBuffer(l);
	while (*p) {
		if (!isalnum(*p)) *p = '_';
		p++;
	}
	out.UnlockBuffer(l);
	
	if (system) out.Prepend('_', 1);
	
	return B_OK;
}
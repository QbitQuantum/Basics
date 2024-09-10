int32_t
PDirectoryGetEntries(void *pobject, void *in, void *out, void *extraData)
{
	if (!pobject || !in || !out)
		return B_ERROR;
	
	PDirectory *parent = static_cast<PDirectory*>(pobject);
	if (!parent)
		return B_BAD_TYPE;
	
	BDirectory *backend = (BDirectory*)parent->GetBackend();
	
	PArgs *outArgs = static_cast<PArgs*>(out);
	outArgs->MakeEmpty();
	
	PArgs nameList;
	backend->Rewind();
	entry_ref ref;
	while (backend->GetNextRef(&ref) == B_OK)
	{
		if (ref.name)
			outArgs->AddString("name", ref.name);
	}
	
	return B_OK;
}
int32_t
PTextViewSelect(void *pobject, void *in, void *out, void *extraData)
{
	if (!pobject || !in || !out)
		return B_ERROR;

	PView *parent = static_cast<PView*>(pobject);
	if (!parent)
		return B_BAD_TYPE;
	
	BTextView *backend = (BTextView*)parent->GetView();


	PArgs *inArgs = static_cast<PArgs*>(in);

	int32 start;
	if (inArgs->FindInt32("start", &start) != B_OK)
		return B_ERROR;

	int32 end;
	if (inArgs->FindInt32("end", &end) != B_OK)
		return B_ERROR;

	if (backend->Window())
		backend->Window()->Lock();


	backend->Select(start, end);

	if (backend->Window())
		backend->Window()->Unlock();

	return B_OK;
}
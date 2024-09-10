int32_t
PListViewSelect(void *pobject, void *in, void *out, void *extraData)
{
	if (!pobject || !in || !out)
		return B_ERROR;

	PView *parent = static_cast<PView*>(pobject);
	if (!parent)
		return B_BAD_TYPE;
	
	BListView *backend = (BListView*)parent->GetView();


	PArgs *inArgs = static_cast<PArgs*>(in);

	int32 index;
	if (inArgs->FindInt32("index", &index) != B_OK)
		return B_ERROR;

	bool extend;
	if (inArgs->FindBool("extend", &extend) != B_OK)
		return B_ERROR;

	if (backend->Window())
		backend->Window()->Lock();


	backend->Select(index, extend);

	if (backend->Window())
		backend->Window()->Unlock();

	return B_OK;
}
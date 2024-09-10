pascal OSStatus LineToProc(const Float32Point *pt, void *callBackDataPtr)
{
	OpGlyphCallbackStruct *data = (OpGlyphCallbackStruct*)callBackDataPtr;

	if(!data)
		return -1;

	OpBpath* p = data->path;
	if(p)
	{
		p->LineTo(pt->x, pt->y, FALSE);
		return noErr;
	}

	return -1;
}
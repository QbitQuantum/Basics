GpStatus
GdipDeletePathIter (GpPathIterator *iterator)
{
	if (!iterator)
		return InvalidParameter;

	if (iterator->path) {
		GdipDeletePath (iterator->path);
		iterator->path = NULL;
	}

	GdipFree (iterator);

	return Ok;
}
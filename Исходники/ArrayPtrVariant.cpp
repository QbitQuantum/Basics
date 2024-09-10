STDMETHODIMP ArrayPtrVariant<I, B>::Add(I* item)
{
	if (item == NULL)
		AtlTrace("Trying to add NULL to arrayptrvariant\n");
	checkCapacity();
	coll[_count++] = item;
	item->AddRef();

	return S_OK;
}
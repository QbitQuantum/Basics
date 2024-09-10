void CssmDbAttributeData::add(const CssmPolyData &inValue, Allocator &inAllocator)
{
	Value = reinterpret_cast<CSSM_DATA *>(inAllocator.realloc(Value, sizeof(*Value) * (NumberOfValues + 1)));
	CssmAutoData valueCopy(inAllocator, inValue);
	Value[NumberOfValues++] = valueCopy.release();
}
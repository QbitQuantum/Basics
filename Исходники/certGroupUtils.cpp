/*
 * Copy one CSSM_DATA to another, mallocing destination.
 */
void tpCopyCssmData(
	Allocator		&alloc,
	const CSSM_DATA	*src,
	CSSM_DATA_PTR	dst)
{
	dst->Data = (uint8 *)alloc.malloc(src->Length);
	dst->Length = src->Length;
	memmove(dst->Data, src->Data, src->Length);
}
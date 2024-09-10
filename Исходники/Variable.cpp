void *VarInteger::operator new(size_t aSize)
{
	return varintegerpool.malloc();
}
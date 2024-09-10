inline
void *Heap::Alloc(size_t sz)
{
	Stat(sz);
	if(sz <= 224) {
		if(sz == 0) sz = 1;
		return Allok(((int)sz - 1) >> 4);
	}
	if(sz <= 576)
		return Allok(sz <= 368 ? sz <= 288 ? 14 : 15 : sz <= 448 ? 16 : 17);
	return LAlloc(sz);
}
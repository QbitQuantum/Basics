void BiVector<T>::Add0() {
	ASSERT(items >= 0);
	if(items >= alloc)
		ReAlloc(ntl_max(2 * items, 4));
	items++;
}
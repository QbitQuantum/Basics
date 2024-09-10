void callASort(T* buff, size_t size, T*(*asort)(T* buff, size_t n), LPCTSTR fileOut)
{
	T* forSort = duplicateBuff(buff, size);

	T* sortRes = asort(forSort, size);

	if (outputOutput)
		outputBuff(sortRes, size);

	writefile(fileOut, sortRes, size);
	delete[] forSort;
}
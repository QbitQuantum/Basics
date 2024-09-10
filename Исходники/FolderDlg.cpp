//////////////////
// Free PIDL using shell's IMalloc
//
void CFolderDialog::FreePIDL(LPCITEMIDLIST pidl)
{
	CComQIPtr<IMalloc> iMalloc;	// shell's IMalloc
	HRESULT hr = SHGetMalloc(&iMalloc);
	ASSERT(SUCCEEDED(hr));
	iMalloc->Free((void*)pidl);
}
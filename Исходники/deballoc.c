void _StoreSigniture(HLOCAL hMem, UINT uByte, LPARAM lParam)
{
    if (hMem)
    {
	UINT uSize = LocalSize(hMem);
	Assert(uSize>=uByte+CBALLOCEXTRA);
	*(UINT*)HMEM2PTR(hMem, uSize-sizeof(UINT)) = uByte;
	*(LPARAM*)HMEM2PTR(hMem, uByte) = lParam;
    }
}
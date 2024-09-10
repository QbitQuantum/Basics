/**************************************************************************
*  IExtractIconW::Extract
*/
static HRESULT WINAPI IExtractIconW_fnExtract(IExtractIconW * iface, LPCWSTR pszFile,
        UINT nIconIndex, HICON *phiconLarge, HICON *phiconSmall, UINT nIconSize)
{
        IExtractIconWImpl *This = impl_from_IExtractIconW(iface);
        int index;
        HIMAGELIST big_icons, small_icons;

        FIXME("(%p) (file=%s index=%d %p %p size=%08x) semi-stub\n", This, debugstr_w(pszFile),
                (signed)nIconIndex, phiconLarge, phiconSmall, nIconSize);

        index = SIC_GetIconIndex(pszFile, nIconIndex, 0);
        Shell_GetImageLists( &big_icons, &small_icons );
	if (phiconLarge)
	  *phiconLarge = ImageList_GetIcon(big_icons, index, ILD_TRANSPARENT);

	if (phiconSmall)
	  *phiconSmall = ImageList_GetIcon(small_icons, index, ILD_TRANSPARENT);

	return S_OK;
}
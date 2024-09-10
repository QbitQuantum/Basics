static void OpenPropertyPages(HWND hwnd, IUnknown *propertyObject)
{
	if (!propertyObject)
		return;

	ComQIPtr<ISpecifyPropertyPages> pages(propertyObject);
	CAUUID cauuid;

	if (pages != NULL) {
		if (SUCCEEDED(pages->GetPages(&cauuid)) && cauuid.cElems) {
			OleCreatePropertyFrame(hwnd, 0, 0, NULL, 1,
					(LPUNKNOWN*)&propertyObject,
					cauuid.cElems, cauuid.pElems,
					0, 0, NULL);
			CoTaskMemFree(cauuid.pElems);
		}
	}
}
// TOOD rename to something else, maybe
HRESULT uiprivInitDrawText(void)
{
	// TOOD use DWRITE_FACTORY_TYPE_ISOLATED instead?
	return DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof (IDWriteFactory),
		(IUnknown **) (&dwfactory));
}
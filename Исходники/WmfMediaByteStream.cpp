STDMETHODIMP FWmfMediaByteStream::QueryInterface(REFIID RefID, void** Object)
{
	static const QITAB QITab[] =
	{
		QITABENT(FWmfMediaByteStream, IMFByteStream),
		QITABENT(FWmfMediaByteStream, IMFAsyncCallback),
		{ 0 }
	};

	return QISearch( this, QITab, RefID, Object );
}
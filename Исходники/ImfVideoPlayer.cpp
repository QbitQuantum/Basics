STDMETHODIMP FImfSampleGrabberCallback::QueryInterface( REFIID RefID, void** Object )
{
	static const QITAB QITab[] =
	{
		QITABENT( FImfSampleGrabberCallback, IMFSampleGrabberSinkCallback ),
		QITABENT( FImfSampleGrabberCallback, IMFClockStateSink ),
		{ 0 }
	};

	return QISearch( this, QITab, RefID, Object );
}
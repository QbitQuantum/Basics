HRESULT CPreviewPlugin::FinalConstruct()
{
	return CoCreateFreeThreadedMarshaler( GetControllingUnknown(), &m_pUnkMarshaler.p );
}
HRESULT CSWFBuilder::FinalConstruct() throw()
{
	return CoCreateFreeThreadedMarshaler( GetControllingUnknown(), &m_pUnkMarshaler.p );
}
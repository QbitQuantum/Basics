CDot11SampleExtUIConProperty::~CDot11SampleExtUIConProperty()
{
    SysFreeString(m_bstrFN);
    InterlockedDecrement(&g_objRefCount);        
}
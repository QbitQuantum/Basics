//
//   FUNCTION: CServiceBase::~CServiceBase()
//
//   PURPOSE: The virtual destructor of CServiceBase. 
//
CServiceBase::~CServiceBase(void)
{
    if (m_etwRegHandle != NULL)
    {
        EventUnregister(m_etwRegHandle);
    }
}
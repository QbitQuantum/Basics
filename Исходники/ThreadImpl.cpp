ThreadImpl::~ThreadImpl()
{
		
		if(IsActive())
		{
				if(m_hdl != 0)
				{
						Terminate();
						Join(INFINITE);
						::CloseHandle(m_hdl);
				}
		}
}
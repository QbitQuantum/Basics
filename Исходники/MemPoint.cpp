void CHandleException::ResetMemBp()//根据g_ResetMemBp重设内存断点，在单步中调用
{
	list<CCResetMemBp*>::iterator itDw = g_ResetMemBp.begin();
	while (g_ResetMemBp.size())
	{
		CCResetMemBp* p = *itDw;
		itDw++;
		DWORD dwTempProtect;
		VirtualProtectEx(m_hProcess, (LPVOID)p->dwAddr,
			1, PAGE_NOACCESS, &dwTempProtect);
		delete p;
		g_ResetMemBp.remove(p);
	}
}
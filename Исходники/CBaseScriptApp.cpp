void CBaseScriptApp::ChangeCurPathToRes()
{
#ifdef _WIN32
	_wchdir(m_pResPathMgr->GetCurPath());
#else
	chdir( utf16_to_utf8(m_pResPathMgr->GetCurPath()).c_str() );
#endif
}
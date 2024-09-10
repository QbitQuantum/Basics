	void CDumpCatch::SetInvalidHandle()
	{
#if _MSC_VER >= 1400  // MSVC 2005/8
		m_preIph = _set_invalid_parameter_handler(MyInvalidParameterHandler);
#endif  // _MSC_VER >= 1400
		m_prePch = _set_purecall_handler(MyPureCallHandler);   //At application, this call can stop show the error message box.
	}
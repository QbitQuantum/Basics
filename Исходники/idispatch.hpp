	HRESULT __stdcall Invoke(
		dispid_t dispidMember,
		const uuid::c_t &,
		lcid_t,
		word_t wFlags,
		dispparams_t * pdispparams,
		variant_t * pvarResult,
		excepinfo_t * pexcepinfo,
		uint_t * puArgErr)
	{
		return DispInvoke(
			(Base *)this, 
			internal<in>(scoped_type_info<Base>::typeinfo()),
			dispidMember, 
			wFlags, 
			pdispparams,
			pvarResult, 
			pexcepinfo, 
			puArgErr);
	}
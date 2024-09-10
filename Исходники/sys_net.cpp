	vm::ptr<s32> _sys_net_errno_loc()
	{
		libnet.warning("_sys_net_errno_loc()");
		return get_errno().ptr();
	}
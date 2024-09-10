//------------------------------------------------------------------------------
// Name: DebuggerCore()
// Desc: constructor
//------------------------------------------------------------------------------
DebuggerCore::DebuggerCore() : page_size_(0), process_handle_(0), start_address(0), image_base(0) {
	DebugSetProcessKillOnExit(false);

	SYSTEM_INFO sys_info;
	GetSystemInfo(&sys_info);
	page_size_ = sys_info.dwPageSize;

	set_debug_privilege(GetCurrentProcess(), true); // gogo magic powers
}
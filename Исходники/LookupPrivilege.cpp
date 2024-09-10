int main()
{
	// Get the name of privilege for a LUID. LUIDs can change from a Windows version to another.
	LUID privilege = { 31, 0 };
	wchar_t priv_name[100];
	DWORD len_priv_name = sizeof(priv_name);
	if (LookupPrivilegeName(nullptr, &privilege, priv_name, &len_priv_name)) {
		std::wstring priv{ priv_name };
		std::wcout << priv << std::endl;
	}
	
	// IID_IGlassTerminal       dd 6344A5B7h; Data1
	// .rdata:0000000100036320  dw 0EF1Ch; Data2
	// .rdata:0000000100036320  dw 47BAh; Data3
	// .rdata:0000000100036320  db 98h, 0B7h, 28h, 0C6h, 64h, 42h, 77h, 93h; Data4
	IID iid_glassterminal{ 0x6344A5B7, 0x0EF1C, 0x47BA, {0x98, 0xB7, 0x28, 0xC6, 0x64, 0x42, 0x77, 0x93} };

	LPOLESTR iid_string;
	StringFromIID(iid_glassterminal, &iid_string);
	std::wcout << "IID_GlassTerminal " << iid_string << std::endl;
	return 0;
}
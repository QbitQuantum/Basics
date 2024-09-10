ngspice::ngspice()
	:m_sendDataDebug(0)
	,m_flagPrompt(false)
	,m_running(false)
	,m_flagCheckLoadCircuit(false)
	//,m_breakTest(false)
{
	string path = get_exe_dir();
	SetCurrentDirectoryA(path.c_str());

	static int copy = 1;
	string dll = FormatString(100, "ngspice%d.dll", copy++);
	BOOL success = CopyFileA("ngspice.dll", dll.c_str(), FALSE);
	m_mod = LoadLibrary(dll.c_str());
	ngSpice_Init		= (Func_ngSpice_Init)GetProcAddress(m_mod, "ngSpice_Init");
	ngSpice_Init_Sync	= (Func_ngSpice_Init_Sync)GetProcAddress(m_mod, "ngSpice_Init_Sync");
	ngSpice_Command		= (Func_ngSpice_Command)GetProcAddress(m_mod, "ngSpice_Command");
	ngGet_Vec_Info		= (Func_ngGet_Vec_Info)GetProcAddress(m_mod, "ngGet_Vec_Info");
	ngSpice_Circ		= (Func_ngSpice_Circ)GetProcAddress(m_mod, "ngSpice_Circ");
	ngSpice_CurPlot		= (Func_ngSpice_CurPlot)GetProcAddress(m_mod, "ngSpice_CurPlot");
	ngSpice_AllPlots	= (Func_ngSpice_AllPlots)GetProcAddress(m_mod, "ngSpice_AllPlots");
	ngSpice_AllVecs		= (Func_ngSpice_AllVecs)GetProcAddress(m_mod, "ngSpice_AllVecs");
	ngSpice_running		= (Func_ngSpice_running)GetProcAddress(m_mod, "ngSpice_running");
	ngSpice_SetBkpt		= (Func_ngSpice_SetBkpt)GetProcAddress(m_mod, "ngSpice_SetBkpt");

	int ret = ngSpice_Init(procSendChar, procSendStat, procControlledExit, procSendData, procSendInitData, procBGThreadRunning, this);
}
int cellPadInit(u32 max_connect)
{
	sys_io.Log("cellPadInit(max_connect=%d)", max_connect);
	if(Emu.GetPadManager().IsInited()) return CELL_PAD_ERROR_ALREADY_INITIALIZED;
	Emu.GetPadManager().Init(max_connect);
	return CELL_OK;
}
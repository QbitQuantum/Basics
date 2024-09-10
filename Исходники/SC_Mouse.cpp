int cellMouseEnd()
{
    sys_io.Log("cellMouseEnd()");
    if(!Emu.GetMouseManager().IsInited()) return CELL_MOUSE_ERROR_UNINITIALIZED;
    Emu.GetMouseManager().Close();
    return CELL_OK;
}
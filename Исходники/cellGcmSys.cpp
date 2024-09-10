int cellGcmSetWaitFlip(mem_ptr_t<CellGcmContextData> ctxt)
{
	cellGcmSys.Log("cellGcmSetWaitFlip(ctx=0x%x)", ctxt.GetAddr());

	GSLockCurrent lock(GS_LOCK_WAIT_FLIP);
	return CELL_OK;
}
s32 cellDmuxPeekAuEx(u32 esHandle, vm::ptr<u32> auInfoEx, vm::ptr<u32> auSpecificInfo)
{
	cellDmux.trace("cellDmuxPeekAuEx(esHandle=0x%x, auInfoEx=**0x%x, auSpecificInfo=**0x%x)", esHandle, auInfoEx, auSpecificInfo);

	const auto es = idm::get<ElementaryStream>(esHandle);

	if (!es)
	{
		return CELL_DMUX_ERROR_ARG;
	}

	u32 info;
	u32 spec;
	if (!es->peek(info, false, spec, false))
	{
		return CELL_DMUX_ERROR_EMPTY;
	}

	*auInfoEx = info;
	*auSpecificInfo = spec;
	return CELL_OK;
}
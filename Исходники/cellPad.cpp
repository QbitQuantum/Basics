s32 cellPadSetSensorMode(u32 port_no, u32 mode)
{
	sys_io.trace("cellPadSetSensorMode(port_no=%d, mode=%d)", port_no, mode);

	const auto handler = fxm::get<PadHandlerBase>();

	if (!handler)
		return CELL_PAD_ERROR_UNINITIALIZED;

	if (mode != 0 && mode != 1)
		return CELL_PAD_ERROR_INVALID_PARAMETER;

	const PadInfo& rinfo = handler->GetInfo();

	if (port_no >= rinfo.max_connect)
		return CELL_PAD_ERROR_INVALID_PARAMETER;
	if (port_no >= rinfo.now_connect)
		return CELL_PAD_ERROR_NO_DEVICE;

	std::vector<Pad>& pads = handler->GetPads();

	if (mode)
		pads[port_no].m_port_setting |= CELL_PAD_SETTING_SENSOR_ON;
	else
		pads[port_no].m_port_setting &= ~CELL_PAD_SETTING_SENSOR_ON;

	return CELL_OK;
}
error_code cellKbRead(u32 port_no, vm::ptr<CellKbData> data)
{
	sys_io.trace("cellKbRead(port_no=%d, data=*0x%x)", port_no, data);

	const auto handler = fxm::get<KeyboardHandlerBase>();

	if (!handler)
		return CELL_KB_ERROR_UNINITIALIZED;

	const std::vector<Keyboard>& keyboards = handler->GetKeyboards();

	if (port_no >= keyboards.size())
		return CELL_KB_ERROR_INVALID_PARAMETER;

	KbData& current_data = handler->GetData(port_no);
	data->led = current_data.led;
	data->mkey = current_data.mkey;
	data->len = std::min((u32)current_data.len, CELL_KB_MAX_KEYCODES);

	for (s32 i=0; i<current_data.len; i++)
	{
		data->keycode[i] = current_data.keycode[i];
	}

	current_data.len = 0;
	
	return CELL_OK;
}
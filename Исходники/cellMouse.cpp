s32 cellMouseGetData(u32 port_no, vm::ptr<CellMouseData> data)
{
	sys_io.trace("cellMouseGetData(port_no=%d, data=*0x%x)", port_no, data);

	const auto handler = fxm::get<MouseHandlerBase>();

	if (!handler)
	{
		return CELL_MOUSE_ERROR_UNINITIALIZED;
	}

	if (port_no >= handler->GetMice().size())
	{
		return CELL_MOUSE_ERROR_NO_DEVICE;
	}
	
	MouseData& current_data = handler->GetData(port_no);
	data->update = current_data.update;
	data->buttons = current_data.buttons;
	data->x_axis = current_data.x_axis;
	data->y_axis = current_data.y_axis;
	data->wheel = current_data.wheel;
	data->tilt = current_data.tilt;

	current_data.update = CELL_MOUSE_DATA_NON;
	current_data.x_axis = 0;
	current_data.y_axis = 0;
	current_data.wheel = 0;

	return CELL_OK;
}
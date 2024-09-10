static void write_board( running_machine &machine, UINT8 data)
{

	Line18_REED=data;

	if (read_board_flag && !strcmp(machine.system().name,"glasgow") ) //HACK
		Line18_LED = 0;
	else
		Line18_LED = data;

	 read_board_flag = FALSE;

	if (data == 0xff)
		mboard_key_selector = 0;
}
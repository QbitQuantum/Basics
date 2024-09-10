// печатает в буфер key_name_buffer текстовое описание нажатой комбинации кнопок
// Кодировка ANSI (для экономии места, всё равно названия клавиш английские)
VOID HwHotKeys_PrintFullKeyname(DWORD scancode)
{
	key_name_buffer[0] = 0;
	if (!scancode) // если нулевой сканкод - то пустую строку делаем.
	{
		return;
	}

	if (scancode & key_flag_sl) // L_Shift
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_SL);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}
	if (scancode & key_flag_sr) // R_Shift
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_SR);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}
	if (scancode & key_flag_ss) // Shift
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_SS);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}

	if (scancode & key_flag_cl) // L_Ctrl
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_CL);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}
	if (scancode & key_flag_cr) // R_Ctrl
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_CR);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}
	if (scancode & key_flag_cc) // Ctrl
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_CC);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}

	if (scancode & key_flag_al) // L_Alt
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_AL);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}
	if (scancode & key_flag_ar) // R_Alt
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_AR);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}
	if (scancode & key_flag_aa) // Alt
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_AA);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}

	if (scancode & key_flag_wl) // L_Win
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_WL);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}
	if (scancode & key_flag_wr) // R_Win
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_WR);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}
	if (scancode & key_flag_ww) // Win
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), t_WW);
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), " + ");
	}

	if ((scancode & 0x1FF) < sizeof(key_tab)) // защита от ошибочных данных - чтобы не выйти из таблицы имён.
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), key_tab[(scancode & 0x1FF)]);
	}
	else
	{
		StringCbCatA(key_name_buffer, sizeof(key_name_buffer), "out of range");
	}

	INT_PTR tmp1 = mir_strlen(key_name_buffer); // допечатываем в конеце строки сканкод - для удобства работы с пока ещё не известными (безимянными) кнопками
	StringCbPrintfA(key_name_buffer + tmp1, sizeof(key_name_buffer) - tmp1, " (%03X)", (scancode & 0x1FF));

	return;
}
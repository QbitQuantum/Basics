int apollo_kbd_device::push_scancode(UINT8 code, UINT8 repeat)
{
	int n_chars = 0;
	UINT16 key_code = 0;
	UINT8 caps = BIT(machine().root_device().ioport("keyboard4")->read(),0);
	UINT8 shift = BIT(machine().root_device().ioport("keyboard4")->read(),1) | BIT(machine().root_device().ioport("keyboard4")->read(),5);
	UINT8 ctrl = BIT(machine().root_device().ioport("keyboard4")->read(),2);
	UINT8 numlock = BIT(machine().root_device().ioport("keyboard4")->read(),6);
	UINT16 index;

	if (keyboard_is_german())
	{
		// map special keys for German keyboard
		switch (code)
		{
		case 0x00: code = 0x68; break; // _
		case 0x0e: code = 0x6b; break; // #
		case 0x29: code = 0x69; break; // <>
		case 0x42: code = 0x6f; break; // NP-
		case 0x46: code = 0x6e; break; // NP+
		case 0x4e: code = 0x73; break; // NP ENTER
		}
	}

#if MAP_APOLLO_KEYS
	if (numlock)
	{
		// don't map function keys to Apollo left keypad
		switch (code)
		{
		case 0x52: code = 0x75; break; // F1
		case 0x53: code = 0x76; break; // F2
		case 0x54: code = 0x77; break; // F3
		case 0x55: code = 0x78; break; // F4
		case 0x56: code = 0x79; break; // F5
		case 0x57: code = 0x7a; break; // F6
		case 0x58: code = 0x7b; break; // F7
		case 0x59: code = 0x7c; break; // F8
		case 0x5a: code = 0x7d; break; // F9
		case 0x5b: code = 0x74; break; // F0 = F10
		}
	}
#endif

	index = (code & 0x7f) * CODE_TABLE_ENTRY_SIZE;
	if (m_mode == KBD_MODE_0_COMPATIBILITY)
	{
		if (code & 0x80)
		{
			// skip up code in ASCII mode
		}
		else if (repeat > 0
				&& m_code_table[index + CODE_TABLE_AUTO_REPEAT_CODE] != Yes)
		{
			// skip repeat in ASCII mode
		}
		else if (ctrl)
		{
			key_code = m_code_table[index + CODE_TABLE_CONTROL_CODE];
		}
		else if (shift)
		{
			key_code = m_code_table[index + CODE_TABLE_SHIFTED_CODE];
		}
		else if (caps)
		{
			key_code = m_code_table[index + CODE_TABLE_CAPS_LOCK_CODE];
		}
		else
		{
			key_code = m_code_table[index + CODE_TABLE_UNSHIFTED_CODE];
		}
	}
	else
	{
		if (repeat > 0)
		{
			if (repeat == 1)
			{
				// auto repeat (but only for first scanned key)
				key_code = 0x7f;
			}
		}
		else if (code & 0x80)
		{
			key_code = m_code_table[index + CODE_TABLE_UP_CODE];
		}
		else
		{
			key_code = m_code_table[index + CODE_TABLE_DOWN_CODE];
		}
	}

	if (key_code != 0)
	{
		LOG2(("scan_code = 0x%02x key_code = 0x%04x",code, key_code));
		if (m_mode > KBD_MODE_1_KEYSTATE)
		{
			set_mode(KBD_MODE_1_KEYSTATE);
		}

		if (key_code & 0xff00)
		{
			xmit_char(key_code >> 8);
			n_chars++;
		}
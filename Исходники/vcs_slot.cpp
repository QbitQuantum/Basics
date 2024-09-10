bool vcs_cart_slot_device::call_load()
{
	if (m_cart)
	{
		UINT8 *ROM;
		UINT32 len;

		if (software_entry() != NULL)
			len = get_software_region_length("rom");
		else
			len = length();

		//printf("Size: 0x%X\n", len);

		// check that filesize is among the supported ones
		switch (len)
		{
			case 0x00800:
			case 0x01000:
			case 0x02000:
			case 0x028ff:
			case 0x02900:
			case 0x03000:
			case 0x04000:
			case 0x08000:
			case 0x10000:
			case 0x80000:
				break;

			default:
				seterror(IMAGE_ERROR_UNSUPPORTED, "Invalid rom file size" );
				return IMAGE_INIT_FAIL;
		}

		m_cart->rom_alloc(len, tag());
		ROM = m_cart->get_rom_base();

		if (software_entry() != NULL)
		{
			const char *pcb_name;
			bool has_ram = get_software_region("ram") ? TRUE : FALSE;
			memcpy(ROM, get_software_region("rom"), len);

			if ((pcb_name = get_feature("slot")) != NULL)
				m_type = vcs_get_pcb_id(pcb_name);
			else
			{
				// identify type based on size
				switch (len)
				{
					case 0x800:
						m_type = A26_2K;
						break;
					case 0x1000:
						m_type = A26_4K;
						break;
					case 0x2000:
						m_type = A26_F8;
						break;
					case 0x28ff:
					case 0x2900:
						m_type = A26_DPC;
						break;
					case 0x3000:
						m_type = A26_FA;
						break;
					case 0x4000:
						m_type = A26_F6;
						break;
					case 0x8000:
						m_type = A26_F4;
						break;
					case 0x10000:
						m_type = A26_32IN1;
						break;
					case 0x80000:
						m_type = A26_3F;
						break;
					default:
						m_type = A26_4K;
						printf("Unrecognized cart type!\n");
						break;
				}
			}

			if (has_ram)
				m_cart->ram_alloc(get_software_region_length("ram"));
		}
		else
		{
			fread(ROM, len);
			m_type = identify_cart_type(ROM, len);

			// check for Special Chip (128bytes of RAM)
			if (len == 0x2000 || len == 0x4000 || len == 0x8000)
				if (detect_super_chip(ROM, len))
				{
					m_cart->ram_alloc(0x80);
					//printf("Super Chip detected!\n");
				}
			// Super chip games:
			// dig dig, crystal castles, millipede, stargate, defender ii, jr. Pac Man,
			// desert falcon, dark chambers, super football, sprintmaster, fatal run,
			// off the wall, shooting arcade, secret quest, radar lock, save mary, klax

			// add CBS RAM+ (256bytes of RAM)
			if (m_type == A26_FA)
				m_cart->ram_alloc(0x100);
			// add M Network RAM
			else if (m_type == A26_E7)
				m_cart->ram_alloc(0x800);
			// add Commavid RAM
			else if (m_type == A26_CV)
				m_cart->ram_alloc(0x400);
			// add Starpath Superchager RAM
			else if (m_type == A26_SS)
				m_cart->ram_alloc(0x1800);
			// add Boulder Dash RAM
			else if (m_type == A26_3E)
				m_cart->ram_alloc(0x8000);
		}

		//printf("Type: %s\n", vcs_get_slot(m_type));

		// pass a pointer to the now allocated ROM for the DPC chip
		if (m_type == A26_DPC)
			m_cart->setup_addon_ptr((UINT8 *)m_cart->get_rom_base() + 0x2000);

		return IMAGE_INIT_PASS;
	}

	return IMAGE_INIT_PASS;
}
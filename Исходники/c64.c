static int c64_crt_load( device_image_interface &image )
{
	legacy_c64_state *state = image.device().machine().driver_data<legacy_c64_state>();
	int size = image.length(), test, i = 0, ii;
	int _80_loaded = 0, _90_loaded = 0, a0_loaded = 0, b0_loaded = 0, e0_loaded = 0, f0_loaded = 0;
	const char *filetype = image.filetype();
	int address = 0, new_start = 0;
	// int lbank_end_addr = 0, hbank_end_addr = 0;
	UINT8 *cart_cpy = state->memregion("user1")->base();

	/* We support .crt files */
	if (!mame_stricmp(filetype, "crt"))
	{
		int j;
		unsigned short c64_cart_type;

		if (i >= C64_MAX_ROMBANK)
			return IMAGE_INIT_FAIL;

		/* Start to parse the .crt header */
		/* 0x16-0x17 is Hardware type */
		image.fseek(0x16, SEEK_SET);
		image.fread(&c64_cart_type, 2);
		state->m_cart.mapper = BIG_ENDIANIZE_INT16(c64_cart_type);

		/* If it is unsupported cart type, warn the user */
		switch (state->m_cart.mapper)
		{
			case SIMONS_BASIC:	/* Type #  4 */
			case OCEAN_1:		/* Type #  5 */
			case FUN_PLAY:		/* Type #  7 */
			case SUPER_GAMES:		/* Type #  8 */
			case EPYX_FASTLOAD:	/* Type # 10 */
			case REX:			/* Type # 12 */
			case C64GS:			/* Type # 15 */
			case DINAMIC:		/* Type # 17 */
			case ZAXXON:		/* Type # 18 */
			case DOMARK:		/* Type # 19 */
			case COMAL_80:		/* Type # 21 */
			case GENERIC_CRT:		/* Type #  0 */
				printf("Currently supported cart type (Type %d)\n", state->m_cart.mapper);
				break;

			default:
			case ACTION_REPLAY:	/* Type #  1 */
			case KCS_PC:		/* Type #  2 */
			case FINAL_CART_III:	/* Type #  3 */
			case EXPERT:		/* Type #  6 */
			case ATOMIC_POWER:	/* Type #  9 */
			case WESTERMANN:		/* Type # 11 */
			case FINAL_CART_I:	/* Type # 13 */
			case MAGIC_FORMEL:	/* Type # 14 */
			case SUPER_SNAP_5:	/* Type # 20 */
				printf("Currently unsupported cart type (Type %d)\n", state->m_cart.mapper);
				break;
		}

		/* 0x18 is EXROM */
		image.fseek(0x18, SEEK_SET);
		image.fread(&state->m_cart.exrom, 1);

		/* 0x19 is GAME */
		image.fread(&state->m_cart.game, 1);

		/* We can pass to the data: it starts from 0x40 */
		image.fseek(0x40, SEEK_SET);
		j = 0x40;

		logerror("Loading cart %s size:%.4x\n", image.filename(), size);
		logerror("Header info: EXROM %d, GAME %d, Cart Type %d \n", state->m_cart.exrom, state->m_cart.game, c64_cart_type);


		/* Data in a .crt image are organized in blocks called 'CHIP':
           each 'CHIP' consists of a 0x10 header, which contains the
           actual size of the block, the loading address and info on
           the bankswitch, followed by the actual data                  */
		while (j < size)
		{
			unsigned short chip_size, chip_bank_index, chip_data_size;
			unsigned char buffer[10];

			/* Start to parse the CHIP header */
			/* First 4 bytes are the string 'CHIP' */
			image.fread(buffer, 6);

			/* 0x06-0x07 is the size of the CHIP block (header + data) */
			image.fread(&chip_size, 2);
			chip_size = BIG_ENDIANIZE_INT16(chip_size);

			/* 0x08-0x09 chip type (ROM, RAM + no ROM, Flash ROM) */
			image.fread(buffer + 6, 2);

			/* 0x0a-0x0b is the bank number of the CHIP block */
			image.fread(&chip_bank_index, 2);
			chip_bank_index = BIG_ENDIANIZE_INT16(chip_bank_index);

			/* 0x0c-0x0d is the loading address of the CHIP block */
			image.fread(&address, 2);
			address = BIG_ENDIANIZE_INT16(address);

			/* 0x0e-0x0f is the data size of the CHIP block (without header) */
			image.fread(&chip_data_size, 2);
			chip_data_size = BIG_ENDIANIZE_INT16(chip_data_size);

			/* Print out the CHIP header! */
			logerror("%.4s %.2x %.2x %.4x %.2x %.2x %.4x %.4x:%.4x\n",
				buffer, buffer[4], buffer[5], chip_size,
				buffer[6], buffer[7], chip_bank_index,
				address, chip_data_size);
			logerror("Loading CHIP data at %.4x size:%.4x\n", address, chip_data_size);

			/* Store data, address & size of the CHIP block */
			state->m_cart.bank[i].addr = address;
			state->m_cart.bank[i].index = chip_bank_index;
			state->m_cart.bank[i].size = chip_data_size;
			state->m_cart.bank[i].start = new_start;

			test = image.fread(cart_cpy + new_start, state->m_cart.bank[i].size);
			new_start += state->m_cart.bank[i].size;

			/* Does CHIP contain any data? */
			if (test != state->m_cart.bank[i].size)
				return IMAGE_INIT_FAIL;

			/* Advance to the next CHIP block */
			i++;
			j += chip_size;
		}
	}
	else /* We also support .80 files for c64 & .e0/.f0 for max */
	{
		/* Assign loading address according to extension */
		if (!mame_stricmp(filetype, "80"))
			address = 0x8000;

		if (!mame_stricmp(filetype, "e0"))
			address = 0xe000;

		if (!mame_stricmp(filetype, "f0"))
			address = 0xf000;

		logerror("loading %s rom at %.4x size:%.4x\n", image.filename(), address, size);

		/* Store data, address & size */
		state->m_cart.bank[0].addr = address;
		state->m_cart.bank[0].size = size;
		state->m_cart.bank[0].start = new_start;

		test = image.fread(cart_cpy + new_start, state->m_cart.bank[0].size);
		new_start += state->m_cart.bank[0].size;

		/* Does cart contain any data? */
		if (test != state->m_cart.bank[0].size)
			return IMAGE_INIT_FAIL;
	}

	state->m_cart.n_banks = i; // this is also needed so that we only set mappers if a cart is present!

	/* If we load a .crt file, use EXROM & GAME from the header! */
	if ((state->m_cart.exrom != -1) && (state->m_cart.game != -1))
	{
		state->m_exrom = state->m_cart.exrom;
		state->m_game  = state->m_cart.game;
	}

	/* Finally load the cart */
	state->m_roml = state->m_c64_roml;
	state->m_romh = state->m_c64_romh;

	memset(state->m_roml, 0, 0x2000);
	memset(state->m_romh, 0, 0x2000);

	switch (state->m_cart.mapper)
	{
	default:
		if (!state->m_game && state->m_exrom && (state->m_cart.n_banks == 1))
		{
			memcpy(state->m_romh, cart_cpy, 0x2000);
		}
		else
		{
			// we first attempt to load the first 'CHIPs' with address 0x8000-0xb000 and 0xe000-0xf000, otherwise we load the first (or first two) 'CHIPs' of the image
			for (ii = 0; ii < state->m_cart.n_banks; ii++)
			{
				if (state->m_cart.bank[ii].addr == 0x8000 && !_80_loaded)
				{
					memcpy(state->m_roml, cart_cpy + state->m_cart.bank[ii].start, state->m_cart.bank[ii].size);
					_80_loaded = 1;
					if (state->m_cart.bank[ii].size > 0x1000)
						_90_loaded = 1;
					if (state->m_cart.bank[ii].size > 0x2000)
						a0_loaded = 1;
					if (state->m_cart.bank[ii].size > 0x3000)
						b0_loaded = 1;
//                  printf("addr 0x8000: 80 %d, 90 %d, a0 %d, b0 %d\n", _80_loaded, _90_loaded, a0_loaded, b0_loaded);
				}

				if (state->m_cart.bank[ii].addr == 0x9000 && !_90_loaded)
				{
					memcpy(state->m_roml + 0x1000, cart_cpy + state->m_cart.bank[ii].start, state->m_cart.bank[ii].size);
					_90_loaded = 1;
					if (state->m_cart.bank[ii].size > 0x1000)
						a0_loaded = 1;
					if (state->m_cart.bank[ii].size > 0x2000)
						b0_loaded = 1;
//                  printf("addr 0x9000: 80 %d, 90 %d, a0 %d, b0 %d\n", _80_loaded, _90_loaded, a0_loaded, b0_loaded);
				}

				if (state->m_cart.bank[ii].addr == 0xa000 && !a0_loaded)
				{
					memcpy(state->m_roml + 0x2000, cart_cpy + state->m_cart.bank[ii].start, state->m_cart.bank[ii].size);
					a0_loaded = 1;
					if (state->m_cart.bank[ii].size > 0x1000)
						b0_loaded = 1;
//                  printf("addr 0xa000: 80 %d, 90 %d, a0 %d, b0 %d\n", _80_loaded, _90_loaded, a0_loaded, b0_loaded);
				}

				if (state->m_cart.bank[ii].addr == 0xb000 && !b0_loaded)
				{
					memcpy(state->m_roml + 0x3000, cart_cpy + state->m_cart.bank[ii].start, state->m_cart.bank[ii].size);
					b0_loaded = 1;
//                  printf("addr 0xb000: 80 %d, 90 %d, a0 %d, b0 %d\n", _80_loaded, _90_loaded, a0_loaded, b0_loaded);
				}

				if (state->m_cart.bank[ii].addr == 0xe000 && !e0_loaded)
				{
					memcpy(state->m_romh, cart_cpy + state->m_cart.bank[ii].start, state->m_cart.bank[ii].size);
					e0_loaded = 1;
					if (state->m_cart.bank[ii].size > 0x1000)
						f0_loaded = 1;
//                  printf("addr 0xe000: e0 %d, f0 %d\n", e0_loaded, f0_loaded);
				}

				if (state->m_cart.bank[ii].addr == 0xf000 && !f0_loaded)
				{
					memcpy(state->m_romh + 0x1000, cart_cpy + state->m_cart.bank[ii].start, state->m_cart.bank[ii].size);
					f0_loaded = 1;
//                  printf("addr 0xe000: e0 %d, f0 %d\n", e0_loaded, f0_loaded);
				}
			}
		}
	}

	return IMAGE_INIT_PASS;
}
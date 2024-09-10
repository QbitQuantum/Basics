		_nes_rom::~_nes_rom(void)
		{

			if(is_initialized()) {
				uninitialize();
			}
		}
static void check_fpu()
{
	uint32_t f_control;
	if(_controlfp_s(&f_control, 0, 0) == 0) {
		uint32_t unused;
		uint32_t rounding_mode = f_control & _MCW_RC;
		uint32_t precision_mode = f_control & _MCW_PC;
		if(rounding_mode != _RC_NEAR) {
			std::cerr << "Floating point rounding mode is currently '" <<
				((rounding_mode == _RC_CHOP) ? "chop" :
				(rounding_mode == _RC_UP) ? "up" :
				(rounding_mode == _RC_DOWN) ? "down" :
				(rounding_mode == _RC_NEAR) ? "near" :
				"unknown") << "' setting to 'near'\n";
			if(_controlfp_s(&unused, _RC_NEAR, _MCW_RC)) {
				std::cerr << "failed to set floating point rounding type to 'near'\n";
			}
		}
		if(precision_mode != _PC_53) {
			std::cerr << "Floating point precision mode is currently '" <<
				((precision_mode == _PC_53) ? "double" :
				(precision_mode == _PC_24) ? "single" :
				(precision_mode == _PC_64 ) ? "double extended" :
				"unknown") << "' setting to 'double'\n";
			if(_controlfp_s(&unused, _PC_53, _MCW_PC)) {
				std::cerr << "failed to set floating point precision type to 'double'\n";
			}
		}
	}
	else {
		std::cerr << "_controlfp_s failed.\n";
	}
}
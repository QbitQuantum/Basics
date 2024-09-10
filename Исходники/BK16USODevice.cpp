void BK16USODevice::init(unsigned char* frame)
{
	if (Debug::BK16_DEBUG_OUT){
		char str[800];
		std::cout << "BK16USODevice::init ";
		for (int i = 0; i < frame[3] + frame[4] * 256 + 7; i++)
			std::cout << _itoa(frame[i], str, 16) << " ";
		std::cout << std::endl;
	}

	fInit = true;

	frame[0] = frame[1];
	frame[1] = address;
	frame[2] = COMMAND_INIT;
	frame[3] = 0;
	frame[4] = 0;
}
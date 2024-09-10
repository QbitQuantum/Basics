static UInt8 _dx2vk(UINT dx){
	if (dx >= VK_TABLE_SIZE) 
		return NOKEY;

	UInt8 vkCode = NOKEY;
	HKL kbLayout = GetKeyboardLayout(0);
	vkCode = MapVirtualKeyEx(dx, 3, kbLayout);
	if (!vkCode)
	{
		switch (dx)
		{
			DX2VK(DIVIDE);
			DX2VK(RCONTROL);
			DX2VK(RMENU);
			DX2VK(HOME);
			DX2VK(PRIOR);
			DX2VK(UP);
			DX2VK(DOWN);
			DX2VK(LEFT);
			DX2VK(RIGHT);
			DX2VK(END);
			DX2VK(NEXT);
			DX2VK(INSERT);
			DX2VK(DELETE);

			case DIK_NUMPADENTER:
				vkCode = VK_SEPARATOR;
				break;
			default:
				vkCode = NOKEY;
		}
	}

	return vkCode;
}
int main(int argc, char ** argv)
{
	
	DWORD devIndex = 0; 
	char Buffer[255];
	ftdi_pins.pins = 0xF1;
	ftdi_pins.clk = HIGH;
	DWORD p = 0;
	byte e1 = 0xff;
	byte e2 = 0;

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 7);
	if (argc < 2) {
		printf("Please specify the hex file\n");
		return 1;
	}

	
	FT_STATUS ftStatus = FT_ListDevices((PVOID)devIndex, Buffer, FT_LIST_BY_INDEX | FT_OPEN_BY_SERIAL_NUMBER);
	if (ftStatus == FT_OK) {

		int bytes = load_file(argv[1]);

		ftStatus = FT_OpenEx(Buffer, FT_OPEN_BY_SERIAL_NUMBER, &ftdi_chip);
		FT_SetBitMode(ftdi_chip, PIN_TX | PIN_RX | PIN_CTS, 1); // BIT BANG MODE
		FT_SetBaudRate(ftdi_chip, BAUD_RATE);						 

		setPin(RST_8051, LOW);
		setPin(MOSI_8051, LOW);
		setPin(CLK_8051, LOW);
		setPin(RST_8051, HIGH);
		
		Sleep(500);
		printf("%x\n", progEnable());		
		Sleep(1100);

		eraseChip();

		for (int i = from_addr; i < to_addr + 1; i++) {
			printf("%02X", readProgmem(0, i));
		}
		printf("\n");


		for (int i = from_addr; i < to_addr + 1; i++) {
			printf("%02X", memory[i]);
		}
		printf("\n");
		
		// write memory
		for (int i = from_addr; i < to_addr+1; i++) {
			writeProgmem(0, i, memory[i]);
			printf("%02X", readProgmem(0, i));
		}
		printf("\n");
		

		Sleep(1000);
		setPin(RST_8051, LOW);
		Sleep(500);

		FT_Close(ftdi_chip);

		getchar();
	}
	else {
		printf("Can't open FTDI chip\n");
		return 1;
	}

	return 0;
}
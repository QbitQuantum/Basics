void CWCheatEngine::Run() {
	CWCheatEngine cheats;
	exit2 = false;
	while (!exit2) {
		codes = cheats.GetCodesList();  // UI Member
		currentCode = 0;

		while (true) {
			std::vector<int> code = GetNextCode();
			if (code.size() < 2) {
				Exit();
				break;
			}

			int value;
			unsigned int comm = code[0];
			int arg = code[1];
			int addr = GetAddress(comm & 0x0FFFFFFF);

			switch (comm >> 28) {
			case 0: // 8-bit write.
				if (Memory::IsValidAddress(addr)){
					Memory::Write_U8((u8) arg, addr);
				}
				break;
			case 0x1: // 16-bit write
				if (Memory::IsValidAddress(addr)){
					Memory::Write_U16((u16) arg, addr);
				}
				break;
			case 0x2: // 32-bit write
				if (Memory::IsValidAddress(addr)){
					Memory::Write_U32((u32) arg, addr);
				}
				break;
			case 0x3: // Increment/Decrement
				{
					addr = GetAddress(arg);
					value = 0;
					int increment = 0;
					// Read value from memory
					switch ((comm >> 20) & 0xF) {
					case 1:
					case 2: // 8-bit
						value = Memory::Read_U8(addr);
						increment = comm & 0xFF;
						break;
					case 3:
					case 4: // 16-bit
						value = Memory::Read_U16(addr);
						increment = comm & 0xFFFF;
						break;
					case 5:
					case 6: // 32-bit
						value = Memory::Read_U32(addr);
						code = GetNextCode();
						if ( code[0] != NULL) {
							increment = code[0];
						}
						break;
					}
					// Increment/Decrement value
					switch ((comm >> 20) & 0xF) {
					case 1:
					case 3:
					case 5: // increment
						value += increment;
						break;
					case 2:
					case 4:
					case 6: // Decrement
						value -= increment;
						break;
					}
					// Write value back to memory
					switch ((comm >> 20) & 0xF) {
					case 1:
					case 2: // 8-bit
						Memory::Write_U8((u8) value, addr);
						break;
					case 3:
					case 4: // 16-bit
						Memory::Write_U16((u16) value, addr);
						break;
					case 5:
					case 6: // 32-bit
						Memory::Write_U32((u32) value, addr);
						break;
					}
					break;
				}
			case 0x4: // 32-bit patch code
				code = GetNextCode();
				if (code[0] != NULL) {
					int data = code[0];
					int dataAdd = code[1];

					int maxAddr = (arg >> 16) & 0xFFFF;
					int stepAddr = (arg & 0xFFFF) * 4;
					for (int a  = 0; a < maxAddr; a++) {
						if (Memory::IsValidAddress(addr)) {
							Memory::Write_U32((u32) data, addr);
						}
						addr += stepAddr;
						data += dataAdd;
					}
				}
				break;
			case 0x5: // Memcpy command
				code = GetNextCode();
				if (code[0] != NULL) {
					int destAddr = code[0];
					if (Memory::IsValidAddress(addr) && Memory::IsValidAddress(destAddr)) {
						Memory::Memcpy(destAddr, Memory::GetPointer(addr), arg);
					}
				}
				break;
			case 0x6: // Pointer commands
				code = GetNextCode();
				if (code[0] != NULL) {
					int arg2 = code[0];
					int offset = code[1];
					int baseOffset = (arg2 >> 20) * 4;
					int base = Memory::Read_U32(addr + baseOffset);
					int count = arg2 & 0xFFFF;
					int type = (arg2 >> 16) & 0xF;
					for (int i = 1; i < count; i ++ ) {
						if (i+1 < count) {
							code = GetNextCode();
							int arg3 = code[0];
							int arg4 = code[1];
							int comm3 = arg3 >> 28;
							switch (comm3) {
							case 0x1: // type copy byte
								{
									int srcAddr = Memory::Read_U32(addr) + offset;
									int dstAddr = Memory::Read_U16(addr + baseOffset) + (arg3 & 0x0FFFFFFF);
									Memory::Memcpy(dstAddr, Memory::GetPointer(srcAddr), arg);
									type = -1; //Done
									break; }
							case 0x2:
							case 0x3: // type pointer walk
								{
									int walkOffset = arg3 & 0x0FFFFFFF;
									if (comm3 == 0x3) {
										walkOffset = -walkOffset;
									}
									base = Memory::Read_U32(base + walkOffset);
									int comm4 = arg4 >> 28;
									switch (comm4) {
									case 0x2:
									case 0x3: // type pointer walk
										walkOffset = arg4 & 0x0FFFFFFF;
										if (comm4 == 0x3) {
											walkOffset = -walkOffset;
										}
										base = Memory::Read_U32(base + walkOffset);
										break;
									}
									break; }
							case 0x9: // type multi address write
								base += arg3 & 0x0FFFFFFF;
								arg += arg4;
								break;
							}
						}
					}

					switch (type) {
					case 0: // 8 bit write
						Memory::Write_U8((u8) arg, base + offset);
						break;
					case 1: // 16-bit write
						Memory::Write_U16((u16) arg, base + offset);
						break;
					case 2: // 32-bit write
						Memory::Write_U32((u32) arg, base + offset);
						break;
					case 3: // 8 bit inverse write
						Memory::Write_U8((u8) arg, base - offset);
						break;
					case 4: // 16-bit inverse write
						Memory::Write_U16((u16) arg, base - offset);
						break;
					case 5: // 32-bit inverse write
						Memory::Write_U32((u32) arg, base - offset);
						break;
					case -1: // Operation already performed, nothing to do
						break;
					}
				}
				break;
			case 0x7: // Boolean commands.
				switch (arg >> 16) {
				case 0x0000: // 8-bit OR.
					if (Memory::IsValidAddress(addr)) {
						int val1 = (int) (arg & 0xFF);
						int val2 = (int) Memory::Read_U8(addr);
						Memory::Write_U8((u8) (val1 | val2), addr);
					}
					break;
				case 0x0002: // 8-bit AND.
					if (Memory::IsValidAddress(addr)) {
						int val1 = (int) (arg & 0xFF);
						int val2 = (int) Memory::Read_U8(addr);
						Memory::Write_U8((u8) (val1 & val2), addr);
					}
					break;
				case 0x0004: // 8-bit XOR.
					if (Memory::IsValidAddress(addr)) {
						int val1 = (int) (arg & 0xFF);
						int val2 = (int) Memory::Read_U8(addr);
						Memory::Write_U8((u8) (val1 ^ val2), addr);
					}
					break;
				case 0x0001: // 16-bit OR.
					if (Memory::IsValidAddress(addr)) {
						short val1 = (short) (arg & 0xFFFF);
						short val2 = (short) Memory::Read_U16(addr);
						Memory::Write_U16((u16) (val1 | val2), addr);
					}
					break;
				case 0x0003: // 16-bit AND.
					if (Memory::IsValidAddress(addr)) {
						short val1 = (short) (arg & 0xFFFF);
						short val2 = (short) Memory::Read_U16(addr);
						Memory::Write_U16((u16) (val1 & val2), addr);
					}
					break;
				case 0x0005: // 16-bit OR.
					if (Memory::IsValidAddress(addr)) {
						short val1 = (short) (arg & 0xFFFF);
						short val2 = (short) Memory::Read_U16(addr);
						Memory::Write_U16((u16) (val1 ^ val2), addr);
					}
					break;
				}
				break;
			case 0x8: // 8-bit and 16-bit patch code
				code = GetNextCode();
				if (code[0] != NULL) {
					int data = code[0];
					int dataAdd = code[1];

					bool is8Bit = (data >> 16) == 0x0000;
					int maxAddr = (arg >> 16) & 0xFFFF;
					int stepAddr = (arg & 0xFFFF) * (is8Bit ? 1 : 2);
					for (int a = 0; a < maxAddr; a++) {
						if (Memory::IsValidAddress(addr)) {
							if (is8Bit) {
								Memory::Write_U8((u8) (data & 0xFF), addr);
							}
							else {
								Memory::Write_U16((u16) (data & 0xFFFF), addr);
							}
						}
						addr += stepAddr;
						data += dataAdd;
					}
				}
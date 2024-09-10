static void _writeRegister(struct GDBStub* stub, const char* message) {
	struct ARMCore* cpu = stub->d.core->cpu;
	const char* readAddress = message;

	unsigned i = 0;
	uint32_t reg = _readHex(readAddress, &i);
	readAddress += i + 1;

	uint32_t value = _readHex(readAddress, &i);

#ifdef _MSC_VER
	value = _byteswap_ulong(value);
#else
	value = __builtin_bswap32(value);
#endif

	if (reg <= ARM_PC) {
		cpu->gprs[reg] = value;
		if (reg == ARM_PC) {
			int32_t currentCycles = 0;
			if (cpu->executionMode == MODE_ARM) {
				ARM_WRITE_PC;
			} else {
				THUMB_WRITE_PC;
			}
		}
	} else if (reg == 0x19) {
		cpu->cpsr.packed = value;
	} else {
		stub->outgoing[0] = '\0';
		_sendMessage(stub);
		return;
	}

	strncpy(stub->outgoing, "OK", GDB_STUB_MAX_LINE - 4);
	_sendMessage(stub);
}
/**
 * @brief Tries to construct a trampoline from original code.
 *
 * A trampoline is the replacement code that features the original code plus
 * a jump back to the original instructions that follow.
 * It is called to execute the original behavior. As it is a replacement for
 * the original, the original can then be overwritten.
 * The size of the trampoline is at least CODEREPLACESIZE. Thus, CODEREPLACESIZE
 * bytes of the original code can afterwards be overwritten (and the trampoline
 * called after those instructions for the original logic).
 * CODEREPLACESIZE has to be smaller than CODEPROTECTSIZE.
 *
 * As commands must not be destroyed they have to be disassembled to get their length.
 * All encountered commands will be part of the trampoline and stored in pCode (shared
 * for all trampolines).
 *
 * If code is encountered that can not be moved into the trampoline (conditionals etc.)
 * construction fails and NULL is returned. If enough commands can be saved the
 * trampoline is finalized by appending a jump back to the original code. The return value
 * in this case will be the address of the newly constructed trampoline.
 *
 * pCode + offset to trampoline:
 *     [SAVED CODE FROM ORIGINAL which is >= CODEREPLACESIZE bytes][JUMP BACK TO ORIGINAL CODE]
 *
 * @param porig Original code
 * @return Pointer to trampoline on success. NULL if trampoline construction failed.
 */
void *HardHook::cloneCode(void **porig) {

	if (! pCode || uiCode > 4000) {
		pCode = VirtualAlloc(NULL, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		uiCode = 0;
	}
	// If we have no memory to clone to, return.
	if (! pCode) {
		return NULL;
	}

	unsigned char *o = (unsigned char *) *porig;
	unsigned char *n = (unsigned char *) pCode;
	n += uiCode;
	unsigned int idx = 0;

	DWORD origProtect;
	if (!VirtualProtect(o, CODEPROTECTSIZE, PAGE_EXECUTE_READ, &origProtect)) {
		fods("HardHook: CloneCode failed; failed to make original code read and executable");
		return NULL;
	}

	// Follow relative jumps to next instruction. On execution it doesn't make
	// a difference if we actually perform all the jumps or directly jump to the
	// end of the chain. Hence these jumps need not be part of the trampoline.
	while (*o == 0xe9) { // JMP
		unsigned char *tmp = o;
		int *iptr = reinterpret_cast<int *>(o+1);
		o += *iptr + 5;

		fods("HardHook: CloneCode: Skipping jump from %p to %p", *porig, o);
		*porig = o;

		// Assume jump took us out of our read enabled zone, get rights for the new one
		DWORD tempProtect;
		VirtualProtect(tmp, CODEPROTECTSIZE, origProtect, &tempProtect);
		if (!VirtualProtect(o, CODEPROTECTSIZE, PAGE_EXECUTE_READ, &origProtect)) {
			fods("HardHook: CloneCode failed; failed to make jump target code read and executable");
			return NULL;
		}
	}

	do {
		unsigned char opcode = o[idx];
		unsigned char a = o[idx+1];
		unsigned char b = o[idx+2];
		unsigned int extra = 0;

		n[idx] = opcode;
		++idx;

		switch (opcode) {
			case 0x50: // PUSH
			case 0x51:
			case 0x52:
			case 0x53:
			case 0x54:
			case 0x55:
			case 0x56:
			case 0x57:
			case 0x58: // POP
			case 0x59:
			case 0x5a:
			case 0x5b:
			case 0x5c:
			case 0x5d:
			case 0x5e:
			case 0x5f:
				break;
			case 0x6a: // PUSH immediate
				extra = 1;
				break;
			case 0x68: // PUSH immediate
				extra = 4;
				break;
			case 0x81: // CMP immediate
				extra = modrmbytes(a,b) + 5;
				break;
			case 0x83:	// CMP
				extra = modrmbytes(a,b) + 2;
				break;
			case 0x8b:	// MOV
				extra = modrmbytes(a,b) + 1;
				break;
			default: {
				int rmop = ((a>>3) & 7);
				if (opcode == 0xff && rmop == 6) { // PUSH memory
					extra = modrmbytes(a,b) + 1;
					break;
				}

				fods("HardHook: CloneCode failed; Unknown opcode at %d: %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x",
						idx-1, o[0], o[1], o[2], o[3], o[4], o[5], o[6], o[7], o[8], o[9], o[10], o[11]);
				DWORD tempProtect;
				VirtualProtect(o, CODEPROTECTSIZE, origProtect, &tempProtect);
				return NULL;
				break;
			}
		}

		for (unsigned int i = 0; i < extra; ++i)
			n[idx+i] = o[idx+i];
		idx += extra;

	} while (idx < CODEREPLACESIZE);

	DWORD tempProtect;
	VirtualProtect(o, CODEPROTECTSIZE, origProtect, &tempProtect);

	// Add a relative jmp back to the original code
	n[idx++] = 0xe9;
	int *iptr = reinterpret_cast<int *>(&n[idx]);
	int offs = o - n - 5;
	*iptr = offs;
	idx += 4;

	uiCode += idx;

	FlushInstructionCache(GetCurrentProcess(), n, idx);

	fods("HardHook: trampoline creation successful at %p", n);

	return n;
}
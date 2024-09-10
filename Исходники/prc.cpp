	Byte Processor::execInstruction() {
#ifdef R_UM_OPT_ENABLE_LOGGING
#ifdef R_UM_OPT_PRC_DEBUG
		ic_ ++;
#endif
#endif
		Word instr = (*mm_)(0, pc_ ++);
		switch (decodeInstruction(instr)) {
			case IC_CNDMOV:
				return CNDMOV(decodeAreg(instr), decodeBreg(instr),
						decodeCreg(instr));
			case IC_ARRIDX:
				return ARRIDX(decodeAreg(instr), decodeBreg(instr),
						decodeCreg(instr));
			case IC_ARRAMD:
				return ARRAMD(decodeAreg(instr), decodeBreg(instr),
						decodeCreg(instr));
			case IC_ADD:
				return ADD(decodeAreg(instr), decodeBreg(instr),
						decodeCreg(instr));
			case IC_MUL:
				return MUL(decodeAreg(instr), decodeBreg(instr),
						decodeCreg(instr));
			case IC_DIV:
				return DIV(decodeAreg(instr), decodeBreg(instr),
						decodeCreg(instr));
			case IC_NOTAND:
				return NOTAND(decodeAreg(instr), decodeBreg(instr),
						decodeCreg(instr));

			case IC_HLT:
				return HLT();
			case IC_ALLOC:
				return ALLOC(decodeBreg(instr), decodeCreg(instr));
			case IC_ABAND:
				return ABAND(decodeCreg(instr));
			case IC_OUTP:
				return OUTP(decodeCreg(instr));
			case IC_INP:
				return INP(decodeCreg(instr));
			case IC_LDPRG:
				return LDPRG(decodeBreg(instr), decodeCreg(instr));

			case IC_ORTHO:
				return ORTHO(decodeOreg(instr), decodeVal(instr));

			default:
				assert(false);
				return HLT();
		}
	}
int SuFunction::disasm1(Ostream& out, int ci) {
	verify(locals);
	verify(literals);
	out << "\t\t\t\t\t" << setw(3) << ci << "  ";
	short op = code[ci++];
	//	out << hex << setw(3) << op << " " << dec;
	out << opcodes[op] << " ";
	if (op == I_SUPER) {
		out << globals(TARGET(ci));
		ci += 2;
	} else if (op == I_EACH)
		out << (int) code[ci++];
	else if (op == I_BLOCK) {
		out << ci + 2 + TARGET(ci);
		ci += 2;
		int first = code[ci++];
		int nargs = code[ci++];
		for (int i = 0; i < nargs; ++i)
			out << " " << 1 + symstr(locals[first + i]);
	} else if (op == I_PUSH_INT) {
		out << TARGET(ci);
		ci += 2;
	} else if (op < 16 || op == I_BOOL)
		;
	else if (op < I_PUSH) {
		switch (op & 0xf0) {
		case I_PUSH_LITERAL:
			out << literals[op & 15];
			break;
		case I_PUSH_AUTO:
			out << symstr(locals[op & 15]);
			break;
		case I_EQ_AUTO:
		case I_EQ_AUTO_POP:
			out << symstr(locals[op & 7]);
			break;
		case I_CALL_GLOBAL:
			out << globals(TARGET(ci)) << " " << (op & 7);
			ci += 2;
			break;
		case I_CALL_MEM:
		case I_CALL_MEM_SELF:
			out << mem(ci) << " " << (op & 7);
			break;
		default:
			break;
		}
	} else if ((op & 0xf8) == I_PUSH) {
		switch (op & 7) {
		case LITERAL:
			out << literals[varint(code, ci)];
			break;
		case AUTO:
		case DYNAMIC:
			out << symstr(locals[code[ci++]]);
			break;
		case MEM:
		case MEM_SELF:
			out << mem(ci);
			break;
		case GLOBAL:
			out << globals(TARGET(ci));
			ci += 2;
			break;
		default:
			break;
		}
	} else if ((op & 0xf8) == I_CALL) {
		switch (op & 7) {
		case AUTO:
		case DYNAMIC:
			out << symstr(locals[code[ci++]]);
			break;
		case MEM:
		case MEM_SELF:
			out << mem(ci);
			ci += 2;
			break;
		case GLOBAL:
			out << globals(TARGET(ci));
			ci += 2;
			break;
		default:
			break;
		}
		out << " " << (short) code[ci++];
		short nargnames = code[ci++];
		out << " " << nargnames;
		for (int i = 0; i < nargnames; ++i) {
			out << " " << symstr(TARGET(ci));
			ci += 2;
		}
	} else if ((op & 0xf8) == I_JUMP || op == I_TRY || op == I_CATCH) {
		out << ci + 2 + TARGET(ci);
		ci += 2;
		if (op == I_TRY)
			out << " " << literals[varint(code, ci)];
	} else if (I_ADDEQ <= op && op < I_ADD) {
		switch ((op & 0x70) >> 4) {
		case AUTO:
		case DYNAMIC:
			out << symstr(locals[code[ci++]]);
			break;
		case MEM:
		case MEM_SELF:
			out << mem(ci);
			break;
		default:
			break;
		}
	}
	out << "\n";
	return ci;
}
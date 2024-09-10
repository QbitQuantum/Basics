void CEException::dumpContext(HANDLE file, HANDLE hProcess, CONTEXT *context) {
	char tempo[200];
	unsigned char memoryDump[100];
	DWORD size;
	unsigned int i;

#ifdef ARM
	writeBreak(file);
	writeString(file, "Context dump");
	sprintf(tempo, "R0=%.8x R1=%.8x R2=%.8x R3=%.8x R4=%.8x", context->R0, context->R1,
	        context->R2, context->R3, context->R4);
	writeString(file, tempo);
	sprintf(tempo, "R5=%.8x R6=%.8x R7=%.8x R8=%.8x R9=%.8x", context->R5, context->R6,
	        context->R7, context->R8, context->R9);
	writeString(file, tempo);
	sprintf(tempo, "R10=%.8x R11=%.8x R12=%.8x", context->R10, context->R11,
	        context->R12);
	writeString(file, tempo);
	sprintf(tempo, "Sp=%.8x Lr=%.8x Pc=%.8x Psr=%.8x", context->Sp, context->Lr,
	        context->Pc, context->Psr);
	writeString(file, tempo);
	writeBreak(file);

	sprintf(tempo, "Memory dump at %.8x", context->Pc - (sizeof(memoryDump) / 2));
	writeString(file, tempo);
	if (ReadProcessMemory(hProcess, (LPCVOID)(context->Pc - (sizeof(memoryDump) / 2)), memoryDump, sizeof(memoryDump), &size)) {
		for (i = 0; i < size; i += 8) {
			int j;
			char digit[4];
			int max;
			max = size - i;
			if (max > 8)
				max = 8;
			tempo[0] = '\0';
			for (j = 0; j < max; j++) {
				sprintf(digit, "%.2x ", memoryDump[i + j]);
				strcat(tempo, digit);
			}
			writeString(file, tempo);
		}
	}
#else
	writeBreak(file);
	writeString(file, "Context dump only available on ARM devices");
#endif
}
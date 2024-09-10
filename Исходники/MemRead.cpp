/*
DWORD MemRead::ReadPointer(DWORD base, DWORD* offset, int count)
{
	for (int i = 0; i < count - 1; i++)
	{
		base = ReadMem(base + offset[i], 4).toUINT16;  // читаем по 4 байта так как адреса занимают 32 битные 4 байта, и приводим к UINT32
	}
	return base + offset[count - 1]; count - 1 - для того что бы возвращать адрес, а не значение
}   
*/
DWORD MemRead::Alloc(DWORD memProtect) { return (DWORD)VirtualAllocEx(m_hProc, NULL, 0x1000, MEM_COMMIT | MEM_RESERVE, memProtect);}
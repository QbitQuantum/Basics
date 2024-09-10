DWORD GetHWIDchunk(int chunk)
{	VU("GetHWIDchunk");

	int res = -1;

	switch (chunk)
	{
	case 1:
		{
			//CPUID
			char cpudata[0x50];
			memset(cpudata, 0, 0x50);
				
			__asm
			{
				pushad
				lea edi, cpudata
				add edi, 0x4C
				mov esi, 0x80000004

				mov eax, 0x80000000
				cpuid
				cmp eax, esi
				jl errora
			loopa:
				mov eax, esi
				cpuid

				mov [edi], edx
				mov [edi-4], ecx
				mov [edi-8], ebx
				mov [edi-12], eax
				sub edi, 0x10

				dec esi
				cmp esi, 0x7FFFFFFF
				jne loopa

				mov res, 1
				jmp exita
			errora:
				mov res, 0
			exita:
				popad
			}

			PrintBuffer((BYTE *)cpudata, 0x50, 16);
			info("GetHWIDchunk(%d) %d res", chunk, res);

			if (res = 1) return GetCRC32(cpudata, 0x50);
		
			info("GetHWIDchunk() Fail, returning default for request %d.", chunk);
			return 0xBAADD00D;
		}
		break;
	case 2:
		{
			//windows installation date
			char windir[256];
			memset(windir, 0, 256);
			GetWindowsDirectoryA(windir, 255);
			info("GetHWIDchunk()  Windows folder = %s", windir);

			struct _stat32 f_stats; 

			if (_stat32(windir, &f_stats) == 0)
			{
				char timebuf[256];
				_ctime32_s(timebuf, 26, &f_stats.st_ctime);
				info("GetHWIDchunk() Windows folder (%s) creation date = %s", windir, timebuf);

				if (strstr(timebuf, V(" 201")) == NULL && strstr(timebuf, V(" 200")) == NULL) return 0xBAADD00D;

				return f_stats.st_ctime ^ GetCRC32(windir, 20);
			}


			info("GetHWIDchunk() Fail, returning default for request %d.", chunk);
			return 0xBAADD00D;
		}
		break;
	case 3:
		{
			char compname[256];
			memset(compname, 0, 256);
			DWORD maxlen = 256;
			GetComputerNameA(compname, &maxlen);

			return GetCRC32(compname, sizeof(compname));
		}
		break;
	default:
		return 0;
	}

	return 0;

	VE();
}
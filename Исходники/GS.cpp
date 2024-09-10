EXPORT_C GSBenchmark(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow)
{
	::SetPriorityClass(::GetCurrentProcess(), HIGH_PRIORITY_CLASS);

	FILE* file = fopen("c:\\temp1\\log.txt", "a");

	fprintf(file, "-------------------------\n\n");

	if(1)
	{
		GSLocalMemory * pMem = new GSLocalMemory();
		GSLocalMemory& mem(*pMem);
		

		static struct {int psm; const char* name;} s_format[] =
		{
			{PSM_PSMCT32, "32"},
			{PSM_PSMCT24, "24"},
			{PSM_PSMCT16, "16"},
			{PSM_PSMCT16S, "16S"},
			{PSM_PSMT8, "8"},
			{PSM_PSMT4, "4"},
			{PSM_PSMT8H, "8H"},
			{PSM_PSMT4HL, "4HL"},
			{PSM_PSMT4HH, "4HH"},
			{PSM_PSMZ32, "32Z"},
			{PSM_PSMZ24, "24Z"},
			{PSM_PSMZ16, "16Z"},
			{PSM_PSMZ16S, "16ZS"},
		};

		uint8* ptr = (uint8*)_aligned_malloc(1024 * 1024 * 4, 32);

		for(int i = 0; i < 1024 * 1024 * 4; i++) ptr[i] = (uint8)i;

		//

		for(int tbw = 5; tbw <= 10; tbw++)
		{
			int n = 256 << ((10 - tbw) * 2);

			int w = 1 << tbw;
			int h = 1 << tbw;

			fprintf(file, "%d x %d\n\n", w, h);

			for(size_t i = 0; i < countof(s_format); i++)
			{
				const GSLocalMemory::psm_t& psm = GSLocalMemory::m_psm[s_format[i].psm];

				GSLocalMemory::writeImage wi = psm.wi;
				GSLocalMemory::readImage ri = psm.ri;
				GSLocalMemory::readTexture rtx = psm.rtx;
				GSLocalMemory::readTexture rtxP = psm.rtxP;

				GIFRegBITBLTBUF BITBLTBUF;

				BITBLTBUF.SBP = 0;
				BITBLTBUF.SBW = w / 64;
				BITBLTBUF.SPSM = s_format[i].psm;
				BITBLTBUF.DBP = 0;
				BITBLTBUF.DBW = w / 64;
				BITBLTBUF.DPSM = s_format[i].psm;

				GIFRegTRXPOS TRXPOS;

				TRXPOS.SSAX = 0;
				TRXPOS.SSAY = 0;
				TRXPOS.DSAX = 0;
				TRXPOS.DSAY = 0;

				GIFRegTRXREG TRXREG;

				TRXREG.RRW = w;
				TRXREG.RRH = h;

				GSVector4i r(0, 0, w, h);

				GIFRegTEX0 TEX0;

				TEX0.TBP0 = 0;
				TEX0.TBW = w / 64;

				GIFRegTEXA TEXA;

				TEXA.TA0 = 0;
				TEXA.TA1 = 0x80;
				TEXA.AEM = 0;

				int trlen = w * h * psm.trbpp / 8;
				int len = w * h * psm.bpp / 8;

				clock_t start, end;

				_ftprintf(file, _T("[%4s] "), s_format[i].name);

				start = clock();

				for(int j = 0; j < n; j++)
				{
					int x = 0;
					int y = 0;

					(mem.*wi)(x, y, ptr, trlen, BITBLTBUF, TRXPOS, TRXREG);
				}

				end = clock();

				fprintf(file, "%6d %6d | ", (int)((float)trlen * n / (end - start) / 1000), (int)((float)(w * h) * n / (end - start) / 1000));

				start = clock();

				for(int j = 0; j < n; j++)
				{
					int x = 0;
					int y = 0;

					(mem.*ri)(x, y, ptr, trlen, BITBLTBUF, TRXPOS, TRXREG);
				}

				end = clock();

				fprintf(file, "%6d %6d | ", (int)((float)trlen * n / (end - start) / 1000), (int)((float)(w * h) * n / (end - start) / 1000));

				const GSOffset* o = mem.GetOffset(TEX0.TBP0, TEX0.TBW, TEX0.PSM);

				start = clock();

				for(int j = 0; j < n; j++)
				{
					(mem.*rtx)(o, r, ptr, w * 4, TEXA);
				}

				end = clock();

				fprintf(file, "%6d %6d ", (int)((float)len * n / (end - start) / 1000), (int)((float)(w * h) * n / (end - start) / 1000));

				if(psm.pal > 0)
				{
					start = clock();

					for(int j = 0; j < n; j++)
					{
						(mem.*rtxP)(o, r, ptr, w, TEXA);
					}

					end = clock();

					fprintf(file, "| %6d %6d ", (int)((float)len * n / (end - start) / 1000), (int)((float)(w * h) * n / (end - start) / 1000));
				}

				fprintf(file, "\n");

				fflush(file);
			}

			fprintf(file, "\n");
		}

		_aligned_free(ptr);
		delete pMem;
	}

	//

	if(0)
	{
		GSLocalMemory * pMem2 = new GSLocalMemory();
		GSLocalMemory& mem2(*pMem2);

		uint8* ptr = (uint8*)_aligned_malloc(1024 * 1024 * 4, 32);

		for(int i = 0; i < 1024 * 1024 * 4; i++) ptr[i] = (uint8)i;

		const GSLocalMemory::psm_t& psm = GSLocalMemory::m_psm[PSM_PSMCT32];

		GSLocalMemory::writeImage wi = psm.wi;

		GIFRegBITBLTBUF BITBLTBUF;

		BITBLTBUF.DBP = 0;
		BITBLTBUF.DBW = 32;
		BITBLTBUF.DPSM = PSM_PSMCT32;

		GIFRegTRXPOS TRXPOS;

		TRXPOS.DSAX = 0;
		TRXPOS.DSAY = 1;

		GIFRegTRXREG TRXREG;

		TRXREG.RRW = 256;
		TRXREG.RRH = 256;

		int trlen = 256 * 256 * psm.trbpp / 8;

		int x = 0;
		int y = 0;

		(mem2.*wi)(x, y, ptr, trlen, BITBLTBUF, TRXPOS, TRXREG);
		delete pMem2;
	}

	//

	fclose(file);
	PostQuitMessage(0);
}
/* ========================================================================= */
int test_add16s_func(void)
{
	INT16 ALIGN(src1[FUNC_TEST_SIZE+3]), ALIGN(src2[FUNC_TEST_SIZE+3]), 
		ALIGN(d1[FUNC_TEST_SIZE+3]), ALIGN(d2[FUNC_TEST_SIZE+3]);
	int failed = 0;
#if defined(WITH_SSE2) || defined(WITH_IPP)
	int i;
#endif
	char testStr[256];

	testStr[0] = '\0';
	get_random_data(src1, sizeof(src1));
	get_random_data(src2, sizeof(src2));
	memset(d1, 0, sizeof(d1));
	memset(d2, 0, sizeof(d2));
	general_add_16s(src1+1, src2+1, d1+1, FUNC_TEST_SIZE);
#ifdef WITH_SSE2
	if(IsProcessorFeaturePresent(PF_SSE3_INSTRUCTIONS_AVAILABLE))
	{
		strcat(testStr, " SSE3");
		/* Aligned */
		sse3_add_16s(src1+1, src2+1, d2+1, FUNC_TEST_SIZE);
		for (i=1; i<FUNC_TEST_SIZE; ++i)
		{
			if (d1[i] != d2[i])
			{ 
				printf("ADD16S-SSE-aligned FAIL[%d] %d+%d=%d, got %d\n", 
					i, src1[i], src2[i], d1[i], d2[i]); 
				++failed;
			}
		}
		/* Unaligned */
		sse3_add_16s(src1+1, src2+1, d2+2, FUNC_TEST_SIZE);
		for (i=1; i<FUNC_TEST_SIZE; ++i)
		{
			if (d1[i] != d2[i+1])
			{ 
				printf("ADD16S-SSE-unaligned FAIL[%d] %d+%d=%d, got %d\n", 
					i, src1[i], src2[i], d1[i], d2[i+1]); 
				++failed;
			}
		}
	}
#endif
#ifdef WITH_IPP
	strcat(testStr, " IPP");
	ippsAdd_16s(src1+1, src2+1, d2+1, FUNC_TEST_SIZE);
	for (i=1; i<FUNC_TEST_SIZE; ++i)
	{
		if (d1[i] != d2[i])
		{ 
			printf("ADD16S-IPP FAIL[%d] %d+%d=%d, got %d\n", 
				i, src1[i], src2[i], d1[i], d2[i]); 
			++failed;
		}
	}
#endif /* WITH_IPP */
	if (!failed) printf("All add16s tests passed (%s).\n", testStr);
	return (failed > 0) ? FAILURE : SUCCESS;
}
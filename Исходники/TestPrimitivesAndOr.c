/* ========================================================================= */
int test_and_32u_func(void)
{
	UINT32 ALIGN(src[FUNC_TEST_SIZE+3]), ALIGN(dst[FUNC_TEST_SIZE+3]);
	int failed = 0;
	int i;
	char testStr[256];

	testStr[0] = '\0';
	get_random_data(src, sizeof(src));
	general_andC_32u(src+1, VALUE, dst+1, FUNC_TEST_SIZE);
	strcat(testStr, " general");
	for (i=1; i<=FUNC_TEST_SIZE; ++i)
	{
		if (dst[i] != (src[i] & VALUE))
		{ 
			printf("AND-general FAIL[%d] 0x%08x&0x%08x=0x%08x, got 0x%08x\n", 
				i, src[i], VALUE, src[i] & VALUE, dst[i]); 
			++failed;
		}
	}
#ifdef WITH_SSE2
	if (IsProcessorFeaturePresent(PF_SSE3_INSTRUCTIONS_AVAILABLE))
	{
		strcat(testStr, " SSE3");
		/* Aligned */
		memset(dst, 0, sizeof(dst));
		sse3_andC_32u(src+1, VALUE, dst+1, FUNC_TEST_SIZE);
		for (i=1; i<=FUNC_TEST_SIZE; ++i)
		{
			if (dst[i] != (src[i] & VALUE))
			{ 
				printf("AND-SSE-aligned FAIL[%d] 0x%08x&0x%08x=0x%08x, got 0x%08x\n", 
					i, src[i], VALUE, src[i] & VALUE, dst[i]); 
				++failed;
			}
		}
		/* Unaligned */
		memset(dst, 0, sizeof(dst));
		sse3_andC_32u(src+1, VALUE, dst+2, FUNC_TEST_SIZE);
		for (i=1; i<=FUNC_TEST_SIZE; ++i)
		{
			if (dst[i+1] != (src[i] & VALUE))
			{ 
				printf("AND-SSE-unaligned FAIL[%d] 0x%08x&0x%08x=0x%08x, got 0x%08x\n", 
					i, src[i], VALUE, src[i] & VALUE, dst[i+1]); 
				++failed;
			}
		}
	}
#endif /* i386 */
	if (!failed) printf("All and_32u tests passed (%s).\n", testStr);
	return (failed > 0) ? FAILURE : SUCCESS;
}
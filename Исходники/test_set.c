/* ------------------------------------------------------------------------- */
int test_set8u_func(void)
{
#if defined(WITH_SSE2) || defined(WITH_IPP)
	BYTE ALIGN(dest[48]);
	int off;
#endif
	int failed = 0;
	char testStr[256];
	testStr[0] = '\0';

#ifdef WITH_SSE2
	/* Test SSE under various alignments */
	if (IsProcessorFeaturePresent(PF_SSE2_INSTRUCTIONS_AVAILABLE))
	{
		strcat(testStr, " SSE2");
		for (off=0; off<16; ++off)
		{
			int len;
			for (len=1; len<48-off; ++len)
			{
				int i;
				memset(dest, 0, sizeof(dest));
				sse2_set_8u(0xa5, dest+off, len);
				for (i=0; i<len; ++i)
				{
					if (dest[off+i] != 0xa5)
					{
						printf("SET8U-SSE FAILED: off=%d len=%d dest[%d]=0x%02x\n",
							off, len, i+off, dest[i+off]);
						failed=1;
					}
				}
			}
		}
	}
#endif /* i386 */

#ifdef WITH_IPP
	/* Test IPP under various alignments */
	strcat(testStr, " IPP");
	for (off=0; off<16; ++off)
	{
		int len;
		for (len=1; len<48-off; ++len)
		{
			int i;
			memset(dest, 0, sizeof(dest));
			ippsSet_8u(0xa5, dest+off, len);
			for (i=0; i<len; ++i)
			{
				if (dest[off+i] != 0xa5)
				{
					printf("SET8U-IPP FAILED: off=%d len=%d dest[%d]=0x%02x\n",
						off, len, i+off, dest[i+off]);
					failed=1;
				}
			}
		}
	}
#endif /* WITH_IPP */

	if (!failed) printf("All set8u tests passed (%s).\n", testStr);
	return (failed > 0) ? FAILURE : SUCCESS;
}
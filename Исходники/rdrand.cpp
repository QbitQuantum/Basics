static int ALL_RSI_GenerateBlock(byte *output, size_t size, unsigned int safety)
{
	assert((output && size) || !(output || size));
#if CRYPTOPP_BOOL_X86 || CRYPTOPP_BOOL_X32
	word32 val;
#else
	word64 val;
#endif

	while (size >= sizeof(val))
	{
#if CRYPTOPP_BOOL_X86 || CRYPTOPP_BOOL_X32
		if (_rdseed32_step((word32*)output))
#else
		if (_rdseed64_step((word64*)output))
#endif
		{
			output += sizeof(val);
			size -= sizeof(val);
		}
		else
		{
			if (!safety--)
			{
				assert(0);
				return 0;
			}
		}
	}

	if (size)
	{
#if CRYPTOPP_BOOL_X86 || CRYPTOPP_BOOL_X32
		if (_rdseed32_step(&val))
#else
		if (_rdseed64_step(&val))
#endif
		{
			memcpy(output, &val, size);
			size = 0;
		}
		else
		{
			if (!safety--)
			{
				assert(0);
				return 0;
			}
		}
	}

	SecureWipeBuffer(&val, 1);

	return int(size == 0);
}
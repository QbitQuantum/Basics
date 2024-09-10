				valid = 0;	/* invalid value */
			}
		}

		if (valid)
		{
			int M = (value & 0xFF000000) >> 24;		/* Major */
			int m = (value & 0x00FF0000) >> 16;		/* Minor */
			int b = (value & 0x0000FFFF);			/* build */
			printf(GREEN "%d.%d.%d\n" NORMAL, M, m, b);
		}
	}

	printf("Testing SCardGetAttrib\t\t: ");
	dwBufLen = sizeof(buf);
	rv = SCardGetAttrib(hCard, SCARD_ATTR_MAXINPUT, buf.as_char, &dwBufLen);
	test_rv(rv, hContext, DONT_PANIC);
	if (rv == SCARD_S_SUCCESS)
	{
		if (dwBufLen == sizeof(uint32_t))
			printf("Max message length\t\t: " GREEN "%d\n" NORMAL,
				buf.as_uint32_t);
		else
			printf(RED "Wrong size" NORMAL);
	}

	printf("Testing SCardGetAttrib\t\t: ");
	dwBufLen = sizeof(buf);
	rv = SCardGetAttrib(hCard, SCARD_ATTR_VENDOR_NAME, buf.as_char, &dwBufLen);
	test_rv(rv, hContext, DONT_PANIC);
	if (rv == SCARD_S_SUCCESS)
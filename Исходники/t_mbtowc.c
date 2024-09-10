static void
h_mbtowc(const char *locale, const char *illegal, const char *legal)
{
	char buf[64];
	size_t stateful, ret;
	char *str;

	ATF_REQUIRE_STREQ(setlocale(LC_ALL, "C"), "C");
#ifdef __NetBSD__
	ATF_REQUIRE(setlocale(LC_CTYPE, locale) != NULL);
#else
	if (setlocale(LC_CTYPE, locale) == NULL) {
		fprintf(stderr, "Locale %s not found.\n", locale);
		return;
	}
#endif

	ATF_REQUIRE((str = setlocale(LC_ALL, NULL)) != NULL);
	(void)printf("Using locale: %s\n", str);

	stateful = wctomb(NULL, L'\0');
	(void)printf("Locale is state-%sdependent\n",
		stateful ? "in" : "");

	/* initialize internal state */
	ret = mbtowc(NULL, NULL, 0);
	ATF_REQUIRE(stateful ? ret : !ret);

	(void)strvis(buf, illegal, VIS_WHITE | VIS_OCTAL);
	(void)printf("Checking illegal sequence: \"%s\"\n", buf);

	ret = mbtowc(NULL, illegal, strlen(illegal));
	(void)printf("mbtowc() returned: %zd\n", ret);
	ATF_REQUIRE_EQ(ret, (size_t)-1);
	(void)printf("errno: %s\n", strerror(errno));
	ATF_REQUIRE_EQ(errno, EILSEQ);

	/* if this is stateless encoding, this re-initialization is not required. */
	if (stateful) {
		/* re-initialize internal state */
		ret = mbtowc(NULL, NULL, 0);
		ATF_REQUIRE(stateful ? ret : !ret);
	}

	/* valid multibyte sequence case */
	(void)strvis(buf, legal, VIS_WHITE | VIS_OCTAL);
	(void)printf("Checking legal sequence: \"%s\"\n", buf);

	errno = 0;
	ret = mbtowc(NULL, legal, strlen(legal));
	(void)printf("mbtowc() returned: %zd\n", ret);
	ATF_REQUIRE(ret != (size_t)-1);
	(void)printf("errno: %s\n", strerror(errno));
	ATF_REQUIRE_EQ(errno, 0);

	(void)printf("Ok.\n");
}
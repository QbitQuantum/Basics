ATF_TC_BODY(positional_precision_wide, tc)
{

	swprintf(wbuf1, sizeof buf, L"%2$.*4$s %2$.*3$s %1$s",
		 "BSD", "bsd", 2, 1);
	temp = correct2;
	mbsrtowcs(wbuf2, &temp, nitems(wbuf2), NULL);
	ATF_REQUIRE_MSG(wcscmp(wbuf1, wbuf2) == 0,
	    "buffers didn't match");
}
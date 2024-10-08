void Fchar_equal(CL_FORM *base, int nargs)
{
	CL_FORM *rest_0;
	CL_FORM *local;
	rest_0 = ARG(1);
	local = ARG(nargs);
	{
		CL_FORM *rest_1;
		LOAD_NIL(LOCAL(0));
		rest_1 = rest_0;
		M1_1:;
		if(NOT(REST_NOT_EMPTY(rest_1)))
		{
			LOAD_NIL(LOCAL(0));
			LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(0));	/* T */
			goto RETURN1;
		}
		{
			CL_FORM *rest_2;
			rest_2 = rest_1;
			REST_CAR(rest_2, LOCAL(0));
		}
		{
			if(CL_CHARP(LOCAL(0)))
			{
				COPY(LOCAL(0), LOCAL(1));
			}
			else
			{
				COPY(SYMVAL(Slisp, 58), LOCAL(1));	/* WRONG_TYPE */
				COPY(LOCAL(0), LOCAL(2));
				LOAD_SYMBOL(SYMBOL(Slisp, 18), LOCAL(3));	/* CHARACTER */
				Ferror(LOCAL(1), 3);
			}
			rt_char_upcase(LOCAL(1));
			rt_char_code(LOCAL(1));
		}
		{
			if(CL_CHARP(ARG(0)))
			{
				COPY(ARG(0), LOCAL(2));
			}
			else
			{
				COPY(SYMVAL(Slisp, 58), LOCAL(2));	/* WRONG_TYPE */
				COPY(ARG(0), LOCAL(3));
				LOAD_SYMBOL(SYMBOL(Slisp, 18), LOCAL(4));	/* CHARACTER */
				Ferror(LOCAL(2), 3);
			}
			rt_char_upcase(LOCAL(2));
			rt_char_code(LOCAL(2));
		}
		Fnumeql(LOCAL(1), 2);
		if(CL_TRUEP(LOCAL(1)))
		{
			LOAD_NIL(ARG(0));
			goto RETURN1;
		}
		{
			CL_FORM *rest_3;
			rest_3 = rest_1;
			rest_1 = REST_CDR(rest_3);
		}
		goto M1_1;
	}
	RETURN1:;
}
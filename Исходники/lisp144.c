void pathname_host1(CL_FORM *base)
{
	COPY(ARG(0), ARG(2));
	LOAD_SYMBOL(SYMBOL(Slisp, 232), ARG(3));	/* PATHNAME */
	rt_struct_typep(ARG(2));
	if(CL_TRUEP(ARG(2)))
	{
		COPY(ARG(0), ARG(2));
	}
	else
	{
		COPY(ARG(0), ARG(2));
		Fstringp(ARG(2));
		if(CL_TRUEP(ARG(2)))
		{
			COPY(ARG(0), ARG(2));
			LOAD_NIL(ARG(3));
			COPY(SYMVAL(Slisp, 231), ARG(4));	/* *DEFAULT-PATHNAME-DEFAULTS* */
			LOAD_SMALLFIXNUM(0, ARG(5));
			LOAD_NIL(ARG(6));
			LOAD_NIL(ARG(7));
			parse_namestring1(ARG(2));
			mv_count = 1;
		}
		else
		{
			COPY(ARG(0), ARG(2));
			LOAD_SYMBOL(SYMBOL(Slisp, 64), ARG(3));	/* STREAM */
			rt_struct_typep(ARG(2));
			if(CL_TRUEP(ARG(2)))
			{
				COPY(ARG(0), ARG(2));
				LOAD_NIL(ARG(3));
				file_name1(ARG(2));
				COPY(SYMVAL(Slisp, 231), ARG(3));	/* *DEFAULT-PATHNAME-DEFAULTS* */
				LOAD_SMALLFIXNUM(0, ARG(4));
				COPY(ARG(2), ARG(5));
				LOAD_NIL(ARG(6));
				COPY(ARG(3), ARG(7));
				COPY(ARG(4), ARG(8));
				LOAD_NIL(ARG(9));
				LOAD_NIL(ARG(10));
				parse_namestring1(ARG(5));
				mv_count = 1;
				COPY(ARG(5), ARG(2));
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&Kpathname_host1[0], ARG(2));	/* etypecase: the value ~a is not a legal value */
				COPY(ARG(0), ARG(3));
				Ferror(ARG(2), 2);
			}
		}
	}
	COPY(ARG(2), ARG(3));
	LOAD_SYMBOL(SYMBOL(Slisp, 232), ARG(4));	/* PATHNAME */
	rt_struct_typep(ARG(3));
	if(CL_TRUEP(ARG(3)))
	{
		COPY(OFFSET(AR_BASE(GET_FORM(ARG(2))), 0 + 1), ARG(0));
	}
	else
	{
		COPY(SYMVAL(Slisp, 342), ARG(0));	/* NO_STRUCT */
		COPY(ARG(2), ARG(1));
		LOAD_SYMBOL(SYMBOL(Slisp, 232), ARG(2));	/* PATHNAME */
		Ferror(ARG(0), 3);
	}
}
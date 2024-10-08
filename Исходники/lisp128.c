void pathname_name1(CL_FORM *base)
{
	COPY(ARG(0), ARG(2));
	LOAD_SYMBOL(SYMBOL(Slisp, 234), ARG(3));	/* PATHNAME */
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
			COPY(SYMVAL(Slisp, 233), ARG(4));	/* *DEFAULT-PATHNAME-DEFAULTS* */
			LOAD_FIXNUM(ARG(5), 0, ARG(5));
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
				COPY(SYMVAL(Slisp, 233), ARG(3));	/* *DEFAULT-PATHNAME-DEFAULTS* */
				COPY(ARG(2), ARG(4));
				LOAD_NIL(ARG(5));
				COPY(ARG(3), ARG(6));
				LOAD_FIXNUM(ARG(7), 0, ARG(7));
				LOAD_NIL(ARG(8));
				LOAD_NIL(ARG(9));
				parse_namestring1(ARG(4));
				mv_count = 1;
				COPY(ARG(4), ARG(2));
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&Kpathname_name1[0], ARG(2));	/* etypecase: the value ~a is not a legal value */
				COPY(ARG(0), ARG(3));
				Ferror(ARG(2), 2);
			}
		}
	}
	COPY(ARG(2), ARG(3));
	LOAD_SYMBOL(SYMBOL(Slisp, 234), ARG(4));	/* PATHNAME */
	rt_struct_typep(ARG(3));
	if(CL_TRUEP(ARG(3)))
	{
		COPY(OFFSET(AR_BASE(GET_FORM(ARG(2))), 3 + 1), ARG(3));
	}
	else
	{
		COPY(SYMVAL(Slisp, 352), ARG(3));	/* NO_STRUCT */
		COPY(ARG(2), ARG(4));
		LOAD_SYMBOL(SYMBOL(Slisp, 234), ARG(5));	/* PATHNAME */
		Ferror(ARG(3), 3);
	}
	if(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 278))	/* COMMON */
	{
		COPY(ARG(2), ARG(4));
		LOAD_SYMBOL(SYMBOL(Slisp, 234), ARG(5));	/* PATHNAME */
		rt_struct_typep(ARG(4));
		if(CL_TRUEP(ARG(4)))
		{
			COPY(OFFSET(AR_BASE(GET_FORM(ARG(2))), 0 + 1), ARG(4));
		}
		else
		{
			COPY(SYMVAL(Slisp, 352), ARG(4));	/* NO_STRUCT */
			COPY(ARG(2), ARG(5));
			LOAD_SYMBOL(SYMBOL(Slisp, 234), ARG(6));	/* PATHNAME */
			Ferror(ARG(4), 3);
		}
		COPY(ARG(4), ARG(5));
		LOAD_SYMBOL(SYMBOL(Slisp, 263), ARG(6));	/* HOST */
		rt_struct_typep(ARG(5));
		if(CL_TRUEP(ARG(5)))
		{
			COPY(OFFSET(AR_BASE(GET_FORM(ARG(4))), 6 + 1), ARG(4));
		}
		else
		{
			COPY(SYMVAL(Slisp, 352), ARG(5));	/* NO_STRUCT */
			COPY(ARG(4), ARG(6));
			LOAD_SYMBOL(SYMBOL(Slisp, 263), ARG(7));	/* HOST */
			Ferror(ARG(5), 3);
		}
		LOAD_BOOL(CL_SYMBOLP(ARG(4)) && GET_SYMBOL(ARG(4)) == SYMBOL(Slisp, 279), ARG(4));	/* LOWER */
	}
	else
	{
		LOAD_NIL(ARG(4));
	}
	maybe_diddle_case(ARG(3));
	COPY(ARG(3), ARG(0));
}
void get_macro_character1(CL_FORM *base)
{
	COPY(ARG(1), ARG(2));
	LOAD_SYMBOL(SYMBOL(Slisp, 410), ARG(3));	/* READTABLE */
	rt_struct_typep(ARG(2));
	if(CL_TRUEP(ARG(2)))
	{
		COPY(OFFSET(AR_BASE(GET_FORM(ARG(1))), 0 + 1), ARG(2));
	}
	else
	{
		COPY(SYMVAL(Slisp, 342), ARG(2));	/* NO_STRUCT */
		COPY(ARG(1), ARG(3));
		LOAD_SYMBOL(SYMBOL(Slisp, 410), ARG(4));	/* READTABLE */
		Ferror(ARG(2), 3);
	}
	if(CL_CHARP(ARG(0)))
	{
		COPY(ARG(0), ARG(3));
	}
	else
	{
		COPY(SYMVAL(Slisp, 58), ARG(3));	/* WRONG_TYPE */
		COPY(ARG(0), ARG(4));
		LOAD_SYMBOL(SYMBOL(Slisp, 18), ARG(5));	/* CHARACTER */
		Ferror(ARG(3), 3);
	}
	rt_char_code(ARG(3));
	LOAD_BOOL(CL_SMVECP(ARG(2)), ARG(4));
	if(CL_TRUEP(ARG(4)))
	{
		goto THEN1;
	}
	else
	{
		COPY(ARG(2), ARG(5));
		LOAD_SYMBOL(SYMBOL(Slisp, 150), ARG(6));	/* COMPLEX-VECTOR */
		rt_struct_typep(ARG(5));
	}
	if(CL_TRUEP(ARG(5)))
	{
		THEN1:;
	}
	else
	{
		COPY(SYMVAL(Slisp, 58), ARG(4));	/* WRONG_TYPE */
		COPY(ARG(2), ARG(5));
		LOAD_SYMBOL(SYMBOL(Slisp, 47), ARG(6));	/* VECTOR */
		Ferror(ARG(4), 3);
	}
	Frow_major_aref(ARG(2));
	if(CL_TRUEP(ARG(2)))
	{
		if(CL_CONSP(ARG(2)))
		{
			COPY(GET_CAR(ARG(2)), ARG(3));
		}
		else
		{
			LOAD_SMSTR((CL_FORM *)&KClisp[239], ARG(3));	/* ~a is not a list */
			COPY(ARG(2), ARG(4));
			Ferror(ARG(3), 2);
		}
		if(CL_CONSP(ARG(2)))
		{
			COPY(GET_CDR(ARG(2)), ARG(4));
		}
		else
		{
			LOAD_SMSTR((CL_FORM *)&KClisp[241], ARG(4));	/* ~a is not a list */
			COPY(ARG(2), ARG(5));
			Ferror(ARG(4), 2);
		}
		COPY(ARG(3), ARG(0));
		COPY(ARG(4), &mv_buf[0]);
		mv_count = 2;
	}
	else
	{
		LOAD_NIL(ARG(0));
	}
}
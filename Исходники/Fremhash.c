void Fremhash(CL_FORM *base)
{
	COPY(ARG(0), ARG(2));
	LOAD_SMALLFIXNUM(0, ARG(3));
	internal_sxhash(ARG(2));
	mv_count = 1;
	COPY(ARG(1), ARG(3));
	LOAD_SYMBOL(SYMBOL(Slisp, 389), ARG(4));	/* HASH-TABLE */
	rt_struct_typep(ARG(3));
	if(CL_TRUEP(ARG(3)))
	{
		COPY(OFFSET(AR_BASE(GET_FORM(ARG(1))), 0 + 1), ARG(3));
	}
	else
	{
		COPY(SYMVAL(Slisp, 342), ARG(3));	/* NO_STRUCT */
		COPY(ARG(1), ARG(4));
		LOAD_SYMBOL(SYMBOL(Slisp, 389), ARG(5));	/* HASH-TABLE */
		Ferror(ARG(3), 3);
	}
	COPY(ARG(2), ARG(4));
	COPY(ARG(3), ARG(5));
	LOAD_SMALLFIXNUM(0, ARG(6));
	rt_convert_to_int(ARG(4));
	COPY(&mv_buf[0], ARG(5));
	mv_count = 1;
	{
		COPY(ARG(5), ARG(2));
	}
	COPY(ARG(1), ARG(3));
	hash_table_array(ARG(3));
	COPY(ARG(2), ARG(4));
	COPY(ARG(1), ARG(5));
	hash_table_array(ARG(5));
	LOAD_BOOL(CL_SMVECP(ARG(5)), ARG(6));
	if(CL_TRUEP(ARG(6)))
	{
		goto THEN1;
	}
	else
	{
		COPY(ARG(5), ARG(7));
		LOAD_SYMBOL(SYMBOL(Slisp, 150), ARG(8));	/* COMPLEX-VECTOR */
		rt_struct_typep(ARG(7));
	}
	if(CL_TRUEP(ARG(7)))
	{
		THEN1:;
	}
	else
	{
		COPY(SYMVAL(Slisp, 58), ARG(6));	/* WRONG_TYPE */
		COPY(ARG(5), ARG(7));
		LOAD_SYMBOL(SYMBOL(Slisp, 47), ARG(8));	/* VECTOR */
		Ferror(ARG(6), 3);
	}
	COPY(ARG(2), ARG(6));
	Frow_major_aref(ARG(5));
	COPY(ARG(1), ARG(6));
	LOAD_SYMBOL(SYMBOL(Slisp, 389), ARG(7));	/* HASH-TABLE */
	rt_struct_typep(ARG(6));
	if(CL_TRUEP(ARG(6)))
	{
		COPY(OFFSET(AR_BASE(GET_FORM(ARG(1))), 4 + 1), ARG(6));
	}
	else
	{
		COPY(SYMVAL(Slisp, 342), ARG(6));	/* NO_STRUCT */
		COPY(ARG(1), ARG(7));
		LOAD_SYMBOL(SYMBOL(Slisp, 389), ARG(8));	/* HASH-TABLE */
		Ferror(ARG(6), 3);
	}
	LOAD_SMALLFIXNUM(0, ARG(7));
	COPY(SYMVAL(Slisp, 0), ARG(8));	/* MOST-POSITIVE-FIXNUM */
	COPY(SYMVAL(Slisp, 0), ARG(9));	/* MOST-POSITIVE-FIXNUM */
	COPY(ARG(0), ARG(10));
	COPY(ARG(5), ARG(11));
	LOAD_NIL(ARG(12));
	COPY(ARG(6), ARG(13));
	LOAD_NIL(ARG(14));
	COPY(ARG(7), ARG(15));
	COPY(ARG(8), ARG(16));
	COPY(ARG(9), ARG(17));
	LOAD_GLOBFUN(&CFcar, ARG(18));
	delete1(ARG(10));
	COPY(ARG(10), ARG(5));
	COPY(ARG(5), ARG(0));
	COPY(ARG(3), ARG(1));
	COPY(ARG(4), ARG(2));
	rt_set_vref(ARG(0));
}
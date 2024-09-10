void char_reader(CL_FORM *base)
{
	COPY(ARG(0), ARG(3));
	LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(4));	/* T */
	LOAD_NIL(ARG(5));
	LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(6));	/* T */
	read_char1(ARG(3));
	LOAD_NIL(ARG(4));
	COPY(ARG(0), ARG(5));
	LOAD_NIL(ARG(6));
	LOAD_NIL(ARG(7));
	LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(8));	/* T */
	peek_char1(ARG(4));
	if(CL_TRUEP(ARG(4)))
	{
		if(CL_TRUEP(SYMVAL(Slisp, 447)))	/* *READTABLE-UNCHANGED* */
		{
			if(CL_CHARP(ARG(4)))	/* *READTABLE-SYNTAX* */
			{
				COPY(ARG(4), ARG(5));
			}
			else
			{
				COPY(SYMVAL(Slisp, 58), ARG(5));	/* WRONG_TYPE */
				COPY(ARG(4), ARG(6));
				LOAD_SYMBOL(SYMBOL(Slisp, 18), ARG(7));	/* CHARACTER */
				Ferror(ARG(5), 3);
			}
			rt_char_code(ARG(5));
			COPY(OFFSET(AR_BASE(GET_FORM(SYMVAL(Slisp, 450))), GET_FIXNUM(ARG(5))), ARG(5));
		}
		else
		{
			COPY(SYMVAL(Slisp, 449), ARG(5));	/* *READTABLE* */
			readtable_syntax(ARG(5));
			if(CL_CHARP(ARG(4)))
			{
				COPY(ARG(4), ARG(6));
			}
			else
			{
				COPY(SYMVAL(Slisp, 58), ARG(6));	/* WRONG_TYPE */
				COPY(ARG(4), ARG(7));
				LOAD_SYMBOL(SYMBOL(Slisp, 18), ARG(8));	/* CHARACTER */
				Ferror(ARG(6), 3);
			}
			rt_char_code(ARG(6));
			LOAD_BOOL(CL_SMVECP(ARG(5)), ARG(7));
			if(CL_TRUEP(ARG(7)))
			{
				goto THEN1;
			}
			else
			{
				COPY(ARG(5), ARG(8));
				LOAD_SYMBOL(SYMBOL(Slisp, 150), ARG(9));	/* COMPLEX-VECTOR */
				rt_struct_typep(ARG(8));
			}
			if(CL_TRUEP(ARG(8)))
			{
				THEN1:;
			}
			else
			{
				COPY(SYMVAL(Slisp, 58), ARG(7));	/* WRONG_TYPE */
				COPY(ARG(5), ARG(8));
				LOAD_SYMBOL(SYMBOL(Slisp, 47), ARG(9));	/* VECTOR */
				Ferror(ARG(7), 3);
			}
			Frow_major_aref(ARG(5));
		}
	}	/* CONSTITUENT */
	else
	{
		goto ELSE2;
	}
	if(CL_SYMBOLP(ARG(5)) && GET_SYMBOL(ARG(5)) == SYMBOL(Slisp, 460))
	{
		LOAD_SMALLFIXNUM(0, SYMVAL(Slisp, 440));	/* *FILL-POINTER* */
		LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(5));	/* T */
		BIND_SPECIAL(SYMBOL(Slisp, 408), ARG(5));	/* *READ-SUPPRESS* */
		COPY(ARG(0), ARG(6));
		COPY(ARG(3), ARG(7));
		bool_result = CL_TRUEP(SYMVAL(Slisp, 447));	/* *READTABLE-UNCHANGED* */
		if(bool_result)
		{
			if(CL_CHARP(ARG(3)))	/* *READTABLE-SYNTAX* */
			{
				COPY(ARG(3), ARG(8));
			}
			else
			{
				COPY(SYMVAL(Slisp, 58), ARG(8));	/* WRONG_TYPE */
				COPY(ARG(3), ARG(9));
				LOAD_SYMBOL(SYMBOL(Slisp, 18), ARG(10));	/* CHARACTER */
				Ferror(ARG(8), 3);
			}
			rt_char_code(ARG(8));
			COPY(OFFSET(AR_BASE(GET_FORM(SYMVAL(Slisp, 450))), GET_FIXNUM(ARG(8))), ARG(8));
		}
		else
		{
			COPY(SYMVAL(Slisp, 449), ARG(8));	/* *READTABLE* */
			readtable_syntax(ARG(8));
			if(CL_CHARP(ARG(3)))
			{
				COPY(ARG(3), ARG(9));
			}
			else
			{
				COPY(SYMVAL(Slisp, 58), ARG(9));	/* WRONG_TYPE */
				COPY(ARG(3), ARG(10));
				LOAD_SYMBOL(SYMBOL(Slisp, 18), ARG(11));	/* CHARACTER */
				Ferror(ARG(9), 3);
			}
			rt_char_code(ARG(9));
			LOAD_BOOL(CL_SMVECP(ARG(8)), ARG(10));
			if(CL_TRUEP(ARG(10)))
			{
				goto THEN3;
			}
			else
			{
				COPY(ARG(8), ARG(11));
				LOAD_SYMBOL(SYMBOL(Slisp, 150), ARG(12));	/* COMPLEX-VECTOR */
				rt_struct_typep(ARG(11));
			}
			if(CL_TRUEP(ARG(11)))
			{
				THEN3:;
			}
			else
			{
				COPY(SYMVAL(Slisp, 58), ARG(10));	/* WRONG_TYPE */
				COPY(ARG(8), ARG(11));
				LOAD_SYMBOL(SYMBOL(Slisp, 47), ARG(12));	/* VECTOR */
				Ferror(ARG(10), 3);
			}
			Frow_major_aref(ARG(8));
		}
		read_token(ARG(6));
		RESTORE_SPECIAL;
		if(CL_TRUEP(SYMVAL(Slisp, 408)))	/* *READ-SUPPRESS* */
		{
		}
		else
		{
			get_token_string(ARG(5));
			Fname_char(ARG(5));
			COPY(ARG(5), ARG(3));
			if(CL_TRUEP(ARG(3)))
			{
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&Kchar_reader[0], ARG(5));	/* illegal character name ~s */
				get_token_string(ARG(6));
				Ferror(ARG(5), 2);
			}
		}
	}
	ELSE2:;
	if(CL_TRUEP(SYMVAL(Slisp, 408)))	/* *READ-SUPPRESS* */
	{
		LOAD_NIL(ARG(0));
	}
	else
	{
		if(CL_TRUEP(ARG(2)))
		{
			COPY(ARG(2), ARG(5));
			Fplusp(ARG(5));
		}
		else
		{
			goto ELSE4;
		}
		if(CL_TRUEP(ARG(5)))
		{
			LOAD_SMSTR((CL_FORM *)&Kchar_reader[2], ARG(5));	/* font ~s of ~s will be ignored */
			COPY(ARG(2), ARG(6));
			COPY(ARG(3), ARG(7));
			Fwarn(ARG(5), 3);
			mv_count = 1;
		}
		ELSE4:;
		COPY(ARG(3), ARG(0));
	}
}
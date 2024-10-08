void quick_integer_to_string(CL_FORM *base)
{
	COPY(ARG(0), ARG(1));
	Fzerop(ARG(1));
	if(CL_TRUEP(ARG(1)))
	{
		LOAD_SMSTR((CL_FORM *)&Kquick_integer_to_string[0], ARG(0));	/* 0 */
	}
	else
	{
		if(CL_FIXNUMP(ARG(0)) && GET_FIXNUM(ARG(0)) == 1)
		{
			LOAD_SMSTR((CL_FORM *)&Kquick_integer_to_string[2], ARG(0));	/* 1 */
		}
		else
		{
			COPY(ARG(0), ARG(1));
			Fminusp(ARG(1));
			if(CL_TRUEP(ARG(1)))
			{
				LOAD_SYMBOL(SYMBOL(Slisp, 40), ARG(1));	/* SIMPLE-STRING */
				LOAD_SMSTR((CL_FORM *)&Kquick_integer_to_string[4], ARG(2));	/* - */
				COPY(ARG(0), ARG(3));
				Fminus(ARG(3), 1);
				quick_integer_to_string(ARG(3));
				if(CL_SMSTRP(ARG(3)))
				{
				}
				else
				{
					LOAD_SMSTR((CL_FORM *)&KClisp[244], ARG(4));	/* type error: ~S is not of type ~S */
					COPY(ARG(3), ARG(5));
					LOAD_SYMBOL(SYMBOL(Slisp, 40), ARG(6));	/* SIMPLE-STRING */
					Ferror(ARG(4), 3);
				}
				Fconcatenate(ARG(1), 3);
				COPY(ARG(1), ARG(0));
			}
			else
			{
				COPY(ARG(0), ARG(1));
				Finteger_length(ARG(1));
				LOAD_FIXNUM(ARG(2), 3, ARG(2));
				LOAD_FIXNUM(ARG(2), 3, ARG(2));
				rt_truncate(ARG(1));
				mv_count = 1;
				F1plus(ARG(1));
				COPY(ARG(1), ARG(2));
				LOAD_CHAR(ARG(3), ' ', ARG(3));
				make_string1(ARG(2));
				COPY(ARG(1), ARG(3));
				F1minus(ARG(3));
				COPY(ARG(0), ARG(4));
				LOAD_FIXNUM(ARG(5), 0, ARG(5));
				M1_1:;
				COPY(ARG(4), ARG(6));
				Fzerop(ARG(6));
				if(CL_TRUEP(ARG(6)))
				{
					F1plus(ARG(3));
					COPY(ARG(2), ARG(6));
					COPY(ARG(2), ARG(7));
					LOAD_FIXNUM(ARG(8), 0, ARG(8));
					LOAD_NIL(ARG(9));
					COPY(ARG(3), ARG(10));
					COPY(ARG(1), ARG(11));
					replace1(ARG(6));
					COPY(ARG(2), ARG(0));
					COPY(ARG(3), ARG(2));
					Fminus(ARG(1), 2);
					shrink_simple_string(ARG(0));
					goto RETURN1;
				}
				LOAD_FIXNUM(ARG(6), 10, ARG(6));
				COPY(ARG(4), ARG(6));
				LOAD_FIXNUM(ARG(7), 10, ARG(7));
				rt_truncate(ARG(6));
				COPY(&mv_buf[0], ARG(7));
				{
					int nargs;
					nargs = 2;
					mv_count = 1;
					{
						switch(nargs)
						{
							case 0:
							LOAD_NIL(ARG(6));
							case 1:
							LOAD_NIL(ARG(7));
							nargs = 2;
						}
						COPY(ARG(6), ARG(4));
						COPY(ARG(7), ARG(5));
					}
				}
				LOAD_SMSTR((CL_FORM *)&Kquick_integer_to_string[6], ARG(6));	/* 0123456789 */
				COPY(ARG(5), ARG(7));
				pvref(ARG(6));
				COPY(ARG(6), ARG(7));
				COPY(ARG(2), ARG(8));
				COPY(ARG(3), ARG(9));
				Fset_schar(ARG(7));
				F1minus(ARG(3));
				goto M1_1;
				RETURN1:;
			}
		}
	}
}
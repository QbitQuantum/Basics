static void Z122_check_for(CL_FORM *base)
{
	COPY(ARG(1), ARG(2));
	LOAD_SYMBOL(SYMBOL(Slisp, 248), ARG(3));	/* PATTERN */
	rt_struct_typep(ARG(2));
	if(CL_TRUEP(ARG(2)))
	{
		LOAD_NIL(ARG(2));
		COPY(ARG(1), ARG(3));
		pattern_pieces(ARG(3));
		M1_1:;
		if(CL_ATOMP(ARG(3)))
		{
			LOAD_NIL(ARG(2));
			COPY(ARG(2), ARG(0));
			goto RETURN1;
		}
		COPY(ARG(3), ARG(4));
		COPY(GET_CAR(ARG(4)), ARG(2));
		if(CL_SMSTRP(ARG(2)))
		{
			COPY(ARG(0), ARG(4));
			COPY(ARG(2), ARG(5));
			Z122_check_for(ARG(4));
			bool_result = CL_TRUEP(ARG(4));
		}
		else
		{
			if(CL_CONSP(ARG(2)))
			{
				if(CL_CONSP(ARG(1)))
				{
					COPY(GET_CAR(ARG(1)), ARG(4));
				}
				else
				{
					if(CL_TRUEP(ARG(1)))
					{
						LOAD_SMSTR((CL_FORM *)&KClisp[239], ARG(4));	/* ~a is not a list */
						COPY(ARG(1), ARG(5));
						Ferror(ARG(4), 2);
					}
					else
					{
						COPY(ARG(1), ARG(4));
					}
				}
				if(CL_SYMBOLP(ARG(4)) && GET_SYMBOL(ARG(4)) == SYMBOL(Slisp, 255))	/* CHARACTER-SET */
				{
					COPY(ARG(0), ARG(5));
					if(CL_CONSP(ARG(1)))
					{
						COPY(GET_CDR(ARG(1)), ARG(6));
					}
					else
					{
						if(CL_TRUEP(ARG(1)))
						{
							LOAD_SMSTR((CL_FORM *)&KClisp[241], ARG(6));	/* ~a is not a list */
							COPY(ARG(1), ARG(7));
							Ferror(ARG(6), 2);
						}
						else
						{
							COPY(ARG(1), ARG(6));
						}
					}
					Z122_check_for(ARG(5));
				}
				else
				{
					goto ELSE1;
				}
			}
			else
			{
				goto ELSE1;
			}
			bool_result = CL_TRUEP(ARG(5));
		}
		if(bool_result)
		{
			LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(0));	/* T */
			goto RETURN1;
		}
		ELSE1:;
		COPY(ARG(3), ARG(4));
		COPY(GET_CDR(ARG(4)), ARG(3));
		goto M1_1;
		RETURN1:;
	}
	else
	{
		if(CL_LISTP(ARG(1)))
		{
			LOAD_NIL(ARG(2));
			COPY(ARG(1), ARG(3));
			M2_1:;
			if(CL_ATOMP(ARG(3)))
			{
				LOAD_NIL(ARG(2));
				COPY(ARG(2), ARG(0));
				goto RETURN2;
			}
			COPY(ARG(3), ARG(4));
			COPY(GET_CAR(ARG(4)), ARG(2));
			COPY(ARG(0), ARG(4));
			COPY(ARG(2), ARG(5));
			Z122_check_for(ARG(4));
			if(CL_TRUEP(ARG(4)))
			{
				LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(0));	/* T */
				goto RETURN2;
			}
			COPY(ARG(3), ARG(4));
			COPY(GET_CDR(ARG(4)), ARG(3));
			goto M2_1;
			RETURN2:;
		}
		else
		{
			if(CL_SMSTRP(ARG(1)))
			{
				COPY(ARG(1), ARG(2));
				Flength(ARG(2));
				LOAD_SMALLFIXNUM(0, ARG(3));
				M3_1:;
				COPY(ARG(3), ARG(4));
				COPY(ARG(2), ARG(5));
				Fge(ARG(4), 2);
				if(CL_TRUEP(ARG(4)))
				{
					LOAD_NIL(ARG(0));
					goto RETURN3;
				}
				COPY(ARG(0), ARG(4));
				COPY(ARG(1), ARG(5));
				COPY(ARG(3), ARG(6));
				Fschar(ARG(5));
				Ffuncall(ARG(4), 2);
				mv_count = 1;
				if(CL_TRUEP(ARG(4)))
				{
					LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(0));	/* T */
					goto RETURN3;
				}
				F1plus(ARG(3));
				goto M3_1;
				RETURN3:;
			}
			else
			{
				if(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 256))	/* UNSPECIFIC */
				{
					LOAD_NIL(ARG(0));
				}
				else
				{
					LOAD_SMSTR((CL_FORM *)&Kmaybe_diddle_case[0], ARG(0));	/* etypecase: the value ~a is not a legal value */
					Ferror(ARG(0), 2);
				}
			}
		}
	}
}
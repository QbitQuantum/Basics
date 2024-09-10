static void Z8_union_internal(CL_FORM *base, CL_FORM *display[])
{
	M1_1:;
	if(CL_TRUEP(ARG(0)))
	{
		if(CL_TRUEP(&display[0][4]))
		{
			COPY(&display[0][4], ARG(1));
			if(CL_CONSP(ARG(0)))
			{
				COPY(GET_CAR(ARG(0)), ARG(2));
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&KClisp[264], ARG(2));	/* ~a is not a list */
				COPY(ARG(0), ARG(3));
				Ferror(ARG(2), 2);
			}
			Ffuncall(ARG(1), 2);
			mv_count = 1;
		}
		else
		{
			if(CL_CONSP(ARG(0)))
			{
				COPY(GET_CAR(ARG(0)), ARG(1));
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&KClisp[264], ARG(1));	/* ~a is not a list */
				COPY(ARG(0), ARG(2));
				Ferror(ARG(1), 2);
			}
		}
		COPY(&display[0][1], ARG(2));
		COPY(&display[0][2], ARG(3));
		COPY(&display[0][4], ARG(4));
		COPY(ARG(1), ARG(5));
		COPY(ARG(2), ARG(6));
		COPY(ARG(3), ARG(7));
		LOAD_NIL(ARG(8));
		COPY(ARG(4), ARG(9));
		member1(ARG(5));
		if(CL_TRUEP(ARG(5)))
		{
			COPY(ARG(0), ARG(1));
			if(CL_CONSP(ARG(1)))
			{
				COPY(GET_CDR(ARG(1)), ARG(0));
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&KClisp[262], ARG(0));	/* ~a is not a list */
				Ferror(ARG(0), 2);
			}
			goto M1_1;
		}
		else
		{
			if(CL_CONSP(ARG(0)))
			{
				COPY(GET_CAR(ARG(0)), ARG(1));
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&KClisp[264], ARG(1));	/* ~a is not a list */
				COPY(ARG(0), ARG(2));
				Ferror(ARG(1), 2);
			}
			if(CL_CONSP(ARG(0)))
			{
				COPY(GET_CDR(ARG(0)), ARG(2));
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&KClisp[262], ARG(2));	/* ~a is not a list */
				COPY(ARG(0), ARG(3));
				Ferror(ARG(2), 2);
			}
			Z8_union_internal(ARG(2), display);
			ALLOC_CONS(ARG(3), ARG(1), ARG(2), ARG(0));
		}
	}
	else
	{
		COPY(&display[0][1], ARG(0));
	}
	goto RETURN1;
	RETURN1:;
}
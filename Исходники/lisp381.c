void Penumerate_directories(CL_FORM *base)
{
	M1_1:;
	if(CL_TRUEP(ARG(1)))
	{
		if(CL_CONSP(ARG(1)))
		{
			COPY(GET_CAR(ARG(1)), ARG(5));
		}
		else
		{
			LOAD_SMSTR((CL_FORM *)&KClisp[239], ARG(5));	/* ~a is not a list */
			COPY(ARG(1), ARG(6));
			Ferror(ARG(5), 2);
		}
		if(CL_SMSTRP(ARG(5)))
		{
			LOAD_SYMBOL(SYMBOL(Slisp, 44), ARG(6));	/* STRING */
			COPY(ARG(0), ARG(7));
			COPY(ARG(5), ARG(8));
			LOAD_SMSTR((CL_FORM *)&KPenumerate_directories[0], ARG(9));	/* / */
			Fconcatenate(ARG(6), 4);
			if(CL_CONSP(ARG(1)))
			{
				COPY(GET_CDR(ARG(1)), ARG(7));
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&KClisp[241], ARG(7));	/* ~a is not a list */
				COPY(ARG(1), ARG(8));
				Ferror(ARG(7), 2);
			}
			COPY(ARG(6), ARG(0));
			COPY(ARG(7), ARG(1));
			LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(3));	/* T */
			goto M1_1;
		}
		else
		{
			if(CL_SYMBOLP(ARG(5)) && GET_SYMBOL(ARG(5)) == SYMBOL(Slisp, 265))	/* UP */
			{
				LOAD_SYMBOL(SYMBOL(Slisp, 44), ARG(6));	/* STRING */
				COPY(ARG(0), ARG(7));
				LOAD_SMSTR((CL_FORM *)&KPenumerate_directories[2], ARG(8));	/* ../ */
				Fconcatenate(ARG(6), 3);
				if(CL_CONSP(ARG(1)))
				{
					COPY(GET_CDR(ARG(1)), ARG(7));
				}
				else
				{
					LOAD_SMSTR((CL_FORM *)&KClisp[241], ARG(7));	/* ~a is not a list */
					COPY(ARG(1), ARG(8));
					Ferror(ARG(7), 2);
				}
				COPY(ARG(6), ARG(0));
				COPY(ARG(7), ARG(1));
				LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(3));	/* T */
				goto M1_1;
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&KPenumerate_directories[4], ARG(0));	/* etypecase: the value ~a is not a legal value */
				COPY(ARG(5), ARG(1));
				Ferror(ARG(0), 2);
			}
		}
	}
	else
	{
		COPY(ARG(2), ARG(1));
		LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(2));	/* T */
		COPY(ARG(4), ARG(3));
		Penumerate_files(ARG(0));
	}
	goto RETURN1;
	RETURN1:;
}
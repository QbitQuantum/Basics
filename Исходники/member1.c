void member1(CL_FORM *base)
{
	GEN_HEAPVAR(ARG(3), ARG(5));
	if(CL_TRUEP(ARG(2)))
	{
	}
	else
	{
		if(CL_TRUEP(INDIRECT(ARG(3))))
		{
			GEN_CLOSURE(array, ARG(5), 4, Z11_lambda, -1);
			COPY(ARG(3), &array[3]);
			LOAD_CLOSURE(array, ARG(5));
			COPY(ARG(5), ARG(2));
		}
		else
		{
			GEN_STATIC_GLOBAL_FUNARG(extern_closure, Feql, 2);
			LOAD_GLOBFUN(&extern_closure, ARG(2));
		}
	}
	COPY(ARG(1), ARG(5));
	M1_1:;
	if(CL_TRUEP(ARG(5)))
	{
		COPY(ARG(2), ARG(6));
		COPY(ARG(0), ARG(7));
		if(CL_TRUEP(ARG(4)))
		{
			COPY(ARG(4), ARG(8));
			if(CL_CONSP(ARG(5)))
			{
				COPY(GET_CAR(ARG(5)), ARG(9));
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&KClisp[264], ARG(9));	/* ~a is not a list */
				COPY(ARG(5), ARG(10));
				Ferror(ARG(9), 2);
			}
			Ffuncall(ARG(8), 2);
			mv_count = 1;
		}
		else
		{
			if(CL_CONSP(ARG(5)))
			{
				COPY(GET_CAR(ARG(5)), ARG(8));
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&KClisp[264], ARG(8));	/* ~a is not a list */
				COPY(ARG(5), ARG(9));
				Ferror(ARG(8), 2);
			}
		}
		Ffuncall(ARG(6), 3);
		mv_count = 1;
		if(CL_TRUEP(ARG(6)))
		{
			COPY(ARG(5), ARG(0));
		}
		else
		{
			COPY(ARG(5), ARG(6));
			COPY(ARG(6), ARG(7));
			if(CL_CONSP(ARG(7)))
			{
				COPY(GET_CDR(ARG(7)), ARG(5));
			}
			else
			{
				if(CL_TRUEP(ARG(7)))
				{
					LOAD_SMSTR((CL_FORM *)&KClisp[262], ARG(5));	/* ~a is not a list */
					COPY(ARG(7), ARG(6));
					Ferror(ARG(5), 2);
				}
				else
				{
					COPY(ARG(7), ARG(5));
				}
			}
			goto M1_1;
		}
	}
	else
	{
		LOAD_NIL(ARG(0));
	}
	goto RETURN1;
	RETURN1:;
}
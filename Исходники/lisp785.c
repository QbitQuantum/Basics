void Fget_properties(CL_FORM *base)
{
	M1_1:;
	if(CL_ATOMP(ARG(0)))
	{
		LOAD_NIL(ARG(0));
		LOAD_NIL(ARG(1));
		LOAD_NIL(ARG(2));
		COPY(ARG(1), &mv_buf[0]);
		COPY(ARG(2), &mv_buf[1]);
		mv_count = 3;
	}
	else
	{
		COPY(GET_CAR(ARG(0)), ARG(2));
		COPY(ARG(2), ARG(3));
		COPY(ARG(1), ARG(4));
		LOAD_NIL(ARG(5));
		LOAD_NIL(ARG(6));
		LOAD_NIL(ARG(7));
		member1(ARG(3));
		if(CL_TRUEP(ARG(3)))
		{
			COPY(GET_CAR(ARG(0)), ARG(2));
			COPY(GET_CDR(ARG(0)), ARG(3));
			if(CL_CONSP(ARG(3)))
			{
				COPY(GET_CAR(ARG(3)), ARG(3));
			}
			else
			{
				if(CL_TRUEP(ARG(3)))
				{
					LOAD_SMSTR((CL_FORM *)&KClisp[264], ARG(4));	/* ~a is not a list */
					COPY(ARG(3), ARG(5));
					Ferror(ARG(4), 2);
				}
				else
				{
				}
			}
			COPY(ARG(0), ARG(4));
			COPY(ARG(2), ARG(0));
			COPY(ARG(3), &mv_buf[0]);
			COPY(ARG(4), &mv_buf[1]);
			mv_count = 3;
		}
		else
		{
			COPY(ARG(0), ARG(2));
			COPY(ARG(2), ARG(3));
			COPY(GET_CDR(ARG(3)), ARG(3));
			if(CL_CONSP(ARG(3)))
			{
				COPY(GET_CDR(ARG(3)), ARG(0));
			}
			else
			{
				if(CL_TRUEP(ARG(3)))
				{
					LOAD_SMSTR((CL_FORM *)&KClisp[262], ARG(4));	/* ~a is not a list */
					COPY(ARG(3), ARG(5));
					Ferror(ARG(4), 2);
				}
				else
				{
					COPY(ARG(3), ARG(0));
				}
			}
			goto M1_1;
		}
	}
	goto RETURN1;
	RETURN1:;
}
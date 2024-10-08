void Ftypep(CL_FORM *base)
{
	if(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 48))	/* T */
	{
		LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(0));	/* T */
	}
	else
	{
		if(CL_TRUEP(ARG(1)))
		{
			if(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 23))	/* FIXNUM */
			{
				if(CL_FIXNUMP(ARG(0)))
				{
					COPY(SYMVAL(Slisp, 1), ARG(2));	/* MOST-NEGATIVE-FIXNUM */
					COPY(ARG(0), ARG(3));
					COPY(SYMVAL(Slisp, 0), ARG(4));	/* MOST-POSITIVE-FIXNUM */
					Fle(ARG(2), 3);
					COPY(ARG(2), ARG(0));
				}
				else
				{
					LOAD_NIL(ARG(0));
				}
			}
			else
			{
				LOAD_BOOL(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 24), ARG(2));	/* FLOAT */
				if(CL_TRUEP(ARG(2)))
				{
					goto THEN1;
				}
				else
				{
					LOAD_BOOL(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 37), ARG(3));	/* SHORT-FLOAT */
					if(CL_TRUEP(ARG(3)))
					{
						goto THEN1;
					}
					else
					{
						LOAD_BOOL(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 42), ARG(4));	/* SINGLE-FLOAT */
						if(CL_TRUEP(ARG(4)))
						{
							goto THEN1;
						}
						else
						{
							LOAD_BOOL(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 22), ARG(5));	/* DOUBLE-FLOAT */
							if(CL_TRUEP(ARG(5)))
							{
								goto THEN1;
							}
							else
							{
							}	/* LONG-FLOAT */
						}
					}
				}
				if(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 29))
				{
					THEN1:;
					LOAD_BOOL(CL_FLOATP(ARG(0)), ARG(0));
				}
				else
				{
					LOAD_BOOL(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 18), ARG(2));	/* CHARACTER */
					if(CL_TRUEP(ARG(2)))
					{
						goto THEN2;
					}
					else
					{
					}	/* STANDARD-CHAR */
					if(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 43))
					{
						THEN2:;
						LOAD_BOOL(CL_CHARP(ARG(0)), ARG(0));
					}
					else
					{
						if(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 28))	/* LIST */
						{
							LOAD_BOOL(CL_LISTP(ARG(0)), ARG(0));
						}
						else
						{
							if(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 31))	/* NULL */
							{
								if(CL_TRUEP(ARG(0)))
								{
									LOAD_NIL(ARG(0));
								}
								else
								{
									LOAD_SYMBOL(SYMBOL(Slisp, 48), ARG(0));	/* T */
								}
							}
							else
							{
								if(CL_SYMBOLP(ARG(1)) && GET_SYMBOL(ARG(1)) == SYMBOL(Slisp, 21))	/* CONS */
								{
									LOAD_BOOL(CL_CONSP(ARG(0)), ARG(0));
								}
								else
								{
									LOAD_SMSTR((CL_FORM *)&KClisp[86], ARG(2));	/* (TYPEP ~S ~S) is not implemented */
									COPY(ARG(0), ARG(3));
									COPY(ARG(1), ARG(4));
									Ferror(ARG(2), 3);
								}
							}
						}
					}
				}
			}
		}
		else
		{
			LOAD_NIL(ARG(0));
		}
	}
}
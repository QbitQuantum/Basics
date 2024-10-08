void copy_symbol1(CL_FORM *base)
{
	if(CL_SYMBOLP(ARG(0)))
	{
		LOAD_SMSTR(SYM_NAME(ARG(0)), ARG(2));
	}
	else
	{
		if(CL_TRUEP(ARG(0)))
		{
			COPY(SYMVAL(Slisp, 676), ARG(2));	/* SYM_EXPECTED */
			COPY(ARG(0), ARG(3));
			Ferror(ARG(2), 2);
		}
		else
		{
			LOAD_SMSTR((CL_FORM *)&KClisp[266], ARG(2));	/* NIL */
		}
	}
	Fmake_symbol(ARG(2));
	if(CL_TRUEP(ARG(1)))
	{
		COPY(ARG(0), ARG(3));
		Fboundp(ARG(3));
		if(CL_TRUEP(ARG(3)))
		{
			COPY(ARG(2), ARG(3));
			if(CL_SYMBOLP(ARG(0)))
			{
				COPY(SYM_VALUE(ARG(0)), ARG(4));
			}
			else
			{
				if(CL_TRUEP(ARG(0)))
				{
					COPY(SYMVAL(Slisp, 676), ARG(4));	/* SYM_EXPECTED */
					COPY(ARG(0), ARG(5));
					Ferror(ARG(4), 2);
				}
				else
				{
					LOAD_NIL(ARG(4));
				}
			}
			Fset(ARG(3));
		}
		if(CL_SYMBOLP(ARG(0)))
		{
			COPY(SYM_PLIST(ARG(0)), ARG(3));
		}
		else
		{
			if(CL_TRUEP(ARG(0)))
			{
				COPY(SYMVAL(Slisp, 676), ARG(3));	/* SYM_EXPECTED */
				COPY(ARG(0), ARG(4));
				Ferror(ARG(3), 2);
			}
			else
			{
				COPY(SYMVAL(Slisp, 678), ARG(3));	/* *NIL-PLIST* */
			}
		}
		Fcopy_list(ARG(3));
		COPY(ARG(3), ARG(4));
		COPY(ARG(2), ARG(5));
		Fset_symbol_plist(ARG(4));
	}
	COPY(ARG(2), ARG(0));
}
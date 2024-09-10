void Fpathname_host(CL_FORM *base, int nargs)
{
	BOOL supl_flags[1];
	static CL_FORM * keylist[] =
	{
		SYMBOL(Slisp, 208),	/* CASE */
	};
	keysort(STACK(base, 1), nargs - 1, 1, keylist, supl_flags, FALSE);
	if(NOT(supl_flags[0]))
	{
		LOAD_SYMBOL(SYMBOL(Slisp, 207), STACK(base, 1));	/* LOCAL */
	}
	COPY(STACK(base, 0), STACK(base, 2));
	COPY(STACK(base, 0), STACK(base, 3));
	LOAD_SYMBOL(SYMBOL(Slisp, 164), STACK(base, 4));	/* PATHNAME */
	struct_typep(STACK(base, 3));
	if(CL_TRUEP(STACK(base, 3)))
	{
		COPY(STACK(base, 0), STACK(base, 2));
	}
	else
	{
		if(CL_ARRAY_P(STACK(base, 0)))
		{
			COPY(STACK(base, 0), STACK(base, 3));
			LOAD_SYMBOL(SYMBOL(Slisp, 43), STACK(base, 4));	/* STANDARD-CHAR */
			LOAD_SYMBOL(SYMBOL(Slisp, 48), STACK(base, 5));	/* * */
			check_array_internal(STACK(base, 3));
			bool_result = CL_TRUEP(STACK(base, 3));
		}
		else
		{
			bool_result = FALSE;
		}
		if(bool_result)
		{
			COPY(STACK(base, 0), STACK(base, 2));
			Fparse_namestring(STACK(base, 2), 1);
			mv_count = 1;
		}
		else
		{
			COPY(STACK(base, 0), STACK(base, 3));
			LOAD_SYMBOL(SYMBOL(Slisp, 63), STACK(base, 4));	/* STREAM */
			struct_typep(STACK(base, 3));
			if(CL_TRUEP(STACK(base, 3)))
			{
				COPY(STACK(base, 0), STACK(base, 2));
				file_name(STACK(base, 2), 1);
				Fparse_namestring(STACK(base, 2), 1);
				mv_count = 1;
			}
			else
			{
				LOAD_SMSTR((CL_FORM *)&KFpathname_host[0], STACK(base, 2));	/* etypecase: the value ~a is not a legal value */
				COPY(STACK(base, 0), STACK(base, 3));
				Ferror(STACK(base, 2), 2);
			}
		}
	}
	COPY(STACK(base, 2), STACK(base, 0));
	LOAD_FIXNUM(0, STACK(base, 1));
	LOAD_SYMBOL(SYMBOL(Slisp, 164), STACK(base, 2));	/* PATHNAME */
	struct_ref(STACK(base, 0));
}
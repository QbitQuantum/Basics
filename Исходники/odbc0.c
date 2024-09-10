static int odbc_dispatch3(void)
{
	unsigned long retval;
	PWord rval; int rtype;
	PWord arg1; int type1;
	PWord arg2; int type2;
	PWord arg3; int type3;
	PWord arg4; int type4;
	PWord arg5; int type5;
	PWord arg6; int type6;

	PI_getan(&arg1,&type1,1);
	if (type1 != PI_INT)
		if (!CI_get_integer((unsigned long *)&arg1,type1))
			PI_FAIL;
	PI_getan(&arg2,&type2,2);
	if (type2 != PI_INT)
		if (!CI_get_integer((unsigned long *)&arg2,type2))
			PI_FAIL;
	PI_getan(&arg3,&type3,3);
	if (type3 != PI_INT)
		if (!CI_get_integer((unsigned long *)&arg3,type3))
			PI_FAIL;
	PI_getan(&arg4,&type4,4);
	if (type4 != PI_INT)
		if (!CI_get_integer((unsigned long *)&arg4,type4))
			PI_FAIL;
	PI_getan(&arg5,&type5,5);
	if (type5 != PI_INT)
		if (!CI_get_integer((unsigned long *)&arg5,type5))
			PI_FAIL;
	PI_getan(&arg6,&type6,6);


	switch(arg1)
	{
		case 0:
			retval = (unsigned long) SQLSetScrollOptions(((SQLHSTMT  ) arg2),((SQLUSMALLINT  ) arg3),((SQLINTEGER  ) arg4),((SQLUSMALLINT  ) arg5));
			break;
		case 1:
			retval = (unsigned long) SQLSetPos(((SQLHSTMT  ) arg2),((SQLUSMALLINT  ) arg3),((SQLUSMALLINT  ) arg4),((SQLUSMALLINT  ) arg5));
			break;
		case 2:
			retval = (unsigned long) SQLSetStmtAttr(((SQLHSTMT  ) arg2),((SQLINTEGER  ) arg3),((SQLPOINTER  ) arg4),((SQLINTEGER  ) arg5));
			break;
		case 3:
			retval = (unsigned long) SQLSetEnvAttr(((SQLHENV  ) arg2),((SQLINTEGER  ) arg3),((SQLPOINTER  ) arg4),((SQLINTEGER  ) arg5));
			break;
		case 4:
			retval = (unsigned long) SQLSetConnectAttr(((SQLHDBC  ) arg2),((SQLINTEGER  ) arg3),((SQLPOINTER  ) arg4),((SQLINTEGER  ) arg5));
			break;
		default:
			PI_FAIL;
	}
	PI_makedouble(&rval,&rtype,(double) retval);
	if (PI_unify(arg6,type6,rval,rtype))
		PI_SUCCEED;
	PI_FAIL;
}
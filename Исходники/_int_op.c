Datum
sort_desc(PG_FUNCTION_ARGS)
{
	ArrayType  *a = (ArrayType *) DatumGetPointer(PG_DETOAST_DATUM_COPY(PG_GETARG_DATUM(0)));

	CHECKARRVALID(a);
	if (ARRISVOID(a))
		PG_RETURN_POINTER(a);
	QSORT(a, 0);
	PG_RETURN_POINTER(a);
}
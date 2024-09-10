RETCODE SQL_API SQLSetParam (
									 HSTMT     hstmt,
									 UWORD     ipar,
									 SWORD     fCType,
									 SWORD     fSqlType,
									 UDWORD       cbColDef,
									 SWORD     ibScale,
									 PTR       rgbValue,
									 SDWORD FAR *pcbValue)
{
	return SQLBindParameter(hstmt,
									ipar,
									(SWORD)SQL_PARAM_INPUT_OUTPUT,
									fCType,
									fSqlType,
									cbColDef,
									ibScale,
									rgbValue,
									SQL_SETPARAM_VALUE_MAX,
									pcbValue );
}
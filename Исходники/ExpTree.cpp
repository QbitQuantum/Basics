void ExpAnd::Evaluate(ExpReturn* er)
{
	ExpReturn param;

	l->Evaluate(er);
	r->Evaluate(&param);

	// Also does string concats
	switch (er->eType) {

	case EXPTYPE_INTEGER:

		switch (param.eType) {
		case EXPTYPE_INTEGER:
			er->eData.iVal = (er->eData.iVal && param.eData.iVal);
			return;
		case EXPTYPE_STRING: {
			er->eType = EXPTYPE_STRING;
			char strbuf[32];
			_i64toa(er->eData.iVal, strbuf, 10);
			temp = strbuf;
			temp += *(param.eData.str);
			er->eData.str = &temp;
			return;
			}
		}//switch

	case EXPTYPE_FLOAT:
		switch(param.eType) {
		case EXPTYPE_STRING:
			{
				er->eType = EXPTYPE_STRING;
				char strbuf[32];
				_gcvt(er->eData.fVal, DBL_DIG, strbuf);
				temp = strbuf;
				if (temp.Right(1) == ".")
					temp = temp.Left(temp.GetLength() - 1);
				temp += *(param.eData.str);
				er->eData.str = &temp;
				return;
			}
		}
	case EXPTYPE_STRING:
		switch(param.eType) {
		case EXPTYPE_INTEGER:
			{
				char strbuf[32];
				_i64toa(param.eData.iVal, strbuf, 10);
				*(er->eData.str) += strbuf;
				return;
			}
		case EXPTYPE_FLOAT:
			{
				char strbuf[32];
				_gcvt(param.eData.fVal, DBL_DIG, strbuf);
				temp = strbuf;
				if (temp.Right(1) == ".")
					temp = temp.Left(temp.GetLength() - 1);
				*(er->eData.str) += temp;
				return;
			}
		case EXPTYPE_STRING:
			{
				*(er->eData.str) += *(param.eData.str);
				return;
			}
		}
	}//switch

	// Types invalid: return without modifying er (!)
	TYPEMISMATCH2(er, &param, "perform 'and'");
}
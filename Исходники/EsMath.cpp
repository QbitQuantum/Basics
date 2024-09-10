/*---------------------------------------------------------------------*//**
	最小値 ⇒ math_min
**//*---------------------------------------------------------------------*/
bool EsMath::EsMathClass::callMin(EsContext* ctx, EsObject* objThis, EsValue* valCallee, EsValue* valThis, EsValue* vaArg, u32 numArg, EsValue* valRet, const EsCallExtParam* exprm)
{
	if(numArg <= 0)
	{
		valRet->setValue(TypeUtils::getF64PositiveInfinity());	// ⇒ *vp = DOUBLE_TO_JSVAL(cx->runtime->jsPositiveInfinity);
		return true;
	}

	f64 a, r;
	r = TypeUtils::getF64PositiveInfinity();
	for(u32 i = 0; i < numArg; i++)
	{
		vaArg[i].toNumber(&a, &vaArg[i], ctx);
		if(vaArg[i].isNull())
		{
			return false;
		}
		if(TFW_F64_IS_NAN(a))
		{
			valRet->setValue(TypeUtils::getF64NaN());	// ⇒ *vp = DOUBLE_TO_JSVAL(cx->runtime->jsNaN);
			return true;
		}

		if((a == 0.0) && (a == r))
		{
			if(COPYSIGN(1.0, r) == -1)
			{
				r = a;
			}
		}
		else if(a < r)
		{
			r = a;
		}
	}

	valRet->setNumber(r);
	return true;
}
BOOL CCalculator::Expression(CCalcExpression** ppcExpression)
{
	BOOL				bOperator;
	BOOL				bOperand;
	BOOL				bFirst;
	CArrayIntAndPointer		cArray;
	CCalcOperator*		pcOperator;
	CCalcExpression*	pcOperand;

	cArray.Init(16);
	bFirst = TRUE;
	for (;;)
	{
		for (;;)
		{
			bOperator = Operator(&pcOperator);
			if (!bOperator)
			{
				break;
			}
			cArray.Add(pcOperator, 0);
		}

		bOperand = Operand(&pcOperand);
		if (!bOperand && !bOperator)
		{
			if (bFirst)
			{
				cArray.Kill();
				return FALSE;
			}
			else
			{
				BuildExpression(ppcExpression, &cArray);

				cArray.Kill();

				if (*ppcExpression == NULL)
				{
					return FALSE;
				}
				else
				{
					return TRUE;
				}
			}
		}
		cArray.Add(pcOperand, 0);
		bFirst = FALSE;
	}
}
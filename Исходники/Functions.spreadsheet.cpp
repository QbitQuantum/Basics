void ERRORFunction(Value *stack, int argCnt, CContainer *cells)
{
	double d;

	if (GetDoubleArgument(stack, argCnt, 1, &d))
	{
		if (isnan(d))
			stack[0] = d;
		else
		{
//			char n[32];
//			sprintf(n, "%d", (int)rint(d));
			stack[0] = Nan( static_cast<int>(rint(d)) );
		}
	}
	else
		stack[0] = gRefNan;
}
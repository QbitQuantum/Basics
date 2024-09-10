void CallFunction(FunctionCall fc)
{
	int function = GetFunction(fc->function);
	
	switch (function)
	{
		case VAR : NewVariable(fc); break;
		case NMX : NewMatrix(fc); break;
		case ADD : Addition(fc); break;
		case SUB : Substraction(fc); break;
		case MUL : Multiplication(fc); break;
		case MSC : Scalar_Mult(fc); break;
		case EXP : Exponentiation(fc); break;
		case TRA : Transpose(fc); break;
		case DET : Determinant(fc); break;
		case DLU : Decomposition(fc); break;
		case SOL : Solve(fc); break;
		case INV : Inversion(fc); break;
		case RNK : Rank(fc); break;
		case DSP : Display(fc); break;
		case NOF : // default
		default :
		{
			if (GetFunction(fc->name)==SPT) SpeedTest(fc);
			else if (IndexVariable(fc->function)!=-1) NewVariable(fc);
			else if (IndexMatrix(fc->function)!=-1) NewMatrix(fc);
			else
			{
				printf("\t%s : Function Not Implemented\n", fc->function);
				fni++;
			}
			break;
		}
	}
	
	if (function!=NOF && function !=VAR) fni = 0;
}
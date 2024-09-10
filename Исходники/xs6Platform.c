	int fpclassify(double x)
	{
		int result = FP_NORMAL;
		switch (_fpclass(x)) {
		case _FPCLASS_SNAN:  
		case _FPCLASS_QNAN:  
			result = FP_NAN;
			break;
		case _FPCLASS_NINF:  
		case _FPCLASS_PINF:  
			result = FP_INFINITE;
			break;
		case _FPCLASS_NZ: 
		case _FPCLASS_PZ:  
			result = FP_ZERO;
			break;
		case _FPCLASS_ND:  
		case _FPCLASS_PD: 
			result = FP_SUBNORMAL;
			break;
		}
		return result;
	}
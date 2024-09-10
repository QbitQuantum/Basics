static void 
getRegReg(reg_id_t r1, reg_id_t r2, int opcode, app_pc addr){
	
	const char * r1Name = get_register_name(r1);
	const char * r2Name = get_register_name(r2);
	int s1        = atoi(r1Name + 3 * sizeof(char));
	int s2        = atoi(r2Name + 3 * sizeof(char));
	dr_mcontext_t mcontext;
   	memset(&mcontext, 0, sizeof(dr_mcontext_t));
   	mcontext.flags = DR_MC_MULTIMEDIA;
   	mcontext.size = sizeof(dr_mcontext_t);
   	bool result = dr_get_mcontext(dr_get_current_drcontext(), &mcontext);
	int r, s;
	int bits = 0;
	double loss = 0;
	double lossD = 0;
	if(is_single_precision_instr(opcode)){
		float op1, op2;
//		for(r=0; r<16; ++r)
//			for(s=0; s<4; ++s)
//		     		printf("reg %i.%i: %f\n", r, s, 
//					*((float*) &mcontext.ymm[r].u32[s]));
		op1 = *((float*) &mcontext.ymm[s1].u32[0]);
		op2 = *((float*) &mcontext.ymm[s2].u32[0]);
       //		dr_fprintf(logF, "%d: %f  %f\n",opcode, op1, op2);
		int exp1, exp2;
		float mant1, mant2;
		mant1 = frexpf(op1, &exp1);
		mant2 = frexpf(op2, &exp2);
		bits = abs(exp1-exp2);

		double dop1 = op1;
		double dop2 = op2;

		if(opcode == OP_addss){
			double dadd = dop1 + dop2;
			float fadd = op1 + op2;
			lossD = dadd - fadd;
//		printf("double %.13lf float %.13f\n", dadd, fadd);
		}
		else{
			double dsub = dop1 - dop2;
			float fsub = op1 - op2;	
			lossD = dsub - fsub;
		}

//		printf("diff of double and float is %.13lf\n", lossD);
	}
	else{
		double op1, op2;
//		for(r=0; r<16; ++r)
//    			for(s=0; s<2; ++s)
//	     			printf("reg %i.%i: %f\n", r, s, 
//					*((double*) &mcontext.ymm[r].u64[s]));
		op1 = *((double*) &mcontext.ymm[s1].u64[0]);
		op2 = *((double*) &mcontext.ymm[s2].u64[0]);
      // 		dr_fprintf(logF, "%d: %.13lf  %.13lf\n",opcode, op1, op2);
		int exp1, exp2;
		double mant1, mant2;
		mant1 = frexp(op1, &exp1);
		mant2 = frexp(op2, &exp2);
		bits = abs(exp1-exp2);
		printf("op1 %.13lf mantissa %.13lf exp %d\n", op1, mant1, exp1);
		printf("op2 %.13lf mantissa %.13lf exp %d\n", op2, mant2, exp2);
	}
	print_address(addr, bits, loss, lossD);
}
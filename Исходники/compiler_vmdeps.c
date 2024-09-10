N_NIMCALL(NimStringDesc*, opslurp_379044)(NimStringDesc* file, Tlineinfo162338 info, Tsym190843* module) {
	NimStringDesc* volatile result;
	TSafePoint TMP2884;
	result = 0;
	pushSafePoint(&TMP2884);
	TMP2884.status = _setjmp(TMP2884.context);
	if (TMP2884.status == 0) {
		NimStringDesc* filename;
		Tnodeseq190807* LOC2;
		TY208694 LOC3;
		Tnode190813* LOC4;
		filename = findfile_154341(file);
		result = readfile_13434(filename);
		LOC2 = 0;
		LOC2 = (Tnodeseq190807*) newSeq((&NTI190807), 1);
		memset((void*)LOC3, 0, sizeof(LOC3));
		LOC3[0] = newstrnode_191644(((NU8) 20), filename);
		asgnRefNoCycle((void**) (&LOC2->data[0]), LOC3[0]);
		LOC4 = 0;
		LOC4 = newnode_192607(((NU8) 121), info, LOC2, NIM_NIL);
		appendtomodule_191911(module, LOC4);
		popSafePoint();
	}
	else {
		popSafePoint();
		if (isObj(getCurrentException()->Sup.m_type, (&NTI3431))) {
			TMP2884.status = 0;
			localerror_164171(info, ((NU16) 3), file);
			result = copyString(((NimStringDesc*) &TMP2885));
			popCurrentException();
		}
	}
	if (TMP2884.status != 0) reraiseException();
	return result;
}
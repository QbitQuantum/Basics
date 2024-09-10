N_LIB_PRIVATE N_NIMCALL(void, raiseFormatException_UlRj9cCVaVq3wqa9ckfyqy9cQ)(NimStringDesc* s) {
	tyObject_ValueError_5aqBlilCK53e9cDu4kUyN5Q* e;
	NimStringDesc* T1_;
	e = (tyObject_ValueError_5aqBlilCK53e9cDu4kUyN5Q*)0;
	e = (tyObject_ValueError_5aqBlilCK53e9cDu4kUyN5Q*) newObj((&NTI_yQYk49cCS1VAqkplQuc6KdQ_), sizeof(tyObject_ValueError_5aqBlilCK53e9cDu4kUyN5Q));
	(*e).Sup.Sup.Sup.m_type = (&NTI_5aqBlilCK53e9cDu4kUyN5Q_);
	T1_ = (NimStringDesc*)0;
	T1_ = rawNewString((s ? s->Sup.len : 0) + 30);
appendString(T1_, ((NimStringDesc*) &TM_ZT9crccxweoChVXn9cHcxIXQ_8));
appendString(T1_, s);
	asgnRefNoCycle((void**) (&(*e).Sup.Sup.message), T1_);
	raiseException((Exception*)e, "ValueError");
}
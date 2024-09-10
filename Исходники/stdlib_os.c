N_NOINLINE(void, nosraiseOSError)(NimStringDesc* msg) {
	{
		NimStringDesc* m;
		Oserror3433* e_115416;
		if (!((msg ? msg->Sup.len : 0) == ((NI) 0))) goto LA3;
		m = nososErrorMsg();
		e_115416 = 0;
		e_115416 = (Oserror3433*) newObj((&NTI115812), sizeof(Oserror3433));
		(*e_115416).Sup.Sup.Sup.m_type = (&NTI3433);
		{
			NimStringDesc* LOC9;
			if (!(((NI) 0) < (m ? m->Sup.len : 0))) goto LA7;
			LOC9 = 0;
			LOC9 = (*e_115416).Sup.Sup.message; (*e_115416).Sup.Sup.message = copyStringRC1(m);
			if (LOC9) nimGCunrefNoCycle(LOC9);
		}
		goto LA5;
		LA7: ;
		{
			NimStringDesc* LOC11;
			LOC11 = 0;
			LOC11 = (*e_115416).Sup.Sup.message; (*e_115416).Sup.Sup.message = copyStringRC1(((NimStringDesc*) &TMP1143));
			if (LOC11) nimGCunrefNoCycle(LOC11);
		}
		LA5: ;
		raiseException((Exception*)e_115416, "OSError");
	}
	goto LA1;
	LA3: ;
	{
		Oserror3433* e_115428;
		NimStringDesc* LOC13;
		e_115428 = 0;
		e_115428 = (Oserror3433*) newObj((&NTI115812), sizeof(Oserror3433));
		(*e_115428).Sup.Sup.Sup.m_type = (&NTI3433);
		LOC13 = 0;
		LOC13 = (*e_115428).Sup.Sup.message; (*e_115428).Sup.Sup.message = copyStringRC1(msg);
		if (LOC13) nimGCunrefNoCycle(LOC13);
		raiseException((Exception*)e_115428, "OSError");
	}
	LA1: ;
}
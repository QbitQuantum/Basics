N_NIMCALL(void, getservbyport_511233)(NU16 port, NimStringDesc* proto, Servent509610* Result) {
	struct servent* s;
	nimfr("getServByPort", "rawsockets.nim")
	nimln(261, "rawsockets.nim");
	s = getservbyport(((int) (((NI)(NU)(NU16)(((NI16)chckRange(port, ((NI16) -32768), ((NI16) 32767))))))), proto->data);
	nimln(262, "rawsockets.nim");
	{
		Oserror3433* e_511416;
		NimStringDesc* LOC5;
		if (!(s == NIM_NIL)) goto LA3;
		e_511416 = 0;
		nimln(2265, "system.nim");
		e_511416 = (Oserror3433*) newObj((&NTI116812), sizeof(Oserror3433));
		(*e_511416).Sup.Sup.Sup.m_type = (&NTI3433);
		nimln(2266, "system.nim");
		LOC5 = 0;
		LOC5 = (*e_511416).Sup.Sup.message; (*e_511416).Sup.Sup.message = copyStringRC1(((NimStringDesc*) &TMP10617));
		if (LOC5) nimGCunrefNoCycle(LOC5);
		nimln(262, "rawsockets.nim");
		raiseException((Exception*)e_511416, "OSError");
	}
	LA3: ;
	nimln(263, "rawsockets.nim");
	unsureAsgnRef((void**) (&(*Result).name), cstrToNimstr((*s).s_name));
	nimln(264, "rawsockets.nim");
	unsureAsgnRef((void**) (&(*Result).aliases), cstringarraytoseq_13843((*s).s_aliases));
	nimln(265, "rawsockets.nim");
	(*Result).port = ((NU16) ((*s).s_port));
	nimln(266, "rawsockets.nim");
	unsureAsgnRef((void**) (&(*Result).proto), cstrToNimstr((*s).s_proto));
	popFrame();
}
N_NIMCALL(void, HEX5BHEX5D_182417)(Table181466 t, int key, Selectorkey181439* Result) {
	NI hc_182428;
	NI index_182430;
	hc_182428 = 0;
	index_182430 = rawget_181585(t, key, (&hc_182428));
	{
		if (!(((NI) 0) <= index_182430)) goto LA3;
		(*Result).fd = t.data->data[index_182430].Field2.fd;
		(*Result).events = t.data->data[index_182430].Field2.events;
		unsureAsgnRef((void**) (&(*Result).data), t.data->data[index_182430].Field2.data);
	}
	goto LA1;
	LA3: ;
	{
		Keyerror3851* e_182602;
		NimStringDesc* LOC6;
		NimStringDesc* LOC7;
		e_182602 = 0;
		e_182602 = (Keyerror3851*) newObj((&NTI182603), sizeof(Keyerror3851));
		(*e_182602).Sup.Sup.Sup.m_type = (&NTI3851);
		LOC6 = 0;
		LOC7 = 0;
		LOC7 = nimIntToStr(key);
		LOC6 = rawNewString(LOC7->Sup.len + 15);
appendString(LOC6, ((NimStringDesc*) &TMP1111));
appendString(LOC6, LOC7);
		asgnRefNoCycle((void**) (&(*e_182602).Sup.Sup.message), LOC6);
		raiseException((Exception*)e_182602, "KeyError");
	}
	LA1: ;
}
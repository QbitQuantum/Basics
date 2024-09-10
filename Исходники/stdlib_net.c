N_NIMCALL(void, send_518209)(Socketimpl513407* socket, NimStringDesc* data, NU8 flags) {
	NI sent;
{	sent = send_517716(socket, ((void*) (data->data)), (data ? data->Sup.len : 0));
	{
		NI32 lasterror;
		if (!(sent < ((NI) 0))) goto LA3;
		lasterror = oslasterror_115833();
		{
			NIM_BOOL LOC7;
			LOC7 = 0;
			LOC7 = isdisconnectionerror_513481(flags, lasterror);
			if (!LOC7) goto LA8;
			goto BeforeRet;
		}
		LA8: ;
		socketerror_514027(socket, ((NI) -1), NIM_FALSE, lasterror);
	}
	LA3: ;
	{
		Oserror3433* e_518220;
		NimStringDesc* LOC14;
		if (!!((sent == (data ? data->Sup.len : 0)))) goto LA12;
		e_518220 = 0;
		e_518220 = (Oserror3433*) newObj((&NTI115812), sizeof(Oserror3433));
		(*e_518220).Sup.Sup.Sup.m_type = (&NTI3433);
		LOC14 = 0;
		LOC14 = (*e_518220).Sup.Sup.message; (*e_518220).Sup.Sup.message = copyStringRC1(((NimStringDesc*) &TMP4996));
		if (LOC14) nimGCunrefNoCycle(LOC14);
		raiseException((Exception*)e_518220, "OSError");
	}
	LA12: ;
	}BeforeRet: ;
}
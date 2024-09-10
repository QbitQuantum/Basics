N_NIMCALL(void, fswritedata_158925_1780494535)(Streamobj157818* s0, void* buffer0, NI buflen0) {
	{
		NI LOC3;
		Ioerror3628* LOC6;
		LOC3 = (NI)0;
		LOC3 = writebuffer_14978_1689653243((*((Filestreamobj158877*) (s0))).f, buffer0, ((NI) (buflen0)));
		if (!!((LOC3 == buflen0))) goto LA4;
		LOC6 = (Ioerror3628*)0;
		LOC6 = neweio_157802_1780494535(((NimStringDesc*) &T1780494535_6));
		raiseException((Exception*)LOC6, "IOError");
	}
	LA4: ;
}
N_NIMCALL(NI, npuParseInt)(NimStringDesc* S_23051, NI* Number_23053, NI Start_23054) {
NI Result_23055;
NI64 Res_23056;
NIM_BOOL LOC2;
NIM_BOOL LOC4;
EOverflow* E_23069;
Result_23055 = 0;
Res_23056 = 0;
Result_23055 = npuParseBiggestInt(S_23051, &Res_23056, Start_23054);
LOC2 = NIM_TRUE;
if (!(LOC2)) goto LA3;
LOC4 = (Res_23056 < (-2147483647 -1));
if (LOC4) goto LA5;
LOC4 = (2147483647 < Res_23056);
LA5: ;
LOC2 = LOC4;
LA3: ;
if (!LOC2) goto LA6;
E_23069 = 0;
E_23069 = (EOverflow*) newObj(NTI6051, sizeof(EOverflow));
(*E_23069).Sup.Sup.Sup.Sup.m_type = NTI432;
asgnRefNoCycle((void**) &(*E_23069).Sup.Sup.Sup.message, copyString(((NimStringDesc*) &TMP195656)));
raiseException((E_Base*)E_23069, "EOverflow");
goto LA1;
LA6: ;
(*Number_23053) = ((NI) (Res_23056));
LA1: ;
return Result_23055;
}
void _stdcall ResetCriticalTable(DWORD critter, DWORD bodypart, DWORD slot, DWORD element) {
 if(!Inited) return;
 if(critter>=CritTableCount||bodypart>=9||slot>=6||element>=7) return;
 //It's been a long time since we worried about win9x compatibility, so just sprintf it for goodness sake...
 char section[16];
 sprintf_s(section, "c_%02d_%d_%d", critter, bodypart, slot);
 CritStruct* defaultTable=(CritStruct*)_crit_succ_eff;
 critTable[slot].values[element]=critTable[slot].DamageMultiplier=GetPrivateProfileIntA(section, CritNames[element], defaultTable[slot].values[element], ".\\CriticalOverrides.ini");
}
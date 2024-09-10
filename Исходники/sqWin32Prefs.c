void SetDeferredUpdate() {
  CheckMenuItem(vmPrefsMenu, ID_DEFERUPDATES, MF_BYCOMMAND | 
		(fDeferredUpdate ? MF_CHECKED : MF_UNCHECKED));
  WritePrivateProfileString(U_GLOBAL,TEXT("DeferUpdate"),
			    fDeferredUpdate ? U_ON : U_OFF,squeakIniName);
}
/**
 * This function checks the version of an iconpack.
 * If the icon pack's version differs from the desired one, 
 * dialog with a warning is displayed.
 *
 * @param		szIconPack	- This is the path to the icon pack. 
 *							  It can be absolute or relative.
 *
 * @return	nothing
 **/
static void IcoLib_CheckIconPackVersion(LPTSTR szIconPack)
{
	if (db_get_b(NULL, MODNAME, SET_ICONS_CHECKFILEVERSION, TRUE)) {
		if (szIconPack) {
			TCHAR szAbsolutePath[MAX_PATH];
			PathToAbsoluteT(szIconPack, szAbsolutePath);

			HMODULE hIconDll = LoadLibrary(szAbsolutePath);
			if (hIconDll) {
				CHAR szFileVersion[64];

				if (!LoadStringA(hIconDll, IDS_ICOPACKVERSION, szFileVersion, sizeof(szFileVersion))
					|| mir_strcmp(szFileVersion, "__UserInfoEx_IconPack_1.2__"))
					MsgErr(NULL, LPGENT("Warning: Your current IconPack's version differs from the one UserInfoEx is designed for.\nSome icons may not be displayed correctly"));
				FreeLibrary(hIconDll);
			}
		}
		else
			MsgErr(NULL, LPGENT("Warning: No IconPack found in one of the following directories: 'customize\\icons', 'icons' or 'plugins'!"));
	}
}
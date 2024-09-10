// unregisters previously registered module 
int KL1_UnregisterModule (const WCHAR *name)
{
    HKEY hkey;

    int err = KL1_OpenHKey(hkey);

    if (err != KL1_SUCC)
    {
        return err;
    }

    if (g_os == KL1_OS_9X)
    {
		USES_CONVERSION;
		LONG nDelResult = RegDeleteValueA(hkey, W2A(name));
        if (nDelResult != ERROR_SUCCESS && nDelResult != ERROR_FILE_NOT_FOUND)
        {
			KL1_CloseHKey(hkey);
            return KL1_ERR;
        }
    }
    else
    {
		LONG nDelResult = RegDeleteValueW(hkey, name);
        if (nDelResult != ERROR_SUCCESS && nDelResult != ERROR_FILE_NOT_FOUND)
        {
			KL1_CloseHKey(hkey);
            return KL1_ERR;
        }
    }

	KL1_CloseHKey(hkey);

    return KL1_SUCC;
}
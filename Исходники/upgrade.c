static UINT ITERATE_FindRelatedProducts(MSIRECORD *rec, LPVOID param)
{
    MSIPACKAGE *package = (MSIPACKAGE*)param;
    WCHAR product[GUID_SIZE];
    DWORD index = 0;
    DWORD attributes = 0;
    DWORD sz = GUID_SIZE;
    LPCWSTR upgrade_code;
    HKEY hkey = 0;
    UINT rc = ERROR_SUCCESS;
    MSIRECORD *uirow;

    upgrade_code = MSI_RecordGetString(rec,1);

    rc = MSIREG_OpenUpgradeCodesKey(upgrade_code, &hkey, FALSE);
    if (rc != ERROR_SUCCESS)
        return ERROR_SUCCESS;

    uirow = MSI_CreateRecord(1);
    attributes = MSI_RecordGetInteger(rec,5);
    
    while (rc == ERROR_SUCCESS)
    {
        rc = RegEnumValueW(hkey, index, product, &sz, NULL, NULL, NULL, NULL);
        TRACE("Looking at (%li) %s\n",index,debugstr_w(product));
        if (rc == ERROR_SUCCESS)
        {
            WCHAR productid[GUID_SIZE];
            LPCWSTR ver;
            LPCWSTR language;
            LPCWSTR action_property;
            DWORD check = 0x00000000;
            DWORD comp_ver = 0x00000000;
            DWORD sz = 0x100;
            HKEY hukey;
            INT r;

            unsquash_guid(product,productid);
            rc = MSIREG_OpenUserProductsKey(productid, &hukey, FALSE);
            if (rc != ERROR_SUCCESS)
            {
                rc = ERROR_SUCCESS;
                index ++;
                continue;
            }
          
            sz = sizeof(DWORD);
            RegQueryValueExW(hukey, INSTALLPROPERTY_VERSIONW, NULL, NULL,
                    (LPBYTE)&check, &sz);
            /* check min */
            ver = MSI_RecordGetString(rec,2);
            comp_ver = msi_version_str_to_dword(ver);
            r = check - comp_ver; 
            if (r < 0 || (r == 0 && !(attributes &
                                    msidbUpgradeAttributesVersionMinInclusive)))
            {
                RegCloseKey(hukey);
                index ++;
                continue;
            }

            /* check max */
            ver = MSI_RecordGetString(rec,3);
            comp_ver = msi_version_str_to_dword(ver);
            r = check - comp_ver;
            if (r > 0 || (r == 0 && !(attributes & 
                                    msidbUpgradeAttributesVersionMaxInclusive)))
            {
                RegCloseKey(hukey);
                index ++;
                continue;
            }

            /* check language*/
            sz = sizeof(DWORD);
            RegQueryValueExW(hukey, INSTALLPROPERTY_LANGUAGEW, NULL, NULL,
                    (LPBYTE)&check, &sz);
            RegCloseKey(hukey);
            language = MSI_RecordGetString(rec,4);
            TRACE("Checking languages 0x%lx and %s\n", check, 
                            debugstr_w(language));
            if (!check_language(check, language, attributes))
            {
                index ++;
                continue;
            }

            action_property = MSI_RecordGetString(rec,7);
            append_productcode(package,action_property,productid);
            ui_actiondata(package,szFindRelatedProducts,uirow);
        }
        index ++;
    }
    RegCloseKey(hkey);
    msiobj_release( &uirow->hdr);
    
    return ERROR_SUCCESS;
}
HRESULT CAzAppGroup::CopyVersion2Constructs(CAzAppGroup &srcAppGroup) {

    static unsigned int rgProperties[]={AZ_PROP_GROUP_BIZRULE,AZ_PROP_GROUP_BIZRULE_LANGUAGE,AZ_PROP_GROUP_BIZRULE_IMPORTED_PATH};

    CComVariant cVVar;

    HRESULT hr=S_OK;

    if (!CAzGlobalOptions::m_bVersionTwo)
        goto lDone;

    for (long i=0;i<3;i++) {

        hr=srcAppGroup.m_native->GetProperty(rgProperties[i],CComVariant(), &cVVar);

        CAzLogging::Log(hr,_TEXT("Getting IAzApplicationGroup Property ID:"),COLE2T(srcAppGroup.getName()),rgProperties[i]);

        if (SUCCEEDED(hr) && (SysStringByteLen(cVVar.bstrVal))!=0) {

            hr=m_native->SetProperty(rgProperties[i],cVVar,CComVariant());

            CAzLogging::Log(hr,_TEXT("Setting IAzApplicationGroup Property ID:"),COLE2T(getName()),rgProperties[i]);

            cVVar.Clear();

        }

    }
lDone:
    return hr;
}
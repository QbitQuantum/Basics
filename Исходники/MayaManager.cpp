HRESULT
CMayaManager::GetExportOptions(bool forcePopup)
{
    HRESULT hr= S_OK;
    LPDXCCPROPERTYBAG pBag= NULL;
    UINT iProperty;
    char szSettingFile[MAX_PATH];
    MString mszAppDir;
    DXCCPROPERTY_KEY key= NULL;
    LPCVOID value= NULL;

    ZeroMemory(&ExportOpts, sizeof(DXCCSaveSceneArgs));

    MGlobal::executeCommand( "internalVar -userAppDir", mszAppDir, false, false );
    PathCombineA( szSettingFile, mszAppDir.asChar(), "DXCCExportOptions.xml" );

    if(DXCC_SUCCEEDED(DXCCLoadPropertyBagFromFile(szSettingFile, EXPORTER_OPTIONS_TYPENAME, EXPORTER_OPTIONS_VERSION, &pBag)))
    {
        key= pBag->GetKey(PROPERTY_POPUP);
        if(key)
        {
            pBag->GetPropertyValueAsData(key, &value);
            if(forcePopup || *(BOOL*)value)
            {
                DXCCShowPropertyBagDialog( pBag, EXPORTER_OPTIONS_TYPENAME, M3dView::applicationShell(), TRUE);
            }
        }

        DXCCSavePropertyBagAsFile( pBag, szSettingFile, EXPORTER_OPTIONS_TYPENAME, EXPORTER_OPTIONS_VERSION);
    }
    else
    {
        const BOOL True= true;
        const BOOL False= false;

        DXCCCreatePropertyBag(&pBag);
        pBag->AddProperty(PROPERTY_POPUP, &key);
        pBag->SetPropertyValueAsData(key, DXCCPD_BOOL, &True);
        pBag->AddProperty(PROPERTY_MESH, &key);
        pBag->SetPropertyValueAsData(key, DXCCPD_BOOL, &True);
        pBag->AddProperty(PROPERTY_ADJACENCIES, &key);
        pBag->SetPropertyValueAsData(key, DXCCPD_BOOL, &True);
        pBag->AddProperty(PROPERTY_MATERIALS, &key);
        pBag->SetPropertyValueAsData(key, DXCCPD_BOOL, &True);

        pBag->AddProperty(PROPERTY_EFFECTPATH_BOOL, &key);
        pBag->SetPropertyValueAsData(key, DXCCPD_BOOL, &False);
        pBag->AddProperty(PROPERTY_EFFECTPATH_TEXT, &key);
        pBag->SetPropertyValueAsData(key, DXCCPD_STRING, "");

        pBag->AddProperty(PROPERTY_TEXTUREPATH_BOOL, &key);
        pBag->SetPropertyValueAsData(key, DXCCPD_BOOL, &False);
        pBag->AddProperty(PROPERTY_TEXTUREPATH_TEXT, &key);
        pBag->SetPropertyValueAsData(key, DXCCPD_STRING, "");

        pBag->AddProperty(PROPERTY_RELATIVEPATH_BOOL, &key);
        pBag->SetPropertyValueAsData(key, DXCCPD_BOOL, &False);

        pBag->AddProperty(PROPERTY_ANIMATION, &key);
        pBag->SetPropertyValueAsData(key, DXCCPD_BOOL, &True);

        hr= DXCCShowPropertyBagDialog(pBag, EXPORTER_OPTIONS_TYPENAME, NULL, TRUE);
        if(DXCC_FAILED(hr))
            DXCC_GOTO_EXIT(e_Exit, FALSE);

        hr= DXCCSavePropertyBagAsFile( pBag, szSettingFile, EXPORTER_OPTIONS_TYPENAME, EXPORTER_OPTIONS_VERSION);
        if(DXCC_FAILED(hr))
            DXCC_GOTO_EXIT(e_Exit, FALSE);
    }

    key= pBag->GetKey(PROPERTY_MESH);
    pBag->GetPropertyValueAsData(key, &value);
    ExportOpts.NoMeshes= ! *(BOOL*)value;

    key= pBag->GetKey(PROPERTY_ADJACENCIES);
    pBag->GetPropertyValueAsData(key, &value);
    ExportOpts.NoMeshAdjacencies= ! *(BOOL*)value;

    key= pBag->GetKey(PROPERTY_MATERIALS);
    pBag->GetPropertyValueAsData(key, &value);
    ExportOpts.NoMeshMaterials= ! *(BOOL*)value;

    key= pBag->GetKey(PROPERTY_EFFECTPATH_BOOL);
    pBag->GetPropertyValueAsData(key, &value);
    ExportOpts.ReplaceEffectPaths= *(BOOL*)value;

    key= pBag->GetKey(PROPERTY_EFFECTPATH_TEXT);
    pBag->GetPropertyValueAsData(key, &value);
    StringCchCopyA(ExportOpts.ReplacementEffectPath, MAX_PATH, (LPCSTR)value);

    key= pBag->GetKey(PROPERTY_TEXTUREPATH_BOOL);
    pBag->GetPropertyValueAsData(key, &value);
    ExportOpts.ReplaceTexturePaths= *(BOOL*)value;

    key= pBag->GetKey(PROPERTY_TEXTUREPATH_TEXT);
    pBag->GetPropertyValueAsData(key, &value);
    StringCchCopyA(ExportOpts.ReplacementTexturePath, MAX_PATH, (LPCSTR)value);

    key= pBag->GetKey(PROPERTY_RELATIVEPATH_BOOL);
    pBag->GetPropertyValueAsData(key, &value);
    ExportOpts.RelativePaths= *(BOOL*)value;

    key= pBag->GetKey(PROPERTY_ANIMATION);
    pBag->GetPropertyValueAsData(key, &value);
    ExportOpts.NoAnimation= ! *(BOOL*)value;

e_Exit:
    DXCC_RELEASE(pBag);

    return hr;
}
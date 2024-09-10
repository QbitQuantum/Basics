BOOL CTypeInfos::GetType(IDiaSymbol* pSymbol, BOOL bBaseType )
{
    BOOL bRet;
    HRESULT hResult;
    IDiaSymbol* pBaseType;
    DWORD dwTag=SymTagNull;
    
    // until a name is found try to get name
    if (!this->Name)
    {
        BSTR Name=NULL;
        pSymbol->get_name(&Name);

        if (Name)
        {
#if (defined(UNICODE)||defined(_UNICODE))
            this->Name=_tcsdup(Name);
#else
            CAnsiUnicodeConvert::UnicodeToAnsi(Name,&this->Name);
#endif
            SysFreeString(Name);
        }
    }
    else
    {
        if ( bBaseType && (!this->TypeName) )
        {
            BSTR TypeName=NULL;
            pSymbol->get_name(&TypeName);

            if (TypeName)
            {
#if (defined(UNICODE)||defined(_UNICODE))
                this->TypeName=_tcsdup(TypeName);
#else
                CAnsiUnicodeConvert::UnicodeToAnsi(TypeName,&this->TypeName);
#endif
                SysFreeString(TypeName);
            }
        }
    }

    pSymbol->get_length(&this->Size);
    pSymbol->get_constType(&this->bConst);
    pSymbol->get_volatileType(&this->bVolatile);
    pSymbol->get_unalignedType(&this->bUnaligned);

    hResult=pSymbol->get_symTag(&dwTag);
    if(FAILED(hResult) || (dwTag==SymTagNull))
        return FALSE;

    if (this->DataKind==SymTagNull)
        this->DataKind=dwTag;

    switch(dwTag)
    {
    case SymTagUDT:
        {
            BSTR UDTName;
            if (FAILED(pSymbol->get_udtKind(&this->UserDefineTypeKind)))
                return FALSE;

            pSymbol->get_name(&UDTName);
            WCHAR* wName;
            // don't put struct / enum / class keyword info to this->TypeName
            // keep only type name
            // wName =(WCHAR*) _alloca((wcslen(rgUdtKind[this->UserDefineTypeKind])+wcslen(UDTName)+2)*sizeof(WCHAR));
            //swprintf(wName,L"%s %s",rgUdtKind[this->UserDefineTypeKind],UDTName);
            wName =(WCHAR*) _alloca((wcslen(UDTName)+1)*sizeof(WCHAR));
            wcscpy(wName,UDTName);
            this->bUserDefineType=TRUE;

#if (defined(UNICODE)||defined(_UNICODE))
            this->TypeName=_tcsdup(wName);
#else
            CAnsiUnicodeConvert::UnicodeToAnsi(wName,&this->TypeName);
#endif
            SysFreeString(UDTName);
        }
        break;

    case SymTagEnum:
        this->bEnum=TRUE;
        break;

    case SymTagFunctionType:
        this->bFunction=TRUE;
        break;

    case SymTagPointerType:
        pBaseType=0;
        pSymbol->get_reference(&this->bRefPointer);
        hResult=pSymbol->get_type(&pBaseType);
        if(FAILED(hResult) || (pBaseType==0))
            return FALSE;

        bRet=this->GetType(pBaseType,TRUE);
        this->PointerLevel++;
        pBaseType->Release();
        if (!bRet)
            return FALSE;
        break;

    case SymTagArrayType:
        pBaseType=0;
        hResult=pSymbol->get_type(&pBaseType);
        if(FAILED(hResult) || (pBaseType==0))
            return FALSE;

        // simplify , don't get array length (sized provided for local vars)
        this->PointerLevel++;
        bRet=this->GetType(pBaseType,TRUE);
        pBaseType->Release();
        if (!bRet)
            return FALSE;
        break;
    case SymTagBaseType:
        {
            WCHAR wsType[MAX_PATH];
            ULONGLONG ulLen;
            pSymbol->get_length(&ulLen); // ukLen may differ from this->Size (if pointer or other type)
            *wsType=0;

            if(FAILED(pSymbol->get_baseType(&this->BaseType)))
                return FALSE;

            switch(this->BaseType)
            {
                case btUInt :
                    wcscpy(wsType,L"unsigned ");
                // don't break btUInt to Fall through btInt
                case btInt :
                    switch(ulLen)
                    {
                        case 1:
                            wcscat(wsType,L"char");
                            break;
                        case 2:
                            wcscat(wsType,L"short");
                            break;
                        case 4:
                            wcscat(wsType,L"int");
                            break;
                        case 8:
                            wcscat(wsType,L"int64");
                            break;
                    }
                    break;
                case btFloat :
                    switch(ulLen)
                    {
                        case 4:
                            wcscpy(wsType,L"float");
                            break;
                        case 8:
                            wcscpy(wsType,L"double");
                            break;
                    }
                    break;
                }

                // if type not filled
                if(*wsType==0)
                    // get the one defined by array
                    wcscpy(wsType,rgBaseType[this->BaseType]);
            
#if (defined(UNICODE)||defined(_UNICODE))
                this->TypeName=_tcsdup(wsType);
#else
                CAnsiUnicodeConvert::UnicodeToAnsi(wsType,&this->TypeName);
#endif
        }
        break;
    case SymTagCustomType: 
        break;
    case SymTagData:
        pBaseType=0;
        hResult=pSymbol->get_type(&pBaseType);
        if(FAILED(hResult) || (pBaseType==0))
            return FALSE; // no information : can appear for local type (static can be name of local vars. Debug infos ???)

        bRet=this->GetType(pBaseType,TRUE);
        pBaseType->Release();
        if (!bRet)
            return FALSE;
        break;
    case SymTagUsingNamespace:
        break;
    case SymTagTypedef: // should not appear
        break;
    default:
#ifdef _DEBUG
        if (IsDebuggerPresent())
            DebugBreak();
#endif
        break;
    }

    return TRUE;
}
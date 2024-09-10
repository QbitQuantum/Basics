BOOL CObjectEntry::StoreObjectDictionarySchema(XML_PARSER* pXmlParser)
{
    CStdString strIndex = "";
    CStdString strSubIndex = "";
    CStdString strParameterName = "";
    CStdString strObjectType = "";
    CStdString strDataType = "";
    CStdString strAccessType = "";
    CStdString strLowLimit = "";
    CStdString strHighLimit = "";
    CStdString strDefaultValue = "";
    CStdString strPDOMapping = "";
    CStdString strObjFlags = "";

    if(pXmlParser)
    {
        //ObjectEntry
        pXmlParser->AddNewLineTab();
        pXmlParser->Add_LastChildNode(_T("ObjectEntry"));
        pXmlParser->IncTabLevel();

        //Prepare Attributes
        GetIndex(strIndex);
        GetSubIndex(strSubIndex);
        GetParameterName(strParameterName);
        GetObjectType(strObjectType);
        GetDataType(strDataType, FALSE);
        GetAccessType(strAccessType);
        GetLowLimit(strLowLimit);
        GetHighLimit(strHighLimit);
        GetDefaultValue(strDefaultValue);
        GetPDOMapping(strPDOMapping);
        GetObjFlags(strObjFlags);

        //ObjectEntry Attributes
        pXmlParser->Set_Attribute(_T("Index"), strIndex);
        pXmlParser->Set_Attribute(_T("SubIndex"), strSubIndex);
        pXmlParser->Set_Attribute(_T("ParameterName"), strParameterName);
        pXmlParser->Set_Attribute(_T("ObjectType"), strObjectType);
        pXmlParser->Set_Attribute(_T("DataType"), strDataType);
        pXmlParser->Set_Attribute(_T("AccessType"), strAccessType);

        if(!strLowLimit.IsEmpty()) pXmlParser->Set_Attribute(_T("LowLimit"), strLowLimit);
        if(!strHighLimit.IsEmpty()) pXmlParser->Set_Attribute(_T("HighLimit"), strHighLimit);
        if(!strDefaultValue.IsEmpty()) pXmlParser->Set_Attribute(_T("DefaultValue"), strDefaultValue);
        if(!strPDOMapping.IsEmpty()) pXmlParser->Set_Attribute(_T("PDOMapping"), strPDOMapping);
        if(!strObjFlags.IsEmpty()) pXmlParser->Set_Attribute(_T("ObjFlags"), strObjFlags);

        //End ObjectEntry
        pXmlParser->DecTabLevel();
        pXmlParser->AddNewLineTab();
        pXmlParser->Go_to_Parent();

        return TRUE;
    }

    return FALSE;
}
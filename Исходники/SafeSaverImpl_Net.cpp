HRESULT CSafeSaverNetImpl::CopyCfData(SCfData& sCfData)
{
    CCameraData* pCameraData = sCfData.pRefData->GetItem();
    DWORD32 dwDataLen = 0;
    memcpy((char*)m_sBuf.addr + dwDataLen, &pCameraData->header, sizeof(pCameraData->header));
    dwDataLen += sizeof(pCameraData->header);
    memcpy((char*)m_sBuf.addr + dwDataLen, pCameraData->pbInfo, pCameraData->header.dwInfoSize);
    dwDataLen += pCameraData->header.dwInfoSize;
    memcpy((char*)m_sBuf.addr + dwDataLen, pCameraData->pbData, pCameraData->header.dwDataSize);
    dwDataLen += pCameraData->header.dwDataSize;

    if (0 == sCfData.iDataType)//识别结果,修正CarID
    {
        BLOCK_HEADER cBlockHeader;
        char* pXML = NULL;
        char* pbTemp = (char*)m_sBuf.addr + sizeof(CAMERA_INFO_HEADER);
        //修正数据类型
        DWORD32 dwRecordType = CAMERA_RECORD_HISTORY;
        memcpy(pbTemp+8, &dwRecordType, 4);

        for (int i = 0; i < (int)pCameraData->header.dwInfoSize; )
        {
            memcpy(&cBlockHeader, pbTemp, sizeof(BLOCK_HEADER));
            pbTemp += sizeof(BLOCK_HEADER);
            i += sizeof(BLOCK_HEADER);

            if (cBlockHeader.dwID == BLOCK_XML_TYPE)  // 识别结果XML附加信息
            {
                pXML = pbTemp;
                if (strstr(pXML, "违章:是"))
                {
                    sCfData.dwDataInfo = 1;
                }
                break;
            }

            pbTemp += cBlockHeader.dwLen;
            i += cBlockHeader.dwLen;
        }

        TiXmlDocument xmlDoc;
        xmlDoc.Parse(pXML);
        if (pXML && xmlDoc.RootElement())
        {
            TiXmlElement* pElement = xmlDoc.RootElement()->FirstChildElement("ResultSet");
            if (pElement)
            {
                pElement = pElement->FirstChildElement("Result");
            }
            TiXmlElement* pElementCarId = NULL;
            TiXmlElement* pElementTimeLow = NULL;
            TiXmlElement* pElementTimeHigh = NULL;
            if (pElement)
            {
                pElementCarId = pElement->FirstChildElement("CarID");
                pElementTimeLow = pElement->FirstChildElement("TimeLow");
                pElementTimeHigh = pElement->FirstChildElement("TimeHigh");
            }
            if (pElementTimeLow)
            {
                const TiXmlAttribute* attr = pElementTimeLow->FirstAttribute();
                for (; attr; attr=attr->Next())
                {
                    if (0 == strcmp(attr->Name(), "value"))
                    {
                        sscanf(attr->Value(), "%u", &sCfData.dwTimeLow);
                        break;
                    }
                }
            }
            if (pElementTimeHigh)
            {
                const TiXmlAttribute* attr = pElementTimeHigh->FirstAttribute();
                for (; attr; attr=attr->Next())
                {
                    if (0 == strcmp(attr->Name(), "value"))
                    {
                        sscanf(attr->Value(), "%u", &sCfData.dwTimeHigh);
                        break;
                    }
                }
            }
            if (pElementCarId)
            {
#if FIX_FILE_VER == 1
                DWORD32 dwCarID = m_cCfRecord.GetHourCount(sCfData.dwTimeLow, sCfData.dwTimeHigh);
#else
                DWORD32 dwCarID;
                GetHourCount(sCfData.dwTimeLow, sCfData.dwTimeHigh, &dwCarID);
                sCfData.dwIndex = dwCarID;
#endif
                char szValue[32] = {0};
                sprintf(szValue, "%u", dwCarID);
                pElementCarId->SetAttribute("value", szValue);

                TiXmlPrinter cTxPr;
                xmlDoc.Accept(&cTxPr);
                strcpy(pXML, cTxPr.CStr());
            }
        }
    }
    else
    {
        REAL_TIME_STRUCT rtsTime;
        ConvertMsToTime(sCfData.dwTimeLow, sCfData.dwTimeHigh, &rtsTime);
        sCfData.dwIndex = rtsTime.wMinute * 60 + rtsTime.wSecond;
    }

    return S_OK;
}
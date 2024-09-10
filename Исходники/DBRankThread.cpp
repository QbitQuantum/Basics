// 数据加载操作
bool DBRankThread::LoadRanks(tagRankInfo *pRankInfo)
{
    if(NULL == pRankInfo)
        return false;

//    DWORD dwBegin = timeGetTime();   

    map<long, tagRankConfig>::iterator itor = GetGame()->GetEntityManager()->GetRankMap().find(pRankInfo->lRankID);
    if(itor != GetGame()->GetEntityManager()->GetRankMap().end())
    {
        tagRankConfig stRankConfig = itor->second;
        _RecordsetPtr rs;

        try
        {
            GetAdoBasePtr()->CreateRs(rs);
            GetAdoBasePtr()->OpenRs(stRankConfig.strCurSQL.c_str(), rs);

        }
        catch (_com_error &e)
        {
          //  _com_issue_error(E_FAIL);
            // 发生异常,通常表现为所连数据库的机子断网了(若数据库和程序在同一机器上不会，除非数据库宕了)
            // 这个时候连接指针已经失效了，需要关闭重新创建
            // 当然这种修复只有在下一次轮询中才会得到成功所用
            GetAdoBasePtr()->PrintErr("LoadRanks Error!!!",e);
            GetAdoBasePtr()->CloseCn();
            GetAdoBasePtr()->OpenCn();
            return false;
        }
   

        pRankInfo->EnterCS();
        // clear data first
        pRankInfo->Clear();

        // then begin update data 
        pRankInfo->ulUpdateTime = timeGetTime();
        for(long l=0; l < rs->GetFields()->GetCount(); l++)
        {
            tagColInfo tgColInfo;
            tgColInfo.strColName = rs->GetFields()->GetItem(l)->GetName();
            strlwr((char*)tgColInfo.strColName.c_str());
            DataTypeEnum dt = rs->GetFields()->GetItem(l)->GetType();
            switch(dt)
            {
            case adChar:
            case adBSTR:                    
            case adVarChar:
            case adLongVarChar:
            case adWChar:
            case adVarWChar:
            case adLongVarWChar:
                {
                    tgColInfo.dt = CT_STRING;
                }
                break;
            case adGUID:
                {
                    tgColInfo.dt = CT_GUID;
                }
                break;
            case adTinyInt:
            case adSmallInt:
            case adBigInt:
            case adUnsignedTinyInt:
            case adUnsignedSmallInt:
            case adUnsignedInt:
            case adUnsignedBigInt:
            case adSingle:
            case adInteger:
            case adNumeric:
            case adDecimal:
                {
                    tgColInfo.dt = CT_LONG;
                }
                break;

            case adDouble:
                {
                    tgColInfo.dt = CT_FLOAT;
                }
                break;

            case adDate:
            case adDBDate:
            case adDBTime:
            case adDBTimeStamp:
                {
                    tgColInfo.dt = CT_TIME;
                }
                break;
            case adBinary:
            case adVarBinary:
            case adLongVarBinary:
                {
                    tgColInfo.dt = CT_BUFFER;
                }
                break;
            default:
                {
                    tgColInfo.dt = CT_UNKNOWN;
                }
                break;
            }
            pRankInfo->vecColInfo.push_back(tgColInfo);
        }
        long lCurLvl = 1;
        while(!rs->GetadoEOF())
        {
            CTableManager* pDataManager = new CTableManager;                    
            long lAttrNum = 0;
            for(size_t lVecCol = 0; lVecCol < pRankInfo->vecColInfo.size(); lVecCol++)
            {
                tagColInfo stInfo = pRankInfo->vecColInfo[lVecCol];

                variant_t var = rs->GetCollect(stInfo.strColName.c_str());
                CDataObject* pEntity = pDataManager->CreateColumnData(lAttrNum);
                switch(stInfo.dt)
                {
                    //     case DATA_OBJECT_BYTE:
                case CT_STRING:
                    {
                        //    pEntity->SetDataType(DATA_OBJECT_STRING);
                        pEntity->SetStringValue(string((_bstr_t)var).c_str(), (long)string((_bstr_t)var).size());
                    }
                    break;

                case CT_GUID:
                    {
                        //     pEntity->SetDataType(DATA_OBJECT_GUID);
                        CGUID tGUID(string(_bstr_t(var)).c_str());
                        pEntity->SetGUIDValue(tGUID);
                    }
                    break;
                case CT_LONG:
                    {
                        long lVal = var.lVal;
                        pEntity->SetLongValue(lVal);                        
                    }
                    break;

                case CT_FLOAT:
                    {
                        float fValue = var.fltVal;
                        pEntity->SetBufValue((void*)&fValue, sizeof(float));
                    }
                    break;
                case CT_TIME:
                    {
                        //     pEntity->SetDataType(DATA_OBJECT_TIME);
                        long timeBuf[6] = {0};
                        SYSTEMTIME st;
                        VariantTimeToSystemTime(var.date, &st);
                        timeBuf[0] = st.wYear;
                        timeBuf[1] = st.wMonth;
                        timeBuf[2] = st.wDay;
                        timeBuf[3] = st.wHour;
                        timeBuf[4] = st.wMinute;
                        timeBuf[5] = st.wSecond;
                        if(timeBuf[0] == 1900 && timeBuf[1] == 1 && timeBuf[2] == 1)
                            memset(timeBuf, 0, sizeof(timeBuf));
                        pEntity->SetBufValue((void*)&timeBuf[0], sizeof(long)*6);
                    }
                    break;
                case CT_BUFFER:
                    {
                        //  pEntity->SetBufAttr()
                    }
                    break;
                }
                lAttrNum++;
            }
            pRankInfo->vecColData.push_back(pDataManager);                    
            rs->MoveNext();
            lCurLvl++;
        }
        // update data end
        GetAdoBasePtr()->ReleaseRs(rs);
        pRankInfo->LeaveCS();        
    }
    else
    {
        return false;
    }


    SendRanksToWS(pRankInfo->lRankID);
    UpdateRanks(pRankInfo->lRankID);


    return true;
}
void CGraphicView::ReloadLabelsFromDB()
{
    ClearAllLabels();

    m_pCon.CreateInstance(_T("ADODB.Connection"));
    m_pRs.CreateInstance(_T("ADODB.Recordset"));
    m_pCon->Open(g_strDatabasefilepath.GetString(),_T(""),_T(""),adModeUnknown);
    CString strSql;
    //if(bac_cm5_graphic == false)
    strSql.Format(_T("select * from Screen_Label where Serial_Num =%i and Tstat_id=%i"),m_nSerialNumber,m_nTstatID);
    //else
    //strSql.Format(_T("select * from Screen_Label where Serial_Num =%i and Tstat_id=%i"),g_bac_instance,g_mac);
    //strSql.Format(_T("select * from Screen_Label where Tstat_id=%i"),m_nTstatID);
    m_pRs->Open((_variant_t)strSql,_variant_t((IDispatch *)m_pCon,true),adOpenStatic,adLockOptimistic,adCmdText);
    CString strtemp;
    strtemp.Empty();

    _variant_t temp_variant;
    int nTemp;
    CString strTemp;
    int nItem = 0;//用于记录有多少个需要刷新;
    while(VARIANT_FALSE==m_pRs->EndOfFile)
    {
        Label_information label;

        label.nSerialNum=m_nSerialNumber;
        label.tstat_id=m_nTstatID;
        label.strScreenName=m_strScreenName;

        nTemp=m_pRs->GetCollect("Cstatic_id");//
        label.cstatic_id=nTemp;

        nTemp=m_pRs->GetCollect("Point_X");//
        label.point.x=nTemp;

        nTemp=m_pRs->GetCollect("Point_Y");//
        label.point.y=nTemp;

        nTemp=m_pRs->GetCollect("Height");//
        label.height=nTemp;

        nTemp=m_pRs->GetCollect("Width");//
        label.width=nTemp;

        nTemp=m_pRs->GetCollect("Status");//
        label.status=nTemp;

        temp_variant=m_pRs->GetCollect("Tips");//
        if(temp_variant.vt!=VT_NULL)
            strtemp=temp_variant;
        else
            strtemp=_T("");
        label.strTips=strtemp;

        /*
        temp_variant=m_pRs->GetCollect("Tips");//
        if(temp_variant.vt!=VT_NULL)
        	strtemp=temp_variant;
        else
        	strtemp=_T("");
        label.strTips=strtemp;
        */


        nTemp=m_pRs->GetCollect("Input_or_Output");//
        label.input_or_output=nTemp;


        strTemp=m_pRs->GetCollect("Text_Color");//
        if(strTemp.IsEmpty())
        {
            label.clrTxt=0;
        }
        else
        {
            label.clrTxt=_wtol(strTemp);
        }


        strTemp=m_pRs->GetCollect("Back_Color");//
        if(strTemp.IsEmpty())
        {
            label.bkColor=254*255*255;
        }
        else
        {
            label.bkColor=_wtol(strTemp);
        }
        //	label.bkColor=nTemp;
        CRelayLabel* pLabel=new(CRelayLabel);
        pLabel->Create(_T(""),WS_CHILD|WS_VISIBLE|SS_CENTER,CRect(XStart+label.point.x,YStart+label.point.y,XStart+label.point.x+label.width,YStart+label.point.y+label.height), this,label.cstatic_id);

        //(int TstatID,int input_or_output,int nStatus,COLORREF textClr,COLORREF bkClr)
        pLabel->SetLabelInfo(label.tstat_id,label.input_or_output,label.status,label.clrTxt,label.bkColor);
        pLabel->MoveWindow(CRect(XStart+label.point.x,YStart+label.point.y,XStart+label.point.x+label.width,YStart+label.point.y+label.height));
        label.plabelCtrl=pLabel;
        m_RelayLabelLst.push_back(label);

        m_pRs->MoveNext();
        _Graphic_Value_Info temp1;
        m_graphic_refresh_data.push_back(temp1);
        m_graphic_refresh_data.at(nItem).deviceid = label.tstat_id;
        m_graphic_refresh_data.at(nItem).value_type = label.input_or_output;
        m_graphic_refresh_data.at(nItem).value_item = label.status;
        m_graphic_refresh_data.at(nItem).control_pt = pLabel;
        if(label.input_or_output == 0)
        {
            m_graphic_refresh_data.at(nItem).command = READINPUT_T3000;
            m_graphic_refresh_data.at(nItem).entitysize = sizeof(Str_in_point);
        }
        else if(label.input_or_output == 1)
        {
            m_graphic_refresh_data.at(nItem).command = READOUTPUT_T3000;
            m_graphic_refresh_data.at(nItem).entitysize = sizeof(Str_out_point);
        }
        else if(label.input_or_output == 2)
        {
            m_graphic_refresh_data.at(nItem).command = READVARIABLE_T3000;
            m_graphic_refresh_data.at(nItem).entitysize = sizeof(Str_variable_point);
        }
        m_graphic_refresh_data.at(nItem).hWnd = this->m_hWnd;
        nItem ++;
    }

    if(m_pRs->State)
        m_pRs->Close();
    if(m_pCon->State)
        m_pCon->Close();

}
void ByjDrawRightRect::CalcSonFiguer(CDC* pDC,CRect &rt)
{
    m_rectDrawLine = rt;
    {
        m_dataFormular .numLine = 0;
        CFormularContent*	pIndex;
        pIndex=(CFormularContent*)pDoc->LookUpArray (pDoc->m_formuar_index,m_nameIndex);
        if(pIndex!=NULL)
            if(!pIndex->IsValid()) return;

        if(pIndex==NULL || pView->m_nCountKline<=0)
        {
            return;
        }

        m_nValidIndicator  = CTaiScreenParent::IsPeriodValid(pView->m_nKlineKind2 ,pIndex);

        CString s ;

        CString str = " ";


        CFormularCompute* m_formuCompute = NULL;
        INPUT_PARAM input;
        input.pmax			=pView->m_nCountKline-1;
        input.pp			= pView->m_pkline;
        input.symbol		= pView->m_sharesSymbol ;
        input.nKindKline	= pView->m_nKlineKind2 ;
        input.pBuySellList	=&( pView->m_hs) ;
        input.pIndex		= pIndex;
        input.bAddBuySell   = false;
        input.m_stkKind		= pView->m_stkKind;

        float fMax, fMin;
        fMax = pView->m_pkline[0].high ;
        fMin = pView->m_pkline[0].low ;
        for(int j=1; j<pView->m_nCountKline; j++)
        {
            if(pView->m_pkline[j].high>fMax)
                fMax = pView->m_pkline[j].high;
            if(pView->m_pkline[j].low<fMin)
                fMin = pView->m_pkline[j].low;
        }

        ARRAY_Right_Box::SetTime (CTime(pView->m_pkline [pView->pKlineDrawing ->m_footCurrent].day )) ;
        TRACE("pView->pKlineDrawing ->m_footCurrent: %d   ; \n",pView->pKlineDrawing ->m_footCurrent);
        ARRAY_Right_Box::GetRuler(fMax, fMin);

        CTaiKlineShowKline *pDoK = pView->pKlineDrawing ;
        pDoK->m_nSon=0;
        pDoK->SetRectCurrent(0);

        if(ComputeFormu2(m_formuCompute,input)==0)
        {
            int rtnLine=0;
            m_dataFormular .numLine =m_formuCompute->GetRlineNum ();
            if(m_dataFormular .numLine>18)
                m_dataFormular .numLine = 18;

            for(int i=0 ; i<m_dataFormular .numLine ; i++)
            {

                CString namePer;
                int nIn = i ;
                rtnLine = m_formuCompute->GetLine (nIn,m_dataFormular .line [i].m_arrBE,namePer);
                if(rtnLine==1)
                    m_dataFormular .line [i].m_arrBE.b = -1;

                m_dataFormular .line [i].type = m_formuCompute->m_RlineType[i] ;

                if(namePer.GetLength()>18)
                    m_lineName [i]="Î´Öª";
                else
                    m_lineName [i]=namePer;
                GetMaxMin(i,i==0);


            }
            for(int i=0 ; i<m_dataFormular .numLine ; i++)
            {
                DrawSonFiguer( pDC,i);
            }
            DrawCaption(pDC, pIndex);

        }
        else
            ;

        delete m_formuCompute;
        ARRAY_Right_Box::Reset ();
    }

}
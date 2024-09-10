/*******************************************************************************
  Function Name  : SetConfigData
  Input(s)       : pvDataStream
  Output         : -
  Functionality  : Sets the Bus stats dialog Configuration from Byte Array.
  Member of      : CBusStatisticsDlg
  Author(s)      : Arunkumar K
  Date Created   : 25-08-2010
  Modifications  :
*******************************************************************************/
HRESULT CBusStatisticsDlg::SetConfigData(BYTE* pvDataStream)
{
    BYTE* pByteSrc = NULL;
    pByteSrc = pvDataStream;

    if (pByteSrc != NULL)
    {
        //Reading Version.
        BYTE byVer = 0;
        COPY_DATA_2(&byVer, pByteSrc, sizeof(BYTE));
        UINT nSize= 0;
        //Reading Buffer Size.
        COPY_DATA_2(&nSize, pByteSrc, sizeof(UINT));

        if ((byVer == BUS_STATS_DLG_VERSION) && (nSize > 0))
        {
            //Reading column Header Positions.
            CHeaderCtrl* pHeaderCtrl = m_omStatList.GetHeaderCtrl();

            if (pHeaderCtrl != NULL)
            {
                int  nColumnCount=0;
                //Reading column count.
                COPY_DATA_2(&nColumnCount, pByteSrc, sizeof(UINT));

                //Saved channel count is same as current channel count.
                if(nColumnCount==m_nChannelCount+1)
                {
                    LPINT pnOrder = (LPINT) malloc(nColumnCount*sizeof(int));

                    for (int i = 0 ; i < nColumnCount; i++)
                    {
                        COPY_DATA_2(&pnOrder[i], pByteSrc, sizeof(int));
                        bool bColumnVisible = false;
                        //Reading visibility
                        COPY_DATA_2(&bColumnVisible, pByteSrc, sizeof(bool));
                        m_omStatList.MakeColumnVisible(i, bColumnVisible);
                        INT nColWidth = 0;
                        //Reading width
                        COPY_DATA_2(&nColWidth, pByteSrc, sizeof(int));
                        m_omStatList.SetColumnWidth(i, nColWidth);
                    }

                    m_omStatList.SetColumnOrderArray(nColumnCount, pnOrder);
                    free(pnOrder);
                }
                else //Saved channel count differs from current channel count.
                {
                    vLoadDefaultValues();
                }
            }

            WINDOWPLACEMENT sMsgWndPlacement;
            COPY_DATA_2(&sMsgWndPlacement, pByteSrc, sizeof(WINDOWPLACEMENT));
            SetWindowPlacement(&sMsgWndPlacement);
        }
    }

    return S_OK;
}
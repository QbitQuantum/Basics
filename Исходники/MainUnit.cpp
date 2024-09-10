void __fastcall TForm1::btnNativeJustTimeClick(TObject *Sender)
{
    if(tvConnectDev->Selected == NULL) return;
    DEVICE_STATUS devStatusInfo;
    String strInfo;

    PDevInfo pDev = NULL;
    TTreeNodes *nodes = tvConnectDev->Items;
    if(nodes != NULL)
    {
        for(int i = 0; i < nodes->Count; i++)
        {
            if(TreeView_GetCheckState(tvConnectDev->Handle,nodes->Item[i]->ItemId))
            {
              String strViewIP = nodes->Item[i]->Text;

                for(int j = 0; j < pDevList->Count; j++)
                {
                    pDev = PDevInfo(pDevList->Items[j]);
                    if(pDev != NULL)
                    {
                        String strDevListIP;
                        strDevListIP.sprintf("%s", pDev->ucIP);
                        if(strDevListIP == strViewIP)
                        {   if(pDev->pHandle != NULL)
                            {
                                int nRes = AdjustTime(pDev->pHandle, 0);
                                if(nRes != 0) ShowMessage("使用本地系统时间校时失败，返回值 = " + IntToStr(nRes));
                                else ShowMessage("校时成功");

                                return;
                            }
                        }
                    }
                }
            }
        }
    }
}
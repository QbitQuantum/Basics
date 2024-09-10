void CUploadListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if (!theApp.emuledlg->IsRunning())
        return;
    if (!lpDrawItemStruct->itemData)
        return;

    // ==> Visual Studio 2010 Compatibility [Stulle/Avi-3k/ied] - Stulle
    /*
    CMemDC dc(CDC::FromHandle(lpDrawItemStruct->hDC), &lpDrawItemStruct->rcItem);
    */
    CMemoryDC dc(CDC::FromHandle(lpDrawItemStruct->hDC), &lpDrawItemStruct->rcItem);
    // <== Visual Studio 2010 Compatibility [Stulle/Avi-3k/ied] - Stulle
    BOOL bCtrlFocused;
    //Xman narrow font at transferwindow
    /*
    InitItemMemDC(dc, lpDrawItemStruct, bCtrlFocused);
    */
    // ==> Design Settings [eWombat/Stulle] - Stulle
    /*
    InitItemMemDC(dc, lpDrawItemStruct, bCtrlFocused, true);
    //Xman end
    */
    InitItemMemDC(dc, lpDrawItemStruct, bCtrlFocused, true, style_b_uploadlist);
    // <== Design Settings [eWombat/Stulle] - Stulle
    CRect cur_rec(lpDrawItemStruct->rcItem);
    CRect rcClient;
    GetClientRect(&rcClient);
    const CUpDownClient *client = (CUpDownClient *)lpDrawItemStruct->itemData;

    // ==> Design Settings [eWombat/Stulle] - Stulle
    /*
    COLORREF crOldBackColor = dc->GetBkColor(); //Xman PowerRelease
    */
    // <== Design Settings [eWombat/Stulle] - Stulle
    //Xman Xtreme Upload
    /*
    if (client->GetSlotNumber() > theApp.uploadqueue->GetActiveUploadsCount())
        dc.SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
    }
    */
    const ThrottledFileSocket* socket=(client->GetFileUploadSocket());
    if( socket!=NULL)
    {
        // ==> Design Settings [eWombat/Stulle] - Stulle
        /*
        if (socket->IsFull())
        	dc.SetTextColor(RGB(0,0,0));
        else if (socket->IsTrickle())
        	dc.SetTextColor(::GetSysColor(COLOR_GRAYTEXT));
        */
#define MLC_BLEND(A, B, X) ((A + B * (X-1) + ((X+1)/2)) / X)

#define MLC_RGBBLEND(A, B, X) (                   \
	RGB(MLC_BLEND(GetRValue(A), GetRValue(B), X), \
	MLC_BLEND(GetGValue(A), GetGValue(B), X),     \
	MLC_BLEND(GetBValue(A), GetBValue(B), X))     \
)
        if (socket->IsFull())
            ;
        else if (socket->IsTrickle())
            dc.SetTextColor(MLC_RGBBLEND(dc.GetTextColor(), dc.GetBkColor(), 2));
        // <== Design Settings [eWombat/Stulle] - Stulle
        //Xman this is used for testing purpose
        else
        {
            if(socket->isready)
                dc.SetTextColor(RGB(0,0,255));
            else
                dc.SetTextColor(RGB(0,128,128));

        }
    }
    //Xman this is used for testing purpose
    else
        dc.SetTextColor(RGB(255,0,0));
    //Xman end

    CHeaderCtrl *pHeaderCtrl = GetHeaderCtrl();
    int iCount = pHeaderCtrl->GetItemCount();
    cur_rec.right = cur_rec.left - sm_iLabelOffset;
    cur_rec.left += sm_iIconOffset;
    for (int iCurrent = 0; iCurrent < iCount; iCurrent++)
    {
        int iColumn = pHeaderCtrl->OrderToIndex(iCurrent);
        if (!IsColumnHidden(iColumn))
        {
            UINT uDrawTextAlignment;
            int iColumnWidth = GetColumnWidth(iColumn, uDrawTextAlignment);
            cur_rec.right += iColumnWidth;
            if (cur_rec.left < cur_rec.right && HaveIntersection(rcClient, cur_rec))
            {
                TCHAR szItem[1024];
                GetItemDisplayText(client, iColumn, szItem, _countof(szItem));
                switch (iColumn)
                {
                case 0: {
                    int iImage;
                    //Xman Show correct Icons
                    /*
                    if (client->IsFriend())
                    	iImage = 4;
                    else if (client->GetClientSoft() == SO_EDONKEYHYBRID) {
                    	if (client->credits->GetScoreRatio(client->GetIP()) > 1)
                    		iImage = 8;
                    	else
                    		iImage = 7;
                    }
                    else if (client->GetClientSoft() == SO_MLDONKEY) {
                    	if (client->credits->GetScoreRatio(client->GetIP()) > 1)
                    		iImage = 6;
                    	else
                    		iImage = 5;
                    }
                    else if (client->GetClientSoft() == SO_SHAREAZA) {
                    	if (client->credits->GetScoreRatio(client->GetIP()) > 1)
                    		iImage = 10;
                    	else
                    		iImage = 9;
                    }
                    else if (client->GetClientSoft() == SO_AMULE) {
                    	if (client->credits->GetScoreRatio(client->GetIP()) > 1)
                    		iImage = 12;
                    	else
                    		iImage = 11;
                    }
                    else if (client->GetClientSoft() == SO_LPHANT) {
                    	if (client->credits->GetScoreRatio(client->GetIP()) > 1)
                    		iImage = 14;
                    	else
                    		iImage = 13;
                    }
                    else if (client->ExtProtocolAvailable()) {
                    	if (client->credits->GetScoreRatio(client->GetIP()) > 1)
                    		iImage = 3;
                    	else
                    		iImage = 1;
                    }
                    else {
                    	if (client->credits->GetScoreRatio(client->GetIP()) > 1)
                    		iImage = 2;
                    	else
                    		iImage = 0;
                    }
                    */
                    if (client->IsFriend())
                        iImage = 6;
                    else if (client->GetClientSoft() == SO_EDONKEYHYBRID) {
                        iImage = 10;
                    }
                    else if (client->GetClientSoft() == SO_EDONKEY) {
                        iImage = 2;
                    }
                    else if (client->GetClientSoft() == SO_MLDONKEY) {
                        iImage = 8;
                    }
                    else if (client->GetClientSoft() == SO_SHAREAZA) {
                        iImage = 12;
                    }
                    else if (client->GetClientSoft() == SO_AMULE) {
                        iImage = 14;
                    }
                    else if (client->GetClientSoft() == SO_LPHANT) {
                        iImage = 16;
                    }
                    else if (client->ExtProtocolAvailable()) {
                        // ==> Mod Icons - Stulle
                        /*
                        iImage = 4;
                        */
                        if(client->GetModClient() == MOD_NONE)
                            iImage = 4;
                        else
                            iImage = (uint8)(client->GetModClient() + 19);
                        // <== Mod Icons - Stulle
                    }
                    else {
                        iImage = 0;
                    }
                    //Xman Anti-Leecher
                    if(client->IsLeecher()>0)
                        iImage=18;
                    else
                        //Xman end
                        // ==> Mod Icons - Stulle
                        // ==> CreditSystems [EastShare/ MorphXT] - Stulle
                        /*
                        if (((client->credits)?client->credits->GetScoreRatio(client):0) > 1)
                        	iImage++;
                        */
                        if (client->GetModClient() == MOD_NONE) {
                            if(client->credits && client->credits->GetHasScore(client))
                                iImage++;
                        }
                    // <== CreditSystems [EastShare/ MorphXT] - Stulle
                    // <== Mod Icons - Stulle
                    //Xman end

                    UINT nOverlayImage = 0;
                    if ((client->Credits() && client->Credits()->GetCurrentIdentState(client->GetIP()) == IS_IDENTIFIED))
                        nOverlayImage |= 1;
                    //Xman changed: display the obfuscation icon for all clients which enabled it
                    /*
                    if (client->IsObfuscatedConnectionEstablished())
                    */
                    if(client->IsObfuscatedConnectionEstablished()
                            || (!(client->socket != NULL && client->socket->IsConnected())
                                && (client->SupportsCryptLayer() && thePrefs.IsClientCryptLayerSupported() && (client->RequestsCryptLayer() || thePrefs.IsClientCryptLayerRequested()))))
                        //Xman end
                        nOverlayImage |= 2;
                    int iIconPosY = (cur_rec.Height() > 16) ? ((cur_rec.Height() - 16) / 2) : 1;
                    POINT point = { cur_rec.left, cur_rec.top + iIconPosY };

                    //Xman friend visualization
                    if (client->IsFriend() && client->GetFriendSlot())
                        m_ImageList.Draw(dc,19, point, ILD_NORMAL);
                    //Xman end

                    //EastShare Start - added by AndCycle, IP to Country
                    if(theApp.ip2country->ShowCountryFlag() )
                    {
                        cur_rec.left+=20;
                        POINT point2= {cur_rec.left,cur_rec.top+1};
                        //theApp.ip2country->GetFlagImageList()->Draw(dc, client->GetCountryFlagIndex(), point2, ILD_NORMAL);
                        theApp.ip2country->GetFlagImageList()->DrawIndirect(&theApp.ip2country->GetFlagImageDrawParams(dc,client->GetCountryFlagIndex(),point2));
                        cur_rec.left += sm_iLabelOffset;
                    }
                    //EastShare End - added by AndCycle, IP to Country

                    m_ImageList.Draw(dc, iImage, point, ILD_NORMAL | INDEXTOOVERLAYMASK(nOverlayImage));

                    // ==> Mod Icons - Stulle
                    if(client->Credits() && client->credits->GetHasScore(client) && client->GetModClient() != MOD_NONE)
                    {
                        if(nOverlayImage & 1)
                            m_overlayimages.Draw(dc,1, point, ILD_TRANSPARENT);
                        else
                            m_overlayimages.Draw(dc,0, point, ILD_TRANSPARENT);
                    }
                    // <== Mod Icons - Stulle

                    cur_rec.left += 16 + sm_iLabelOffset;
                    dc.DrawText(szItem, -1, &cur_rec, MLC_DT_TEXT | uDrawTextAlignment);
                    cur_rec.left -= 16;
                    cur_rec.right -= sm_iSubItemInset;

                    //EastShare Start - added by AndCycle, IP to Country
                    if(theApp.ip2country->ShowCountryFlag() )
                    {
                        cur_rec.left-=20;
                    }
                    //EastShare End - added by AndCycle, IP to Country

                    break;
                }

                case 7:
                {
                    cur_rec.bottom--;
                    cur_rec.top++;
                    COLORREF crOldBackColor = dc->GetBkColor(); //Xman Code Improvement: FillSolidRect
                    client->DrawUpStatusBar(dc, &cur_rec, false, thePrefs.UseFlatBar());
                    dc.SetBkColor(crOldBackColor); //Xman Code Improvement: FillSolidRect
                    //Xman client percentage (font idea by morph)
                    CString buffer;
                    // ==> Show Client Percentage optional [Stulle] - Stulle
                    /*
                    if (thePrefs.GetUseDwlPercentage())
                    */
                    if (thePrefs.GetShowClientPercentage())
                        // <== Show Client Percentage optional [Stulle] - Stulle
                    {
                        if(client->GetHisCompletedPartsPercent_UP() >=0)
                        {
                            COLORREF oldclr = dc.SetTextColor(RGB(0,0,0));
                            int iOMode = dc.SetBkMode(TRANSPARENT);
                            buffer.Format(_T("%i%%"), client->GetHisCompletedPartsPercent_UP());
                            CFont *pOldFont = dc.SelectObject(&m_fontBoldSmaller);
#define	DrawClientPercentText	dc.DrawText(buffer, buffer.GetLength(),&cur_rec, ((MLC_DT_TEXT | DT_RIGHT) & ~DT_LEFT) | DT_CENTER)
                            cur_rec.top-=1;
                            cur_rec.bottom-=1;
                            DrawClientPercentText;
                            cur_rec.left+=1;
                            cur_rec.right+=1;
                            DrawClientPercentText;
                            cur_rec.left+=1;
                            cur_rec.right+=1;
                            DrawClientPercentText;
                            cur_rec.top+=1;
                            cur_rec.bottom+=1;
                            DrawClientPercentText;
                            cur_rec.top+=1;
                            cur_rec.bottom+=1;
                            DrawClientPercentText;
                            cur_rec.left-=1;
                            cur_rec.right-=1;
                            DrawClientPercentText;
                            cur_rec.left-=1;
                            cur_rec.right-=1;
                            DrawClientPercentText;
                            cur_rec.top-=1;
                            cur_rec.bottom-=1;
                            DrawClientPercentText;
                            cur_rec.left++;
                            cur_rec.right++;
                            dc.SetTextColor(RGB(255,255,255));
                            DrawClientPercentText;
                            dc.SelectObject(pOldFont);
                            dc.SetBkMode(iOMode);
                            dc.SetTextColor(oldclr);
                        }
                    }
                    //Xman end

                    cur_rec.bottom++;
                    cur_rec.top--;
                    break;
                }

                // ==> Uploading Chunk Detail Display [SiRoB/Fafner] - Stulle
                case 10:
                {
                    cur_rec.bottom--;
                    cur_rec.top++;
                    client->DrawUpStatusBarChunk(dc,&cur_rec,false,thePrefs.UseFlatBar());
                    CFont *pOldFont = dc.SelectObject(&m_fontBoldSmaller);
                    client->DrawUpStatusBarChunkText(dc,&cur_rec);
                    dc.SelectObject(pOldFont);
                    cur_rec.bottom++;
                    cur_rec.top--;
                }
                break;
                // <== Uploading Chunk Detail Display [SiRoB/Fafner] - Stulle

                default:
                    // ==> Design Settings [eWombat/Stulle] - Stulle
                    /*
                    //Xman PowerRelease //Xman show LowIDs
                    if(iColumn == 1){
                    	const CKnownFile *file = theApp.sharedfiles->GetFileByID(client->GetUploadFileID());
                    	if(file && file->GetUpPriority()==PR_POWER)
                    		dc->SetBkColor(RGB(255,225,225));
                    }
                    else if(iColumn == 8 && client->HasLowID())
                    	dc->SetBkColor(RGB(255,250,200));
                    //Xman End
                    */
                    // <== Design Settings [eWombat/Stulle] - Stulle
                    dc.DrawText(szItem, -1, &cur_rec, MLC_DT_TEXT | uDrawTextAlignment);
                    // ==> Design Settings [eWombat/Stulle] - Stulle
                    /*
                    dc.SetBkColor(crOldBackColor); //Xman PowerRelease //Xman show LowIDs
                    */
                    // <== Design Settings [eWombat/Stulle] - Stulle
                    break;
                }
            }
            cur_rec.left += iColumnWidth;
        }
    }

    DrawFocusRect(dc, lpDrawItemStruct->rcItem, lpDrawItemStruct->itemState & ODS_FOCUS, bCtrlFocused, lpDrawItemStruct->itemState & ODS_SELECTED);
}
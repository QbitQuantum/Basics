//----CheckBox绘制函数----------------------------------------------------------
//功能：这是CheckBox控件的MSG_PAINT消息响应函数
//参数：pMsg，消息指针
//返回：固定true
//-----------------------------------------------------------------------------
static  bool_t CheckBox_Paint(struct WindowMsg *pMsg)
{
    HWND hwnd;
    HDC hdc;
    RECT rc;
    RECT rc0;

    hwnd=pMsg->hwnd;
    hdc =BeginPaint(hwnd);
    if(NULL!=hdc)
    {
        GetClientRect(hwnd,&rc0);

        SetTextColor(hdc,RGB(1,1,1));
        SetDrawColor(hdc,RGB(40,40,40));
        SetFillColor(hdc,RGB(200,200,200));

        FillRect(hdc,&rc0);

        if(hwnd->Style&CBS_SELECTED)
        {
            CopyRect(&rc,&rc0);
            rc.right =rc.left+RectH(&rc0);

            InflateRect(&rc,-2,-2);
            SetDrawColor(hdc,RGB(70,70,70));
            DrawRect(hdc,&rc);

            InflateRect(&rc,-1,-1);
            SetDrawColor(hdc,RGB(110,110,110));
            DrawRect(hdc,&rc);

            InflateRect(&rc,-1,-1);
            SetFillColor(hdc,RGB(240,240,240));
            FillRect(hdc,&rc);

            InflateRect(&rc,-4,-4);
            SetDrawColor(hdc,RGB(150,150,240));
            DrawRect(hdc,&rc);
            InflateRect(&rc,-1,-1);
            SetDrawColor(hdc,RGB(100,100,220));
            DrawRect(hdc,&rc);

            InflateRect(&rc,-1,-1);
            SetFillColor(hdc,RGB(50,50,200));
            FillRect(hdc,&rc);
        }
        else
        {
            CopyRect(&rc,&rc0);
            rc.right =rc.left+RectH(&rc0);

            InflateRect(&rc,-2,-2);
            SetDrawColor(hdc,RGB(100,100,100));
            DrawRect(hdc,&rc);

            InflateRect(&rc,-1,-1);
            SetDrawColor(hdc,RGB(160,160,160));
            DrawRect(hdc,&rc);

            InflateRect(&rc,-1,-1);
            SetFillColor(hdc,RGB(220,220,220));
            FillRect(hdc,&rc);

        }

        CopyRect(&rc,&rc0);
        InflateRectEx(&rc,-RectH(&rc),0,0,0);

        DrawText(hdc,hwnd->Text,-1,&rc,DT_LEFT|DT_VCENTER);
        EndPaint(hwnd,hdc);
    }

    return true;

}
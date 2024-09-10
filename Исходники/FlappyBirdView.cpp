void CFlappyBirdView::OnDraw(CDC* pDC)
{
    CFlappyBirdDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: 在此处为本机数据添加绘制代码
    pDC->TextOutW(200,0,L"通过w和s键控制小鸟的上下来躲避管道吧！");

    CBrush NewBrush;
    CBrush *pOldBrush;
    NewBrush.CreateSolidBrush(RGB(200,228,242));
    pOldBrush=pDC->SelectObject(&NewBrush);
    pDC->Rectangle(0,348,900,600);
    pDC->SelectObject(pOldBrush);

    CBrush NewBrush2;
    CBrush *pOldBrush2;
    NewBrush2.CreateSolidBrush(RGB(0,0,242));
    pOldBrush2=pDC->SelectObject(&NewBrush2);
    pDC->Rectangle(900,348,1000,600);
    pDC->SelectObject(pOldBrush2);


    pDoc->getBirdY(bird_y);
    CBitmap bm;
    bm.LoadBitmap(IDB_BIRD);
    CDC MemDC;
    MemDC.CreateCompatibleDC(pDC);
    MemDC.SelectObject(&bm);
    BITMAP info;
    bm.GetBitmap(&info);
    pDC->BitBlt(bird_x,bird_y,info.bmWidth, info.bmHeight,&MemDC,0,0,SRCCOPY);
    bm.DeleteObject();
    //
    CBitmap bm2;
    bm2.LoadBitmap(IDB_UP_STOP);
    CDC MemDC2;
    MemDC2.CreateCompatibleDC(pDC);
    MemDC2.SelectObject(&bm2);
    BITMAP info2;
    bm2.GetBitmap(&info2);
    pDC->BitBlt(up_stop1_x,0,info2.bmWidth, info2.bmHeight,&MemDC2,0,0,SRCCOPY);
    bm2.DeleteObject();
    //
    CBitmap bm3;
    bm3.LoadBitmap(IDB_DOWN_STOP);
    CDC MemDC3;
    MemDC3.CreateCompatibleDC(pDC);
    MemDC3.SelectObject(&bm3);
    BITMAP info3;
    bm3.GetBitmap(&info3);
    pDC->BitBlt(down_stop_x,248,info3.bmWidth, info3.bmHeight,&MemDC3,0,0,SRCCOPY);
    bm3.DeleteObject();
    ///============///
    if(!bird_die)
    {
        SetTimer(1,6,NULL);
        SetTimer(2,10,NULL);
        SetTimer(3,12,NULL);
    }
    else
    {
        pDC->TextOutW(200,200,L"You Lost!Try Again!");
        KillTimer(1);
        KillTimer(2);
        KillTimer(3);
        KillTimer(4);
        //pDC->BitBlt(bird_x,bird_y,info.bmWidth, info.bmHeight,&MemDC,0,0,SRCCOPY);
    }


}
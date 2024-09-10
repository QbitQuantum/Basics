void CDlgPointWin::OnPaint()
{
    // 字符串
    CString str;
    // 设备上下文
    CPaintDC dc ( this );
    // 获取绘制坐标的文本框
    CWnd* pWnd = GetDlgItem ( IDC_COORD );
    // 指针
    CDC* pDC = pWnd->GetDC();
    pWnd->Invalidate();
    pWnd->UpdateWindow();
    pDC->Rectangle ( 0, 0, 330, 300 );
    // 创建画笔对象
    CPen* pPenRed = new CPen;
    // 红色画笔
    pPenRed->CreatePen ( PS_SOLID, 2, RGB ( 255, 0,
                                            0 ) );
    // 创建画笔对象
    CPen* pPenBlue = new CPen;
    // 蓝色画笔
    pPenBlue->CreatePen ( PS_SOLID, 2, RGB ( 0, 0,
                          255 ) );
    // 创建画笔对象
    CPen* pPenGreen = new CPen;
    // 绿色画笔
    pPenGreen->CreatePen ( PS_DOT, 1, RGB ( 0, 255,
                                            0 ) );
    // 选中当前红色画笔，并保存以前的画笔
    CGdiObject* pOldPen = pDC->SelectObject (
                              pPenRed );
    // 绘制坐标轴
    pDC->MoveTo ( 10, 10 );
    // 垂直轴
    pDC->LineTo ( 10, 280 );
    // 水平轴
    pDC->LineTo ( 320, 280 );
    // 写坐标
    str.Format ( L"0" );
    pDC->TextOut ( 10, 281, str );
    str.Format ( L"255" );
    pDC->TextOut ( 265, 281, str );
    pDC->TextOut ( 11, 25, str );
    // 绘制X轴箭头
    pDC->LineTo ( 315, 275 );
    pDC->MoveTo ( 320, 280 );
    pDC->LineTo ( 315, 285 );
    // 绘制X轴箭头
    pDC->MoveTo ( 10, 10 );
    pDC->LineTo ( 5, 15 );
    pDC->MoveTo ( 10, 10 );
    pDC->LineTo ( 15, 15 );
    // 更改成绿色画笔
    pDC->SelectObject ( pPenGreen );
    // 绘制窗口上下限
    pDC->MoveTo ( m_bLow + 10, 25 );
    pDC->LineTo ( m_bLow + 10, 280 );
    pDC->MoveTo ( m_bUp + 10, 25 );
    pDC->LineTo ( m_bUp + 10, 280 );
    // 更改成蓝色画笔
    pDC->SelectObject ( pPenBlue );
    // 绘制坐标值
    str.Format ( L"(%d, %d)", m_bLow, m_bLow );
    pDC->TextOut ( m_bLow + 10, 281 - m_bLow, str );
    str.Format ( L"(%d, %d)", m_bUp, m_bUp );
    pDC->TextOut ( m_bUp + 10, 281 - m_bUp, str );
    // 绘制用户指定的窗口（注意转换坐标系）
    pDC->MoveTo ( 10, 280 );
    pDC->LineTo ( m_bLow + 10, 280 );
    pDC->LineTo ( m_bLow + 10, 280 - m_bLow );
    pDC->LineTo ( m_bUp + 10, 280 - m_bUp );
    pDC->LineTo ( m_bUp + 10, 25 );
    pDC->LineTo ( 265, 25 );
    // 恢复以前的画笔
    pDC->SelectObject ( pOldPen );
    // 绘制边缘
    pDC->MoveTo ( 10, 25 );
    pDC->LineTo ( 265, 25 );
    pDC->LineTo ( 265, 280 );
    // 删除新的画笔
    delete pPenRed;
    delete pPenBlue;
    delete pPenGreen;
}
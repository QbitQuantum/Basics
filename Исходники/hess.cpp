/* 画棋子 */
void Chess::DrawChess(CDC *pDC)
{
    CBrush *brush;
    COLORREF color;
    CPen pen;
    int a, b;

    a = x - SIZE / 2;
    b = y - SIZE / 2;

    /* 选择颜色 */
    if (this->color == WHITE)	/* 白色 */
    {
        color = RGB(255, 255, 255);
        pen.CreatePen(PS_SOLID, 1, color);
    }
    else	/* 黑色 */
    {
        color = RGB(0, 0, 0);
        pen.CreatePen(PS_SOLID, 1, color);
    }

    brush = new CBrush(color);	/* 笔的属性 */
    pDC->SelectObject(brush);			/* 使用这支笔 */
    pDC->SelectObject(&pen);
    pDC->Ellipse(a, b, a + size, b + size);	/* 画圆 */
    brush->DeleteObject();
    pen.DeleteObject();
}
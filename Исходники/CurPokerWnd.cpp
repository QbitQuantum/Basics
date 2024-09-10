// 移动鼠标（当鼠标在扑克牌上按下并移动时，XOR方式画一矩形，以示玩家选择扑克区域）
void CurPokerWnd::OnMouseMove(int x, int y)
{
    RECT rect;
    RECT rectRangeSel;

    if (m_bLButtonDown != TRUE) {
        return;
    }

    GetCardRangeSelectRect(&rectRangeSel);

    if (PtInRect(&rectRangeSel, m_ptLButtonDown)) {
        m_bLBtnDownAndMouseMove = TRUE;

        HDC hdc = GetDC(m_hWnd);
        HPEN hpen = CreatePen(PS_SOLID|PS_INSIDEFRAME, SEL_CARDS_FRAME_WIDTH, SEL_CARDS_FRAME_CLR);
        HBRUSH hbrush = (HBRUSH)GetStockObject(NULL_BRUSH);
        HPEN oldpen = (HPEN)SelectObject(hdc, hpen);
        HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, hbrush);
        int mode = SetROP2(hdc, R2_XORPEN);

        if (m_ptMouseMove.x != INVALID_COORD) {
            rect.left = max(0, min(m_ptMouseMove.x, m_ptLButtonDown.x));
            rect.right = max(m_ptMouseMove.x, m_ptLButtonDown.x);
            rect.top = max(0, min(m_ptMouseMove.y, m_ptLButtonDown.y));
            rect.bottom = max(m_ptMouseMove.y, m_ptLButtonDown.y);
            IntersectRect(&rect, &rect, &rectRangeSel);
            Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
        }

        m_ptMouseMove.x = max(0, x);
        m_ptMouseMove.y = max(0, y);

        rect.left = max(0, min(m_ptMouseMove.x, m_ptLButtonDown.x));
        rect.right = max(m_ptMouseMove.x, m_ptLButtonDown.x);
        rect.top = max(0, min(m_ptMouseMove.y, m_ptLButtonDown.y));
        rect.bottom = max(m_ptMouseMove.y, m_ptLButtonDown.y);
        IntersectRect(&rect, &rect, &rectRangeSel);
        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

        SetROP2(hdc, mode);
        SelectObject(hdc, oldbrush);
        SelectObject(hdc, oldpen);

        DeleteObject(hpen);

        ReleaseDC(m_hWnd, hdc);
    }
}
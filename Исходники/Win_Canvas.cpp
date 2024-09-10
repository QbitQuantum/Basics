    void GdiContext2D::Check()
    {
        //because GDI closes the path after Fill or stroke
        //we need a state to do both at the same time
        if (this->flags == 0)
        {
            //not using path
            return;
        }

        if (this->flags == 1)
        {
            COLORREF color = ColorToColorRef(strokeStyle.m_Color);
            HPEN hpen = CreatePen(PS_SOLID, (int)lineWidth, color); //TODO
            HPEN oldPen = (HPEN) SelectObject(m_hDC, hpen);
            StrokePath(m_hDC);
            SelectObject(m_hDC, oldPen);
            //
            DeleteObject(hpen);
        }
        else if (this->flags == 2)
        {
            COLORREF color = ColorToColorRef(fillStyle.m_Color);
            LOGBRUSH logbrush;
            logbrush.lbColor = color;
            logbrush.lbStyle = BS_SOLID;
            logbrush.lbHatch = 0;
            HBRUSH hBrush = CreateBrushIndirect(&logbrush);
            HBRUSH oldBrush = (HBRUSH)SelectObject(m_hDC, hBrush);
            //
            FillPath(m_hDC);
            //
            SelectObject(m_hDC, oldBrush);
            DeleteObject(hBrush);
        }
        else if (this->flags == 3)
        {
            COLORREF color2 = ColorToColorRef(strokeStyle.m_Color);
            HPEN hpen = CreatePen(PS_SOLID, (int) lineWidth, color2); //TODO
            HPEN oldPen = (HPEN) SelectObject(m_hDC, hpen);
            COLORREF color = ColorToColorRef(fillStyle.m_Color);
            LOGBRUSH logbrush;
            logbrush.lbColor = color;
            logbrush.lbStyle = BS_SOLID;
            logbrush.lbHatch = 0;
            HBRUSH hBrush = CreateBrushIndirect(&logbrush);
            HBRUSH oldBrush = (HBRUSH)SelectObject(m_hDC, hBrush);
            //
            StrokeAndFillPath(m_hDC);
            //
            SelectObject(m_hDC, oldPen);
            SelectObject(m_hDC, oldBrush);
            //
            DeleteObject(hBrush);
            DeleteObject(hpen);
        }

        this->flags = 0;
    }
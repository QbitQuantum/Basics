void CPDF_PathObject::CalcBoundingBox()
{
    if (m_Path.IsNull()) {
        return;
    }
    CFX_FloatRect rect;
    FX_FLOAT width = m_GraphState.GetObject()->m_LineWidth;
    if (m_bStroke && width != 0) {
        rect = m_Path.GetBoundingBox(width, m_GraphState.GetObject()->m_MiterLimit);
    } else {
        rect = m_Path.GetBoundingBox();
    }
    rect.Transform(&m_Matrix);
    if (width == 0 && m_bStroke) {
        rect.left += -0.5f;
        rect.right += 0.5f;
        rect.bottom += -0.5f;
        rect.top += 0.5f;
    }
    m_Left = rect.left;
    m_Right = rect.right;
    m_Top = rect.top;
    m_Bottom = rect.bottom;
}
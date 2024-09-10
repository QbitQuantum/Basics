static void CheckRotate(CPDF_Page& page, CFX_FloatRect& page_bbox)
{
    int total_count = 0, rotated_count[3] = {0, 0, 0};
    FX_POSITION pos = page.GetFirstObjectPosition();
    while (pos) {
        CPDF_PageObject* pObj = page.GetNextObject(pos);
        if (pObj->m_Type != PDFPAGE_TEXT) {
            continue;
        }
        total_count ++;
        CPDF_TextObject* pText = (CPDF_TextObject*)pObj;
        FX_FLOAT angle = pText->m_TextState.GetBaselineAngle();
        if (angle == 0.0) {
            continue;
        }
        int degree = (int)(angle * 180 / PI + 0.5);
        if (degree % 90) {
            continue;
        }
        if (degree < 0) {
            degree += 360;
        }
        int index = degree / 90 % 3 - 1;
        if (index < 0) {
            continue;
        }
        rotated_count[index] ++;
    }
    if (total_count == 0) {
        return;
    }
    CFX_AffineMatrix matrix;
    if (rotated_count[0] > total_count * 2 / 3) {
        matrix.Set(0, -1, 1, 0, 0, page.GetPageHeight());
    } else if (rotated_count[1] > total_count * 2 / 3) {
        matrix.Set(-1, 0, 0, -1, page.GetPageWidth(), page.GetPageHeight());
    } else if (rotated_count[2] > total_count * 2 / 3) {
        matrix.Set(0, 1, -1, 0, page.GetPageWidth(), 0);
    } else {
        return;
    }
    page.Transform(matrix);
    page_bbox.Transform(&matrix);
}
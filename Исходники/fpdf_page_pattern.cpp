CFX_FloatRect _GetShadingBBox(CPDF_Stream* pStream, int type, const CFX_AffineMatrix* pMatrix,
                              CPDF_Function** pFuncs, int nFuncs, CPDF_ColorSpace* pCS)
{
    if (pStream == NULL || pStream->GetType() != PDFOBJ_STREAM || pFuncs == NULL || pCS == NULL) {
        return CFX_FloatRect(0, 0, 0, 0);
    }
    CPDF_MeshStream stream;
    if (!stream.Load(pStream, pFuncs, nFuncs, pCS)) {
        return CFX_FloatRect(0, 0, 0, 0);
    }
    CFX_FloatRect rect;
    FX_BOOL bStarted = FALSE;
    FX_BOOL bGouraud = type == 4 || type == 5;
    int full_point_count = type == 7 ? 16 : (type == 6 ? 12 : 1);
    int full_color_count = (type == 6 || type == 7) ? 4 : 1;
    while (!stream.m_BitStream.IsEOF()) {
        FX_DWORD flag;
        if (type != 5) {
            flag = stream.GetFlag();
        }
        int point_count = full_point_count, color_count = full_color_count;
        if (!bGouraud && flag) {
            point_count -= 4;
            color_count -= 2;
        }
        for (int i = 0; i < point_count; i ++) {
            FX_FLOAT x, y;
            stream.GetCoords(x, y);
            if (bStarted) {
                rect.UpdateRect(x, y);
            } else {
                rect.InitRect(x, y);
                bStarted = TRUE;
            }
        }
        stream.m_BitStream.SkipBits(stream.m_nComps * stream.m_nCompBits * color_count);
        if (bGouraud) {
            stream.m_BitStream.ByteAlign();
        }
    }
    rect.Transform(pMatrix);
    return rect;
}
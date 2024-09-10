void CFX_PSRenderer::SetClip_PathStroke(const CFX_PathData* pPathData,
                                        const CFX_AffineMatrix* pObject2Device,
                                        const CFX_GraphStateData* pGraphState
                                       )
{
    StartRendering();
    SetGraphState(pGraphState);
    if (pObject2Device) {
        CFX_ByteTextBuf buf;
        buf << FX_BSTRC("mx Cm [") << pObject2Device->a << FX_BSTRC(" ") << pObject2Device->b << FX_BSTRC(" ") <<
            pObject2Device->c << FX_BSTRC(" ") << pObject2Device->d << FX_BSTRC(" ") << pObject2Device->e <<
            FX_BSTRC(" ") << pObject2Device->f << FX_BSTRC("]cm ");
        m_pOutput->OutputPS((FX_LPCSTR)buf.GetBuffer(), buf.GetSize());
    }
    OutputPath(pPathData, NULL);
    CFX_FloatRect rect = pPathData->GetBoundingBox(pGraphState->m_LineWidth, pGraphState->m_MiterLimit);
    rect.Transform(pObject2Device);
    m_ClipBox.Intersect(rect.GetOutterRect());
    if (pObject2Device) {
        OUTPUT_PS("strokepath W n sm\n");
    } else {
        OUTPUT_PS("strokepath W n\n");
    }
}
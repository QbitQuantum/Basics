void CanvasRenderingContext2D::setTransform(float m11, float m12, float m21, float m22, float dx, float dy)
{
    GraphicsContext* c = drawingContext();
    if (!c)
        return;
    
    // HTML5 3.14.11.1 -- ignore any calls that pass non-finite numbers
    if (!isfinite(m11) | !isfinite(m21) | !isfinite(dx) | 
        !isfinite(m12) | !isfinite(m22) | !isfinite(dy))
        return;

    TransformationMatrix ctm = state().m_transform;
    if (!ctm.isInvertible())
        return;
    c->concatCTM(c->getCTM().inverse());
    c->concatCTM(m_canvas->baseTransform());
    state().m_transform.multiply(ctm.inverse());
    m_path.transform(ctm);

    state().m_invertibleCTM = true;
    transform(m11, m12, m21, m22, dx, dy);
}
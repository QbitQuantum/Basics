void QAlphaPaintEngine::updateState(const QPaintEngineState &state)
{
    Q_D(QAlphaPaintEngine);

    DirtyFlags flags = state.state();
    if (flags & QPaintEngine::DirtyTransform) {
        d->m_transform = state.transform();
        d->m_complexTransform = (d->m_transform.type() > QTransform::TxScale);
        d->m_emulateProjectiveTransforms = !(d->m_savedcaps & QPaintEngine::PerspectiveTransform)
                                           && !(d->m_savedcaps & QPaintEngine::AlphaBlend)
                                           && (d->m_transform.type() >= QTransform::TxProject);
    }
    if (flags & QPaintEngine::DirtyPen) {
        d->m_pen = state.pen();
        if (d->m_pen.style() == Qt::NoPen) {
            d->m_advancedPen = false;
            d->m_alphaPen = false;
        } else {
            d->m_advancedPen = (d->m_pen.brush().style() != Qt::SolidPattern);
            d->m_alphaPen = !d->m_pen.brush().isOpaque();
        }
    }

    if (d->m_pass != 0) {
        d->m_continueCall = true;
        return;
    }
    d->m_continueCall = false;

    if (flags & QPaintEngine::DirtyOpacity) {
        d->m_alphaOpacity = (state.opacity() != 1.0f);
    }

    if (flags & QPaintEngine::DirtyBrush) {
        if (state.brush().style() == Qt::NoBrush) {
            d->m_advancedBrush = false;
            d->m_alphaBrush = false;
        } else {
            d->m_advancedBrush = (state.brush().style() != Qt::SolidPattern);
            d->m_alphaBrush = !state.brush().isOpaque();
        }
    }


    d->m_hasalpha = d->m_alphaOpacity || d->m_alphaBrush || d->m_alphaPen;

    if (d->m_picengine) {
        const QPainter *p = painter();
        d->m_picpainter->setPen(p->pen());
        d->m_picpainter->setBrush(p->brush());
        d->m_picpainter->setBrushOrigin(p->brushOrigin());
        d->m_picpainter->setFont(p->font());
        d->m_picpainter->setOpacity(p->opacity());
        d->m_picpainter->setTransform(p->combinedTransform());
        d->m_picengine->updateState(state);
    }
}
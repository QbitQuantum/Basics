void QEmulationPaintEngine::fill(const QVectorPath &path, const QBrush &brush)
{
    QPainterState *s = state();

    if (s->bgMode == Qt::OpaqueMode) {
        Qt::BrushStyle style = brush.style();
        if (style >= Qt::Dense1Pattern && style <= Qt::DiagCrossPattern)
            real_engine->fill(path, s->bgBrush);
    }

    Qt::BrushStyle style = qbrush_style(brush);
    if (style >= Qt::LinearGradientPattern && style <= Qt::ConicalGradientPattern) {
        const QGradient *g = brush.gradient();

        if (g->coordinateMode() > QGradient::LogicalMode) {
            if (g->coordinateMode() == QGradient::StretchToDeviceMode) {
                QBrush copy = brush;
                QTransform mat = copy.transform();
                mat.scale(real_engine->painter()->device()->width(), real_engine->painter()->device()->height());
                copy.setTransform(mat);
                real_engine->fill(path, copy);
                return;
            } else if (g->coordinateMode() == QGradient::ObjectBoundingMode) {
                QBrush copy = brush;
                QTransform mat = copy.transform();
                QRectF r = path.controlPointRect();
                mat.translate(r.x(), r.y());
                mat.scale(r.width(), r.height());
                copy.setTransform(mat);
                real_engine->fill(path, copy);
                return;
            }
        }
    }

    real_engine->fill(path, brush);
}
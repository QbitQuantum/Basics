void QTRenderer::DrawRectangle(const Pointf& point, const Sizef& size, const Color& outlineColor, float thickness) {
    QPen p(QColor(outlineColor.R(),outlineColor.G(),outlineColor.B(),outlineColor.A()));
         p.setWidth((int)thickness);
    painter->setPen(p);
    painter->drawRect(point.X(),point.Y(),size.W(),size.H());
}
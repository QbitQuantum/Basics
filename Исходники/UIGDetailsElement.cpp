void UIGDetailsElement::paintBackground(QPainter *pPainter, const QStyleOptionGraphicsItem *pOption)
{
    /* Save painter: */
    pPainter->save();

    /* Prepare variables: */
    int iMargin = data(ElementData_Margin).toInt();
    int iHeaderHeight = 2 * iMargin + m_iMinimumHeaderHeight;
    QRect optionRect = pOption->rect;
    QRect fullRect = !m_fAnimationRunning ? optionRect :
                     QRect(optionRect.topLeft(), QSize(optionRect.width(), iHeaderHeight + m_iAdditionalHeight));
    int iFullHeight = fullRect.height();

    /* Prepare color: */
    QPalette pal = palette();
    QColor headerColor = pal.color(QPalette::Active, QPalette::Button);
    QColor strokeColor = pal.color(QPalette::Active, QPalette::Mid);
    QColor bodyColor = pal.color(QPalette::Active, QPalette::Base);

    /* Add clipping: */
    QPainterPath path;
    path.moveTo(m_iCornerRadius, 0);
    path.arcTo(QRectF(path.currentPosition(), QSizeF(2 * m_iCornerRadius, 2 * m_iCornerRadius)).translated(-m_iCornerRadius, 0), 90, 90);
    path.lineTo(path.currentPosition().x(), iFullHeight - m_iCornerRadius);
    path.arcTo(QRectF(path.currentPosition(), QSizeF(2 * m_iCornerRadius, 2 * m_iCornerRadius)).translated(0, -m_iCornerRadius), 180, 90);
    path.lineTo(fullRect.width() - m_iCornerRadius, path.currentPosition().y());
    path.arcTo(QRectF(path.currentPosition(), QSizeF(2 * m_iCornerRadius, 2 * m_iCornerRadius)).translated(-m_iCornerRadius, -2 * m_iCornerRadius), 270, 90);
    path.lineTo(path.currentPosition().x(), m_iCornerRadius);
    path.arcTo(QRectF(path.currentPosition(), QSizeF(2 * m_iCornerRadius, 2 * m_iCornerRadius)).translated(-2 * m_iCornerRadius, -m_iCornerRadius), 0, 90);
    path.closeSubpath();
    pPainter->setClipPath(path);

    /* Calculate top rectangle: */
    QRect tRect = fullRect;
    tRect.setBottom(tRect.top() + iHeaderHeight);
    /* Calculate bottom rectangle: */
    QRect bRect = fullRect;
    bRect.setTop(tRect.bottom());

    /* Prepare top gradient: */
    QLinearGradient tGradient(tRect.bottomLeft(), tRect.topLeft());
    tGradient.setColorAt(0, headerColor.darker(110));
    tGradient.setColorAt(1, headerColor.darker(animationDarkness()));

    /* Paint all the stuff: */
    pPainter->fillRect(tRect, tGradient);
    pPainter->fillRect(bRect, bodyColor);

    /* Stroke path: */
    pPainter->setClipping(false);
    pPainter->strokePath(path, strokeColor);

    /* Restore painter: */
    pPainter->restore();
}
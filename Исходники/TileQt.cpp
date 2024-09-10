void Tile::paintCheckerPattern(GraphicsContext* context, const FloatRect& target)
{
    QPainter* painter = context->platformContext();
    QTransform worldTransform = painter->worldTransform();
    qreal scaleX = worldTransform.m11();
    qreal scaleY = worldTransform.m22();
    
    QRect targetViewRect = QRectF(target.x() * scaleX,
                                  target.y() * scaleY,
                                  target.width() * scaleX,
                                  target.height() * scaleY).toAlignedRect();
    
    QTransform adjustedTransform(1., worldTransform.m12(), worldTransform.m13(),
                  worldTransform.m21(), 1., worldTransform.m23(),
                  worldTransform.m31(), worldTransform.m32(), worldTransform.m33());
    painter->setWorldTransform(adjustedTransform);
    
    painter->drawTiledPixmap(targetViewRect,
                             checkeredPixmap(),
                             QPoint(targetViewRect.left() % checkerSize,
                                    targetViewRect.top() % checkerSize));
    
    painter->setWorldTransform(worldTransform);
}
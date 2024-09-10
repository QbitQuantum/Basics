void SceneGraphDeviceContext::DrawRectangle(int x, int y, int width, int height)
{
    vrv::Pen currentPen = m_penStack.top();

    QSGSimpleRectNode *node = new QSGSimpleRectNode;
    node->setColor(static_cast<QRgb>(currentPen.GetColour()));
    qreal rectX = static_cast<qreal>(translateX(x));
    qreal rectY = static_cast<qreal>(translateY(y));
    qreal rectWidth = static_cast<qreal>(translate(width));
    qreal rectHeight = static_cast<qreal>(translate(height));
    node->setRect(rectX, rectY, rectWidth, rectHeight);
    AddGeometryNode(node);
}
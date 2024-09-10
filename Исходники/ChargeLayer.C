void Charge::drawLabel(QGLViewer& viewer, QFontMetrics& fontMetrics) 
{
   Vec pos(getPosition());
   Vec shift = viewer.camera()->position() - pos;
   shift.normalize();

   pos = pos + 1.05 * shift * getRadius(true);
   pos = viewer.camera()->projectedCoordinatesOf(pos);
   pos.x -= fontMetrics.width(m_label)/2;
   pos = viewer.camera()->unprojectedCoordinatesOf(pos);
   viewer.renderText(pos[0], pos[1], pos[2], m_label);
}
void Atom::drawLabel(Viewer& viewer, LabelType const type, QFontMetrics& fontMetrics) 
{
   Vec pos(getPosition());
   Vec shift = viewer.camera()->position() - pos;
   shift.normalize();
   QString label(getLabel(type));

   pos = pos + 1.05 * shift * getRadius(true);
   pos = viewer.camera()->projectedCoordinatesOf(pos);
   pos.x -= fontMetrics.width(label)/2.0;
   pos.y += fontMetrics.height()/4.0;
   pos = viewer.camera()->unprojectedCoordinatesOf(pos);

   glColor3f(0.1, 0.1, 0.1);
   viewer.renderText(pos[0], pos[1], pos[2], label, viewer.labelFont());
}
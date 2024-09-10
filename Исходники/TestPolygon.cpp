END_TEST

START_TEST ( test_Polygon_read_old_style )
{
  std::string s = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                  "<polygon xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
                  "  <listOfCurveSegments>\n"
                  "    <curveSegment xsi:type=\"LineSegment\">\n"
                  "      <start x=\"0\" y=\"0\" />\n"
                  "      <end x=\"10\" y=\"3\" />\n"
                  "    </curveSegment>\n"
                  "    <curveSegment xsi:type=\"LineSegment\">\n"
                  "      <start x=\"10\" y=\"3\" />\n"
                  "      <end x=\"0\" y=\"6\" />\n"
                  "    </curveSegment>\n"
                  "  </listOfCurveSegments>\n"
                  "</polygon>\n"
                ;
      
  XMLInputStream* pStream= new XMLInputStream(s.c_str(),false);
  XMLNode* pNode = new XMLNode(*pStream);

  Polygon c = Polygon(*pNode);
  fail_unless(!c.isSetMatrix());
  fail_unless(!c.isSetStroke());
  fail_unless(!c.isSetStrokeWidth());
  fail_unless(!c.isSetDashArray());
  fail_unless(!c.isSetFillColor());
  fail_unless(!c.isSetFillRule());
  fail_unless(c.getNumElements() == 3);
  const RenderPoint* pP=c.getElement(0);
  fail_unless( pP != NULL );
  if (pP == NULL) return;
  fail_unless( pP->getTypeCode() == SBML_RENDER_POINT );
  fail_unless( dynamic_cast<const RenderCubicBezier*>(pP) == NULL);
  fail_unless( pP->x().getAbsoluteValue() < 1e-9);
  fail_unless( pP->x().getRelativeValue() < 1e-9);
  fail_unless( pP->y().getAbsoluteValue() < 1e-9);
  fail_unless( pP->y().getRelativeValue() < 1e-9);
  fail_unless( pP->z().getAbsoluteValue() < 1e-9);
  fail_unless( pP->z().getRelativeValue() < 1e-9);
  pP=c.getElement(1);
  fail_unless( pP != NULL );
  fail_unless( pP->getTypeCode() == SBML_RENDER_POINT );
  fail_unless( dynamic_cast<const RenderCubicBezier*>(pP) == NULL);
  fail_unless( fabs((pP->x().getAbsoluteValue() - 10.0 ) / 10.0) < 1e-9);
  fail_unless( pP->x().getRelativeValue() < 1e-9);
  fail_unless( fabs((pP->y().getAbsoluteValue() - 3.0) / 3.0) < 1e-9);
  fail_unless( pP->y().getRelativeValue() < 1e-9);
  fail_unless( pP->z().getAbsoluteValue() < 1e-9);
  fail_unless( pP->z().getRelativeValue() < 1e-9);
  pP=c.getElement(2);
  fail_unless( pP != NULL );
  fail_unless( pP->getTypeCode() == SBML_RENDER_POINT );
  fail_unless( dynamic_cast<const RenderCubicBezier*>(pP) == NULL);
  fail_unless( pP->x().getAbsoluteValue() < 1e-9);
  fail_unless( pP->x().getRelativeValue() < 1e-9);
  fail_unless( fabs((pP->y().getAbsoluteValue() - 6.0) / 6.0) < 1e-9);
  fail_unless( pP->y().getRelativeValue() < 1e-9);
  fail_unless( pP->z().getAbsoluteValue() < 1e-9);
  fail_unless( pP->z().getRelativeValue() < 1e-9);
  delete pNode;
  delete pStream;
      
      
  s = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      "<polygon xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\">\n"
      "  <listOfCurveSegments>\n"
      "    <curveSegment xsi:type=\"CubicBezier\">\n"
      "      <start x=\"2.0\" y=\"7.71428\"/>\n"
      "      <basePoint1 x=\"10.21428\" y=\"12.0\"/>\n"
      "      <basePoint2 x=\"15.21428\" y=\"17.04464\"/>\n"
      "      <end x=\"24.05357\" y=\"15.83928\"/>\n"
      "    </curveSegment>\n"
      "    <curveSegment xsi:type=\"CubicBezier\">\n"
      "      <start x=\"24.05357\" y=\"15.83928\"/>\n"
      "      <basePoint1 x=\"32.89285\" y=\"14.63392\"/>\n"
      "      <basePoint2 x=\"45.57142\" y=\"7.17856\"/>\n"
      "      <end x=\"45.57142\" y=\"7.17856\"/>\n"
      "    </curveSegment>\n"
      "    <curveSegment xsi:type=\"LineSegment\">\n"
      "      <start x=\"45.57142\" y=\"7.17856\"/>\n"
      "      <end x=\"41.46427\" y=\"2.0\"/>\n"
      "    </curveSegment>\n"
      "    <curveSegment xsi:type=\"CubicBezier\">\n"
      "      <start x=\"41.46427\" y=\"2.0\"/>\n"
      "      <basePoint1 x=\"41.46427\" y=\"2.0\"/>\n"
      "      <basePoint2 x=\"31.9107\" y=\"9.14285\"/>\n"
      "      <end x=\"23.42856\" y=\"9.32142\"/>\n"
      "    </curveSegment>\n"
      "    <curveSegment xsi:type=\"CubicBezier\">\n"
      "      <start x=\"23.42856\" y=\"9.32142\"/>\n"
      "      <basePoint1 x=\"14.94642\" y=\"9.49999\"/>\n"
      "      <basePoint2 x=\"7.5357\" y=\"2.71428\"/>\n"
      "      <end x=\"7.5357\" y=\"2.71428\"/>\n"
      "    </curveSegment>\n"
      "    <curveSegment xsi:type=\"LineSegment\">\n"
      "      <start x=\"7.5357\" y=\"2.71428\"/>\n"
      "      <end x=\"2.0\" y=\"7.71428\"/>\n"
      "    </curveSegment>\n"
      "  </listOfCurveSegments>\n"
      "</polygon>\n"
    ;

  pStream= new XMLInputStream(s.c_str(),false);
  pNode = new XMLNode(*pStream);
  
  c = Polygon(*pNode);
  fail_unless(!c.isSetMatrix());
  fail_unless(!c.isSetStroke());
  fail_unless(!c.isSetStrokeWidth());
  fail_unless(!c.isSetDashArray());
  fail_unless(!c.isSetFillColor());
  fail_unless(!c.isSetFillRule());
  fail_unless(c.getNumElements() == 7);
  pP=c.getElement(0);
  fail_unless( pP != NULL );
  fail_unless( pP->getTypeCode() == SBML_RENDER_POINT );
  fail_unless( dynamic_cast<const RenderCubicBezier*>(pP) == NULL);
  fail_unless( fabs((pP->x().getAbsoluteValue() - 2.0) / 2.0) < 1e-9);
  fail_unless( pP->x().getRelativeValue() < 1e-9);
  fail_unless( fabs((pP->y().getAbsoluteValue() - 7.71428) / 7.71428) < 1e-9);
  fail_unless( pP->y().getRelativeValue() < 1e-9);
  fail_unless( pP->z().getAbsoluteValue() < 1e-9);
  fail_unless( pP->z().getRelativeValue() < 1e-9);
  pP=c.getElement(1);
  fail_unless( pP != NULL );
  fail_unless( pP->getTypeCode() == SBML_RENDER_POINT );
  fail_unless( dynamic_cast<const RenderCubicBezier*>(pP) == NULL);
  fail_unless( fabs((pP->x().getAbsoluteValue() - 24.05357) / 24.05357) < 1e-9);
  fail_unless( pP->x().getRelativeValue() < 1e-9);
  fail_unless( fabs((pP->y().getAbsoluteValue() - 15.83928) / 15.83928) < 1e-9);
  fail_unless( pP->y().getRelativeValue() < 1e-9);
  fail_unless( pP->z().getAbsoluteValue() < 1e-9);
  fail_unless( pP->z().getRelativeValue() < 1e-9);
  pP=c.getElement(2);
  fail_unless( pP != NULL );
  fail_unless( pP->getTypeCode() == SBML_RENDER_POINT );
  fail_unless( dynamic_cast<const RenderCubicBezier*>(pP) == NULL);
  fail_unless( fabs((pP->x().getAbsoluteValue() - 45.57142) / 45.57142) < 1e-9);
  fail_unless( pP->x().getRelativeValue() < 1e-9);
  fail_unless( fabs((pP->y().getAbsoluteValue() - 7.17856) / 7.17856) < 1e-9);
  fail_unless( pP->y().getRelativeValue() < 1e-9);
  fail_unless( pP->z().getAbsoluteValue() < 1e-9);
  fail_unless( pP->z().getRelativeValue() < 1e-9);
  pP=c.getElement(3);
  fail_unless( pP != NULL );
  fail_unless( pP->getTypeCode() == SBML_RENDER_POINT );
  fail_unless( dynamic_cast<const RenderCubicBezier*>(pP) == NULL);
  fail_unless( fabs((pP->x().getAbsoluteValue() - 41.46427) / 41.46427) < 1e-9);
  fail_unless( pP->x().getRelativeValue() < 1e-9);
  fail_unless( fabs((pP->y().getAbsoluteValue() - 2.0) / 2.0) < 1e-9);
  fail_unless( pP->y().getRelativeValue() < 1e-9);
  fail_unless( pP->z().getAbsoluteValue() < 1e-9);
  fail_unless( pP->z().getRelativeValue() < 1e-9);
  pP=c.getElement(4);
  fail_unless( pP != NULL );
  fail_unless( pP->getTypeCode() == SBML_RENDER_POINT );
  fail_unless( dynamic_cast<const RenderCubicBezier*>(pP) == NULL);
  fail_unless( fabs((pP->x().getAbsoluteValue() - 23.42856) / 23.42856) < 1e-9);
  fail_unless( pP->x().getRelativeValue() < 1e-9);
  fail_unless( fabs((pP->y().getAbsoluteValue() - 9.32142) / 9.32142) < 1e-9);
  fail_unless( pP->y().getRelativeValue() < 1e-9);
  fail_unless( pP->z().getAbsoluteValue() < 1e-9);
  fail_unless( pP->z().getRelativeValue() < 1e-9);
  pP=c.getElement(5);
  fail_unless( pP != NULL );
  fail_unless( pP->getTypeCode() == SBML_RENDER_POINT );
  fail_unless( dynamic_cast<const RenderCubicBezier*>(pP) == NULL);
  fail_unless( fabs((pP->x().getAbsoluteValue() - 7.5357) / 7.5357) < 1e-9);
  fail_unless( pP->x().getRelativeValue() < 1e-9);
  fail_unless( fabs((pP->y().getAbsoluteValue() - 2.71428) / 2.71428) < 1e-9);
  fail_unless( pP->y().getRelativeValue() < 1e-9);
  fail_unless( pP->z().getAbsoluteValue() < 1e-9);
  fail_unless( pP->z().getRelativeValue() < 1e-9);
  pP=c.getElement(6);
  fail_unless( pP != NULL );
  fail_unless( pP->getTypeCode() == SBML_RENDER_POINT );
  fail_unless( dynamic_cast<const RenderCubicBezier*>(pP) == NULL);
  fail_unless( fabs((pP->x().getAbsoluteValue() - 2.0) / 2.0) < 1e-9);
  fail_unless( pP->x().getRelativeValue() < 1e-9);
  fail_unless( fabs((pP->y().getAbsoluteValue() - 7.71428) / 7.71428) < 1e-9);
  fail_unless( pP->y().getRelativeValue() < 1e-9);
  fail_unless( pP->z().getAbsoluteValue() < 1e-9);
  fail_unless( pP->z().getRelativeValue() < 1e-9);
  delete pNode;
  delete pStream;
} 
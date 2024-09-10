void VectorFont::Glyph::GlyphArc::glCommands(
	const gp_Pnt & starting_point,
	const bool select,
	const bool marked,
	const bool no_color,
	COrientationModifier *pOrientationModifier,
	gp_Trsf transformation,
	const float width) const
{
	glBegin(GL_LINE_STRIP);
	std::list<gp_Pnt> vertices = Interpolate( starting_point, 20 );
	for (std::list<gp_Pnt>::iterator l_itVertex = vertices.begin(); l_itVertex != vertices.end(); l_itVertex++)
	{
		if (pOrientationModifier) *l_itVertex = pOrientationModifier->Transform(transformation, starting_point.Distance(gp_Pnt(0.0,0.0,0.0)), *l_itVertex, width );
		glVertex3d(l_itVertex->X(), l_itVertex->Y(), l_itVertex->Z());
	} // End for
	glEnd();
} // End glCommands() method
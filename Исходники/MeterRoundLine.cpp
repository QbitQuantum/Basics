/*
** Draws the meter on the double buffer
**
*/
bool CMeterRoundLine::Draw(Graphics& graphics)
{
	if (!CMeter::Draw(graphics)) return false;

	// Calculate the center of for the line
	int x = GetX();
	int y = GetY();
	double cx = x + m_W / 2.0;
	double cy = y + m_H / 2.0;

	double lineStart = ((m_CntrlLineStart) ? m_LineStartShift * m_Value : 0) + m_LineStart;
	double lineLength = ((m_CntrlLineLength) ? m_LineLengthShift * m_Value : 0) + m_LineLength;

	// Calculate the end point of the line
	double angle = ((m_CntrlAngle) ? m_RotationAngle * m_Value : m_RotationAngle) + m_StartAngle;
	double e_cos = cos(angle);
	double e_sin = sin(angle);

	REAL sx = (REAL)(e_cos * lineStart + cx);
	REAL sy = (REAL)(e_sin * lineStart + cy);
	REAL ex = (REAL)(e_cos * lineLength + cx);
	REAL ey = (REAL)(e_sin * lineLength + cy);

	if (m_Solid)
	{
		REAL startAngle = (REAL)(CONVERT_TO_DEGREES(m_StartAngle));
		REAL sweepAngle = (REAL)(CONVERT_TO_DEGREES(m_RotationAngle * m_Value));

		// Calculate the start point of the line
		double s_cos = cos(m_StartAngle);
		double s_sin = sin(m_StartAngle);

		//Create a path to surround the arc
		GraphicsPath path;
		path.AddArc((REAL)(cx - lineStart), (REAL)(cy - lineStart), (REAL)(lineStart * 2.0), (REAL)(lineStart * 2.0), startAngle, sweepAngle);
		path.AddLine((REAL)(lineStart * s_cos + cx), (REAL)(lineStart * s_sin + cy), (REAL)(lineLength * s_cos + cx), (REAL)(lineLength * s_sin + cy));
		path.AddArc((REAL)(cx - lineLength), (REAL)(cy - lineLength), (REAL)(lineLength * 2.0), (REAL)(lineLength * 2.0), startAngle, sweepAngle);
		path.AddLine(ex, ey, sx, sy);

		SolidBrush solidBrush(m_LineColor);
		graphics.FillPath(&solidBrush, &path);
	}
	else
	{
		Pen pen(m_LineColor, (REAL)m_LineWidth);
		graphics.DrawLine(&pen, sx, sy, ex, ey);
	}

	return true;
}
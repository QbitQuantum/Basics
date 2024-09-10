/**--------------------------------------------------------------------------<BR>
C2DLine::Reflect
\brief Point reflection.
<P>---------------------------------------------------------------------------*/
void C2DLine::Reflect(const C2DPoint& Point)
{
	C2DPoint pointTo = GetPointTo();
	point.Reflect(Point);
	pointTo.Reflect(Point);
	SetPointTo(pointTo);

}
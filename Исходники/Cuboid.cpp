void cCuboid::ClampX(int a_MinX, int a_MaxX)
{
	p1.x = Clamp(p1.x, a_MinX, a_MaxX);
	p2.x = Clamp(p2.x, a_MinX, a_MaxX);
}
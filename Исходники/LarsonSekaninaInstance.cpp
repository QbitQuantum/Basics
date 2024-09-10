inline static
void ToCartesian( double r, double theta, DPoint center, DPoint& p )
{
   p.x = center.x + r*Cos( theta );
   p.y = center.y + r*Sin( theta );
}
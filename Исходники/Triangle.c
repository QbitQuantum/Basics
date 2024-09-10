static void FillRightOrientedTriangle (HDC hDc)
{
	long y          = points [LOW_POINT].y;

	long leftEdge   = points [LOW_POINT].x;
	long rightEdge  = points [LOW_POINT].x;

	long leftDx     = longEdge->dx;
	long leftDy     = longEdge->dy;
	long rightDx;
	long rightDy;

	long leftConst  = Floor (longEdge->dx, longEdge->dy);
	long rightConst;

	long leftMod    = Mod (longEdge->dx, longEdge->dy);
	long rightMod;

	long leftNumer  = -1;
	long rightNumer = -1;

	rightConst = Floor (lowEdge->dx, lowEdge->dy);
	rightDx    = lowEdge->dx;
	rightDy    = lowEdge->dy;
	rightMod   = Mod (rightDx, rightDy);

	while (lowEdge->dy--)
	{
		WriteRow (hDc, leftEdge, rightEdge, y++);

		leftEdge    += leftConst  + Floor (Mod (leftNumer,  leftDy)  + leftMod,  leftDy);
		rightEdge   += rightConst + Floor (Mod (rightNumer, rightDy) + rightMod, rightDy);
		
		leftNumer   += leftDx;
		rightNumer	+= rightDx;
	}

	rightConst = Floor (topEdge->dx, topEdge->dy);
	rightDx    = topEdge->dx;
	rightDy    = topEdge->dy;
	rightMod   = Mod (rightDx, rightDy);

	while (topEdge->dy--)
	{
		WriteRow (hDc, leftEdge, rightEdge, y++);

		leftEdge    += leftConst  + Floor (Mod (leftNumer,  leftDy)  + leftMod,  leftDy);
		rightEdge   += rightConst + Floor (Mod (rightNumer, rightDy) + rightMod, rightDy);  

		leftNumer   += leftDx;
		rightNumer	+= rightDx;

	}
}
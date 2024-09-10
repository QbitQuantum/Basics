void	MotionHandler(int x, int y)
// Handles mouse motion.
{
	float	dx = x - LastMouseX;
	float	dy = y - LastMouseY;
	LastMouseX = x;
	LastMouseY = y;
	
	if (LeftButton && RightButton) {
		// Translate in the view plane.
		vector	right = ViewerDir.cross(ViewerUp);
		ViewerLoc += right * dx / 3 * Speed + ViewerUp * -dy / 3 * Speed;
		
	} else if (LeftButton) {
		// Rotate the viewer.
		ViewerTheta += -dx / 100;
		while (ViewerTheta < 0) ViewerTheta += 2 * PI;
		while (ViewerTheta >= 2 * PI) ViewerTheta -= 2 * PI;

		ViewerPhi += -dy / 100;
		const float	plimit = PI / 2;
		if (ViewerPhi > plimit) ViewerPhi = plimit;
		if (ViewerPhi < -plimit) ViewerPhi = -plimit;

		ViewerDir = vector(1, 0, 0);
		ViewerUp = vector(0, 1, 0);
		
		ViewerDir = Geometry::Rotate(ViewerTheta, ViewerUp, ViewerDir);
		vector	right = ViewerDir.cross(ViewerUp);
		ViewerDir = Geometry::Rotate(ViewerPhi, right, ViewerDir);
		ViewerUp = Geometry::Rotate(ViewerPhi, right, ViewerUp);
		
	} else if (RightButton) {
		// Translate the viewer.
		vector	right = ViewerDir.cross(ViewerUp);
		ViewerLoc += right * dx / 3 * Speed + ViewerDir * -dy / 3 * Speed;
	}
}
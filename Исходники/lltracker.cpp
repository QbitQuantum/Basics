void LLTracker::drawMarker(const LLVector3d& pos_global, const LLColor4& color)
{
	// get position
	LLVector3 pos_local = gAgent.getPosAgentFromGlobal(pos_global);

	// check in frustum
	LLCoordGL screen;
	S32 x = 0;
	S32 y = 0;
	const BOOL CLAMP = TRUE;

	if (LLViewerCamera::getInstance()->projectPosAgentToScreen(pos_local, screen, CLAMP)
		|| LLViewerCamera::getInstance()->projectPosAgentToScreenEdge(pos_local, screen) )
	{
		gHUDView->screenPointToLocal(screen.mX, screen.mY, &x, &y);

		// the center of the rendered position of the arrow obeys 
		// the following rules:
		// (1) it lies on an ellipse centered on the target position 
		// (2) it lies on the line between the target and the window center
		// (3) right now the radii of the ellipse are fixed, but eventually
		//     they will be a function of the target text
		// 
		// from those rules we can compute the position of the 
		// lower left corner of the image
		LLRect rect = gHUDView->getRect();
		S32 x_center = lltrunc(0.5f * (F32)rect.getWidth());
		S32 y_center = lltrunc(0.5f * (F32)rect.getHeight());
		x = x - x_center;	// x and y relative to center
		y = y - y_center;
		F32 dist = sqrt((F32)(x*x + y*y));
		S32 half_arrow_size = lltrunc(0.5f * HUD_ARROW_SIZE);
		if (dist > 0.f)
		{
			const F32 ARROW_ELLIPSE_RADIUS_X = 2 * HUD_ARROW_SIZE;
			const F32 ARROW_ELLIPSE_RADIUS_Y = HUD_ARROW_SIZE;

			// compute where the arrow should be
			F32 x_target = (F32)(x + x_center) - (ARROW_ELLIPSE_RADIUS_X * ((F32)x / dist) );	
			F32 y_target = (F32)(y + y_center) - (ARROW_ELLIPSE_RADIUS_Y * ((F32)y / dist) );

			// keep the arrow within the window
			F32 x_clamped = llclamp( x_target, (F32)half_arrow_size, (F32)(rect.getWidth() - half_arrow_size));
			F32 y_clamped = llclamp( y_target, (F32)half_arrow_size, (F32)(rect.getHeight() - half_arrow_size));

			F32 slope = (F32)(y) / (F32)(x);
			F32 window_ratio = (F32)(rect.getHeight() - HUD_ARROW_SIZE) / (F32)(rect.getWidth() - HUD_ARROW_SIZE);

			// if the arrow has been clamped on one axis
			// then we need to compute the other axis
			if (llabs(slope) > window_ratio)
			{  
				if (y_clamped != (F32)y_target)
				{
					// clamp by y 
					x_clamped = (y_clamped - (F32)y_center) / slope + (F32)x_center;
				}
			}
			else if (x_clamped != (F32)x_target)
			{
				// clamp by x
				y_clamped = (x_clamped - (F32)x_center) * slope + (F32)y_center;
			}
			mHUDArrowCenterX = lltrunc(x_clamped);
			mHUDArrowCenterY = lltrunc(y_clamped);
		}
		else
		{
			// recycle the old values
			x = mHUDArrowCenterX - x_center;
			y = mHUDArrowCenterY - y_center;
		}

		F32 angle = atan2( (F32)y, (F32)x );

		gl_draw_scaled_rotated_image(mHUDArrowCenterX - half_arrow_size, 
									 mHUDArrowCenterY - half_arrow_size, 
									 HUD_ARROW_SIZE, HUD_ARROW_SIZE, 
									 RAD_TO_DEG * angle, 
									 LLWorldMapView::sTrackArrowImage->getImage(), 
									 color);
	}
}
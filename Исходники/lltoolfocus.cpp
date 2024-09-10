BOOL LLToolCamera::handleHover(S32 x, S32 y, MASK mask)
{
	S32 dx = gViewerWindow->getCurrentMouseDX();
	S32 dy = gViewerWindow->getCurrentMouseDY();
	
	BOOL moved_outside_slop = FALSE;
	
	if (hasMouseCapture() && mValidClickPoint)
	{
		mAccumX += llabs(dx);
		mAccumY += llabs(dy);

		if (mAccumX >= SLOP_RANGE)
		{
			if (!mOutsideSlopX)
			{
				moved_outside_slop = TRUE;
			}
			mOutsideSlopX = TRUE;
		}

		if (mAccumY >= SLOP_RANGE)
		{
			if (!mOutsideSlopY)
			{
				moved_outside_slop = TRUE;
			}
			mOutsideSlopY = TRUE;
		}
	}

	if (mOutsideSlopX || mOutsideSlopY)
	{
		if (!mValidClickPoint)
		{
			lldebugst(LLERR_USER_INPUT) << "hover handled by LLToolFocus [invalid point]" << llendl;
			gViewerWindow->setCursor(UI_CURSOR_NO);
			gViewerWindow->showCursor();
			return TRUE;
		}

		if (gCameraBtnOrbit ||
			mask == MASK_ORBIT || 
			mask == (MASK_ALT | MASK_ORBIT))
		{
			// Orbit tool
			if (hasMouseCapture())
			{
				const F32 RADIANS_PER_PIXEL = 360.f * DEG_TO_RAD / gViewerWindow->getWorldViewWidthScaled();

				if (dx != 0)
				{
					gAgentCamera.cameraOrbitAround( -dx * RADIANS_PER_PIXEL );
				}

				if (dy != 0)
				{
					gAgentCamera.cameraOrbitOver( -dy * RADIANS_PER_PIXEL );
				}

				gViewerWindow->moveCursorToCenter();
			}
			lldebugst(LLERR_USER_INPUT) << "hover handled by LLToolFocus [active]" << llendl;
		}
		else if (	gCameraBtnPan ||
					mask == MASK_PAN ||
					mask == (MASK_PAN | MASK_ALT) )
		{
			// Pan tool
			if (hasMouseCapture())
			{
				LLVector3d camera_to_focus = gAgentCamera.getCameraPositionGlobal();
				camera_to_focus -= gAgentCamera.getFocusGlobal();
				F32 dist = (F32) camera_to_focus.normVec();

				// Fudge factor for pan
				F32 meters_per_pixel = 3.f * dist / gViewerWindow->getWorldViewWidthScaled();

				if (dx != 0)
				{
					gAgentCamera.cameraPanLeft( dx * meters_per_pixel );
				}

				if (dy != 0)
				{
					gAgentCamera.cameraPanUp( -dy * meters_per_pixel );
				}

				gViewerWindow->moveCursorToCenter();
			}
			lldebugst(LLERR_USER_INPUT) << "hover handled by LLToolPan" << llendl;
		}
		else if (gCameraBtnZoom)
		{
			// Zoom tool
			if (hasMouseCapture())
			{

				const F32 RADIANS_PER_PIXEL = 360.f * DEG_TO_RAD / gViewerWindow->getWorldViewWidthScaled();

				if (dx != 0)
				{
					gAgentCamera.cameraOrbitAround( -dx * RADIANS_PER_PIXEL );
				}

				const F32 IN_FACTOR = 0.99f;

				if (dy != 0 && mOutsideSlopY )
				{
					if (mMouseSteering)
					{
						gAgentCamera.cameraOrbitOver( -dy * RADIANS_PER_PIXEL );
					}
					else
					{
						gAgentCamera.cameraZoomIn( pow( IN_FACTOR, dy ) );
					}
				}

				gViewerWindow->moveCursorToCenter();
			}

			lldebugst(LLERR_USER_INPUT) << "hover handled by LLToolZoom" << llendl;		
		}
	}

	if (gCameraBtnOrbit ||
		mask == MASK_ORBIT || 
		mask == (MASK_ALT | MASK_ORBIT))
	{
		gViewerWindow->setCursor(UI_CURSOR_TOOLCAMERA);
	}
	else if (	gCameraBtnPan ||
				mask == MASK_PAN ||
				mask == (MASK_PAN | MASK_ALT) )
	{
		gViewerWindow->setCursor(UI_CURSOR_TOOLPAN);
	}
	else
	{
		gViewerWindow->setCursor(UI_CURSOR_TOOLZOOMIN);
	}
	
	return TRUE;
}
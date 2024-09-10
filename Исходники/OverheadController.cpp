void COverheadController::MouseWheelMove(float move)
{
	if (move == 0.0f)
		return;

	camHandler->CameraTransition(0.05f);

	const float shiftSpeed = (KeyInput::GetKeyModState(KMOD_SHIFT) ? 3.0f : 1.0f);
	const float altZoomDist = height * move * 0.007f * shiftSpeed;
	
	// tilt the camera if LCTRL is pressed
	//
	// otherwise holding down LALT uses 'instant-zoom'
	// from here to the end of the function (smoothed)
	if (KeyInput::GetKeyModState(KMOD_CTRL)) {
		angle += (move * tiltSpeed * shiftSpeed * 0.025f) * angleStep;
		angle = Clamp(angle, 0.01f, fastmath::HALFPI);
	} else {
		if (move < 0.0f) {
			// ZOOM IN to mouse cursor instead of mid screen
			float3 cpos = pos - dir * height;
			float dif = -altZoomDist;

			if ((height - dif) < 60.0f) {
				dif = height - 60.0f;
			}
			if (KeyInput::GetKeyModState(KMOD_ALT)) {
				// instazoom in to standard view
				dif = (height - oldAltHeight) / mouse->dir.y * dir.y;
			}

			float3 wantedPos = cpos + mouse->dir * dif;
			float newHeight = CGround::LineGroundCol(wantedPos, wantedPos + dir * 15000, false);

			if (newHeight < 0.0f) {
				newHeight = height * (1.0f + move * 0.007f * shiftSpeed);
			}
			if ((wantedPos.y + (dir.y * newHeight)) < 0.0f) {
				newHeight = -wantedPos.y / dir.y;
			}
			if (newHeight < maxHeight) {
				height = newHeight;
				pos = wantedPos + dir * height;
			}
		} else {
			// ZOOM OUT from mid screen
			if (KeyInput::GetKeyModState(KMOD_ALT)) {
				// instazoom out to maximum height
				if (height < maxHeight*0.5f && changeAltHeight) {
					oldAltHeight = height;
					changeAltHeight = false;
				}
				height = maxHeight;
				pos.x  = mapDims.mapx * SQUARE_SIZE * 0.5f;
				pos.z  = mapDims.mapy * SQUARE_SIZE * 0.55f; // somewhat longer toward bottom
			} else {
				height *= (1.0f + (altZoomDist / height));
			}
		}

		// instant-zoom: turn on the smooth transition and reset the camera tilt
		if (KeyInput::GetKeyModState(KMOD_ALT)) {
			angle = DEFAULT_ANGLE;
			camHandler->CameraTransition(1.0f);
		} else {
			changeAltHeight = true;
		}
	}

	Update();
}
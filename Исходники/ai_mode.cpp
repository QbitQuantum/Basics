//-----------------------------------------------
// aiMode :
// Manage the Fly Mode.
//-----------------------------------------------
void CUserControls::aiMode()
{
	CInterfaceManager *IM = CInterfaceManager::getInstance ();

	// Left Click and Dbl Click
	bool dblClickLeft = false;
	if(EventsListener.isMouseButtonPushed(leftButton))
	{
		_LeftClickStart = T1;
	}
	if( EventsListener.isMouseButtonReleased (leftButton) )
	{
		if(T1 <= _LeftClickEnd + CWidgetManager::getInstance()->getUserDblClickDelay())
		{
			dblClickLeft = true;
		}
		_LeftClickEnd = T1;
	}

	// Right Click and Dbl Click
	bool dblClickRight = false;
	if(EventsListener.isMouseButtonPushed(rightButton))
	{
		_RightClickStart = T1;
	}
	if( EventsListener.isMouseButtonReleased (rightButton) )
	{
		if(T1 <= _RightClickEnd + CWidgetManager::getInstance()->getUserDblClickDelay())
		{
			dblClickRight = true;
		}
		_RightClickEnd = T1;
	}

	if (EventsListener.isMouseButtonReleased (rightButton))
	{
		// Short Right Click -> Check Action
		if((T1-_RightClickStart) <= _TimeLongClick)
		{
			if(ClientCfg.SelectWithRClick)
				execActionCursorPos(true,dblClickRight);

			// Launch Context Menu
			if (!R2::isEditionCurrent()) // context menu managed in a different fashion for R2ED
			{
				IM->launchContextMenuInGame("ui:interface:game_context_menu");
			}
		}
		else
		{
			EventsListener.enableMouseSmoothing(false);
		}

		// Give back the mouse handling to the interface.
		CWidgetManager::getInstance()->enableMouseHandling(true);
	}
	else if (EventsListener.isMouseButtonDown (rightButton))
	{
		if((T1-_RightClickStart) > _TimeLongClick)
		{
			CWidgetManager::getInstance()->enableMouseHandling(false);
			EventsListener.enableMouseSmoothing(true);
			// Get the cursor instance and hide.
			CViewPointer *cursor = static_cast< CViewPointer* >( CWidgetManager::getInstance()->getPointer() );
			if(cursor)
			{
				// Freelook mode.
				SetMouseFreeLook ();
			}

			if (EventsListener.isMouseAngleX())
			{
				// Rotate the body.
				CMatrix m;
				m.identity();
				m.rotateZ(-EventsListener.getMouseAngleX ());
				View.view((m * View.view()).normed());
			}

			if (EventsListener.isMouseAngleY())
			{
				CMatrix m;
				// Get the rotation axis.
				CVector v = View.view() ^ CVector(0,0,1);
				// Transform to a Quaternion
				CQuat quat(v, EventsListener.getMouseAngleY ());

				// Get the rotation matrix.
				m.identity();
				m.setRot(quat);
				// Create a front vector from the view.
				CVector front = View.view();
				front.z = 0;
				front.normalize();
				// Set the new view.
				v = (m * View.view()).normed();
				if(v*front > 0)
					View.view(v);
			}
		}
	}
	else
	{
		// Freelook mode.
		SetMouseCursor ();

		// Is the left click activated.
		if (EventsListener.isMouseButtonReleased (leftButton))
			execActionCursorPos(true,dblClickLeft);
	}


	// Turn the camera to the left.
	if(Actions.valide("turn_left"))
	{
		CMatrix camMatrix = MainCam.getMatrix();
		camMatrix.rotateZ(DT*ClientCfg.RotKeySpeedMax);
		View.view(camMatrix.getJ());
	}
	// Turn the camera to the right.
	if(Actions.valide("turn_right"))
	{
		CMatrix camMatrix = MainCam.getMatrix();
		camMatrix.rotateZ(-DT*ClientCfg.RotKeySpeedMax);
		View.view(camMatrix.getJ());
	}

	// look up
	if (Actions.valide("look_up"))
	{
		CMatrix camMatrix = MainCam.getMatrix();
		// Avoid gimbal lock
		float	angle= DT*ClientCfg.RotKeySpeedMax;
		float	curAngle= asinf(camMatrix.getJ().z);
		if(curAngle+angle > float(0.95*Pi/2))
			angle= float(0.95*Pi/2) - curAngle;
		// rotate
		camMatrix.rotateX(angle);
		View.view(camMatrix.getJ());
	}
	// look down
	if (Actions.valide("look_down"))
	{
		CMatrix camMatrix = MainCam.getMatrix();
		// Avoid gimbal lock
		float	angle= -DT*ClientCfg.RotKeySpeedMax;
		float	curAngle= asinf(camMatrix.getJ().z);
		if(curAngle+angle < float(-0.95*Pi/2))
			angle= float(-0.95*Pi/2) - curAngle;
		// rotate
		camMatrix.rotateX(angle);
		View.view(camMatrix.getJ());
	}

	// Move up
	float accel = 0;
	if (Actions.valide("camera_up"))
		accel += ClientCfg.FlyAccel;
	// Move down
	if (Actions.valide("camera_down"))
		accel -= ClientCfg.FlyAccel;
	updateVelocity (DT, accel, ClientCfg.FlyAccel, ClientCfg.Fly, _FlyVerticalVelocity);

	// Action "Foraward" is valide -> Autowalk false, forward true.
	accel = 0;
	if(Actions.valide("forward"))
		accel += ClientCfg.FlyAccel;
	// Action "backward" is valide -> Autowalk false, backward true.
	if(Actions.valide("backward"))
		accel -= ClientCfg.FlyAccel;
	updateVelocity (DT, accel, ClientCfg.FlyAccel, ClientCfg.Fly, _FlyFrontVelocity);

	// Action "strafe_left" is valide -> strafeLeft true.
	accel = 0;
	if(Actions.valide("strafe_left"))
		accel -= ClientCfg.FlyAccel;
	// Action "strafe_right" is valide -> strafeRight true.
	if(Actions.valide("strafe_right"))
		accel += ClientCfg.FlyAccel;
	updateVelocity (DT, accel, ClientCfg.FlyAccel, ClientCfg.Fly, _FlyLateralVelocity);

	// Set the view.
	const CMatrix &camMatrix = MainCam.getMatrix();
	View.viewPos(View.viewPos() + camMatrix.getI()*(_FlyLateralVelocity*DT) + camMatrix.getJ()*(_FlyFrontVelocity*DT) + camMatrix.getK()*(_FlyVerticalVelocity*DT));
}// aiMode //
	bool ControllerInput::OISMouse_MouseMoved(const OIS::MouseEvent &arg)
    {   		
		// delta pixels
		int dx = arg.state.X.rel;
		int dy = arg.state.Y.rel;
		int dz = arg.state.Z.rel;
		
		if (dx == 0 && dy == 0 && dz == 0)
			return true;

		bool isAiming = false;

		// update flag whether mouse is in window or not
		IsMouseInWindow = (
			arg.state.X.abs > 0 && arg.state.Y.abs > 0 &&
			arg.state.X.abs < arg.state.width && arg.state.Y.abs < arg.state.height);

		// inject mousemove to cegui	
		ControllerUI::InjectMousePosition((float)arg.state.X.abs, (float)arg.state.Y.abs);
		
		// if the cursor moved outside the window
		// make sure to release any pressed keys
		if (!isMouseInWindow)
		{
			if (IsLeftMouseDown)
				ControllerUI::InjectMouseButtonUp(CEGUI::MouseButton::LeftButton);

			if (IsRightMouseDown)
				ControllerUI::InjectMouseButtonUp(CEGUI::MouseButton::RightButton);
		}

		// exit conditions
		if (!OgreClient::Singleton->RenderWindow ||
			!OgreClient::Singleton->RenderWindow->isVisible() ||
			!OgreClient::Singleton->RenderWindow->isActive() ||
			!OgreClient::Singleton->HasFocus ||
			!isMouseInWindow)
			return true;
		
		// inject wheel
		ControllerUI::InjectMouseWheelChange((float)dz / 120.0f);
						
		// the cameranode
		SceneNode* cameraNode = OgreClient::Singleton->CameraNode;

		// exit conditions for 'actual playing' e.g. with avatar set
		if (OgreClient::Singleton->Data->IsWaiting || 
			Avatar == nullptr ||                
            Avatar->SceneNode == nullptr ||
			cameraNode == nullptr)
			return true;

		if (!isMouseWentDownOnUI)
		{
			// there is a small delay until aiming starts, to not shackle the
			// camera with any short mouseclick
			double dtRightButton = OgreClient::Singleton->GameTick->Current - tickMouseDownRight;
			double dtLeftButton = OgreClient::Singleton->GameTick->Current - tickMouseDownLeft;

			// right mousebutton (or both) pressed and dleay for mouseaim exceeded
			if (IsRightMouseDown && dtRightButton > MOUSELOOKMINDELAY)
			{				
				if (dx != 0)					    
				{
					// stop immediately if we switched directions
					if (::System::Math::Sign(dx) != ::System::Math::Sign(avatarYawDelta))
						avatarYawDelta = 0.0f;

					// set a new delta and stepsize
					// this will be processed tick based
					avatarYawDelta += MOUSELOOKSPEED * (float)OgreClient::Singleton->Config->MouseAimSpeed * (float)dx;
					avatarYawStep = MOUSELOOKSTEPFACT * avatarYawDelta * ::System::Math::Max((float)OgreClient::Singleton->GameTick->Span, 1.0f);

					isAiming = true;
				}

				if (dy != 0)
				{
					// invert mouse y if enabled in config
					if (OgreClient::Singleton->Config->InvertMouseY)
						dy = -dy;

					// stop immediately if we switched directions
					if (::System::Math::Sign(dy) != ::System::Math::Sign(cameraPitchDelta))
						cameraPitchDelta = 0.0f;

					// set a new delta and stepsize
					// this will be processed tick based
					cameraPitchDelta += MOUSELOOKSPEED * (float)OgreClient::Singleton->Config->MouseAimSpeed * (float)dy;
					cameraPitchStep = MOUSELOOKSTEPFACT * cameraPitchDelta * ::System::Math::Max((float)OgreClient::Singleton->GameTick->Span, 1.0f);

					isAiming = true;
				}
			}

			// left mousebutton pressed and delay for mouseaim exceeded
			else if (IsLeftMouseDown && dtLeftButton > MOUSELOOKMINDELAY)
			{                    
				if (dx != 0)
				{
					// stop immediately if we switched directions
					if (::System::Math::Sign(dx) != ::System::Math::Sign(cameraYawDelta))
						cameraYawDelta = 0.0f;

					// set a new delta and stepsize
					// this will be processed tick based
					cameraYawDelta += MOUSELOOKSPEED * (float)OgreClient::Singleton->Config->MouseAimSpeed * (float)dx;
					cameraYawStep = MOUSELOOKSTEPFACT * cameraYawDelta * ::System::Math::Max((float)OgreClient::Singleton->GameTick->Span, 1.0f);

					isAiming = true;
				}
	
				if (dy != 0)
				{	
					// invert mouse y if enabled in config
					if (OgreClient::Singleton->Config->InvertMouseY)
						dy = -dy;

					// stop immediately if we switched directions
					if (::System::Math::Sign(dy) != ::System::Math::Sign(cameraPitchDelta))
						cameraPitchDelta = 0.0f;

					// set a new delta and stepsize
					// this will be processed tick based
					cameraPitchDelta += MOUSELOOKSPEED * (float)OgreClient::Singleton->Config->MouseAimSpeed * (float)dy;
					cameraPitchStep = MOUSELOOKSTEPFACT * cameraPitchDelta * ::System::Math::Max((float)OgreClient::Singleton->GameTick->Span, 1.0f);

					isAiming = true;
				}
			}

			// mousewheel / zoom
			if (dz != 0 && ControllerUI::IgnoreTopControlForMouseInput)
			{			
				// set a new delta and stepsize
				// this will be processed tick based
				cameraZDelta += ZOOMSPEED * (float)dz;
				cameraZStep = MOUSELOOKSTEPFACT * cameraZDelta * ::System::Math::Max((float)OgreClient::Singleton->GameTick->Span, 1.0f);
			}

			// restore/fixed windows cursor position on mouse look										
			if (IsAnyMouseDown)							
				SetCursorPos(mouseDownWindowsPosition->x, mouseDownWindowsPosition->y);	
		}
		
		if (!isAiming && ControllerUI::IgnoreTopControlForMouseInput)
			PerformMouseOver(arg.state.X.abs, arg.state.Y.abs, false);												 

        return true;
    };
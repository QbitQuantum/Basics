void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
	float fSpeed = 0.01f;
#pragma region ON_MOUSE_PRESS_RELEASE
	static bool	bLastLeft = false, bLastMiddle = false, bLastRight = false;
#define ON_MOUSE_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion
	bool bLeft = false;
	ON_MOUSE_PRESS_RELEASE(Left, NULL, bLeft = true)
	if (bLeft)
	{
		//Turn off the visibility of all BOs for all instances
		m_pMeshMngr->SetVisibleBO(BD_NONE, "ALL", -1);
		//Get the Position and direction of the click on the screen
		std::pair<vector3, vector3> pair =
			m_pCameraMngr->GetClickAndDirectionOnWorldSpace(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
		float fDistance = 0;//Stores the distance to the first colliding object
		m_selection = m_pMeshMngr->IsColliding(pair.first, pair.second, fDistance);

		//If there is a collision
		if (m_selection.first >= 0)
		{
			//Turn on the BO of the group
			m_pMeshMngr->SetVisibleBO(BD_OB, m_selection.first, m_selection.second);

			//Turn of the BO of the instance but not the group
			m_pMeshMngr->SetVisibleBO(BD_NONE, m_selection.first, -2);
		}
	}
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
		m_bArcBall = true;
	
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;

	if (m_bFPC) {
		//the following code is taken from ReEngAppClass.h CameraRotation ln 351
		UINT	MouseX, MouseY;		// Coordinates for the mouse
		UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

									//Initialize the position of the pointer to the middle of the screen
		CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
		CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

		//Calculate the position of the mouse and store it
		POINT pt;
		GetCursorPos(&pt);
		MouseX = pt.x;
		MouseY = pt.y;

		//Calculate the difference in view with the angle
		float fAngleX = 0.0f;
		float fAngleY = 0.0f;
		float fDeltaMouse = 0.0f;
		if (MouseX < CenterX)
		{
			fDeltaMouse = static_cast<float>(CenterX - MouseX);
			fAngleY += fDeltaMouse * fSpeed;
		}
		else if (MouseX > CenterX)
		{
			fDeltaMouse = static_cast<float>(MouseX - CenterX);
			fAngleY -= fDeltaMouse * fSpeed;
		}

		if (MouseY < CenterY)
		{
			fDeltaMouse = static_cast<float>(CenterY - MouseY);
			fAngleX -= fDeltaMouse * fSpeed;
		}
		else if (MouseY > CenterY)
		{
			fDeltaMouse = static_cast<float>(MouseY - CenterY);
			fAngleX += fDeltaMouse * fSpeed;
		}
		//Change the Yaw and the Pitch of the camera
		myCam->ChangeYaw(-fAngleY * 3.0f);
		myCam->ChangePitch(fAngleX * 3.0f);
		SetCursorPos(CenterX, CenterY);//Position the mouse in the center
	}
}
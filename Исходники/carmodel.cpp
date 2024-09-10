void CarModel::MoveBackward(){

	  //Move the airplane in the direction it is facing based on its
	  //direction vector and the speed factor which can be adjusted for smooth motion

	  XMFLOAT3 effectiveDirectionVector;
	  XMFLOAT4X4 fuselageDirectionMatrix = m_Body->GetWorldRotateMatrix();
      XMStoreFloat3( &effectiveDirectionVector,  XMVector3Transform( XMLoadFloat3(&m_directionVector), XMLoadFloat4x4(&fuselageDirectionMatrix) ));

	  float deltaX = -effectiveDirectionVector.x*CAR_FORWARD_SPEED_FACTOR;
	  float deltaY = -effectiveDirectionVector.y*CAR_FORWARD_SPEED_FACTOR;
	  float deltaZ = -effectiveDirectionVector.z*CAR_FORWARD_SPEED_FACTOR;

	  //Move all the  component parts of the airplane relative to the world
	  //co-ordinate system

	  m_Body->worldTranslate(deltaX, deltaY, deltaZ);
	  m_WheelFL->worldTranslate(deltaX, deltaY, deltaZ);
	   m_WheelFR->worldTranslate(deltaX, deltaY, deltaZ);
	    m_WheelBL->worldTranslate(deltaX, deltaY, deltaZ);
		 m_WheelBR->worldTranslate(deltaX, deltaY, deltaZ);
	  //Spin the wheels
	float wheelRadianAngularIncrement = XM_PIDIV4/5; //sign changes direction of the propeller
	m_WheelFL->orientRotateZ(wheelRadianAngularIncrement);
	m_WheelFR->orientRotateZ(wheelRadianAngularIncrement);
	m_WheelBL->orientRotateZ(wheelRadianAngularIncrement);
	m_WheelBR->orientRotateZ(wheelRadianAngularIncrement);
}
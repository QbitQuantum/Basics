void TopicApp::OnMouseMove(WPARAM btnState, int x, int y)
{
    //Rotate if left mouse button is pressed
    if( (btnState & MK_LBUTTON) != 0 )
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - m_lastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - m_lastMousePos.y));

		m_cam.pitch(dy); //Rotate on right vector (x axis)
		m_cam.rotateY(dx);
	}

	m_lastMousePos.x = x;
	m_lastMousePos.y = y;
}
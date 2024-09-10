bool BoidsSimulation::OnEvent( MSG* msg )
{
	switch (msg->message)
	{
	case WM_MOUSEWHEEL:
	{
		auto delta = GET_WHEEL_DELTA_WPARAM( msg->wParam );
		m_camera.ZoomRadius( -0.1f*delta );
	}
	case WM_POINTERDOWN:
	case WM_POINTERUPDATE:
	case WM_POINTERUP:
	{
		auto pointerId = GET_POINTERID_WPARAM( msg->wParam );
		POINTER_INFO pointerInfo;
		if (GetPointerInfo( pointerId, &pointerInfo )) {
			if (msg->message == WM_POINTERDOWN) {
				// Compute pointer position in render units
				POINT p = pointerInfo.ptPixelLocation;
				ScreenToClient( Core::g_hwnd, &p );
				RECT clientRect;
				GetClientRect( Core::g_hwnd, &clientRect );
				p.x = p.x * Core::g_config.swapChainDesc.Width / (clientRect.right - clientRect.left);
				p.y = p.y * Core::g_config.swapChainDesc.Height / (clientRect.bottom - clientRect.top);
				// Camera manipulation
				m_camera.AddPointer( pointerId );
			}
		}

		// Otherwise send it to the camera controls
		m_camera.ProcessPointerFrames( pointerId, &pointerInfo );
		if (msg->message == WM_POINTERUP) m_camera.RemovePointer( pointerId );
	}
	}
	return false;
}
UINT CRoboticsLabDlg::StartDlgUpdateThread (LPVOID param){

	DLGTHREADSTRUCT*	ts = (DLGTHREADSTRUCT*)param;

	Sleep(3000);

	// Default Point to Simulator so that encoders can point to something
	ts->_this->m_MOTSDK = &(ts->_this->m_MOTSDK_simulator);


	// Update openGL screen until terminated from dialog OK
	while(!ts->_this->openGLControl->terminate && !ts->_this->StopThreads)
	{

		// Update Encoders
		ts->_this->m_Encoder1 = ts->_this->m_MOTSDK->GetEncoderPulse1();
		ts->_this->m_Encoder2 = ts->_this->m_MOTSDK->GetEncoderPulse2();

		// Udpate Sonars
		ts->_this->m_Sonar1= ts->_this->m_MOTSDK->GetSensorSonar1 (ts->_this->robot_dlg->x, ts->_this->robot_dlg->y, ts->_this->robot_dlg->t);
		ts->_this->m_Sonar2= ts->_this->m_MOTSDK->GetSensorSonar2 (ts->_this->robot_dlg->x, ts->_this->robot_dlg->y, ts->_this->robot_dlg->t);
		ts->_this->m_Sonar3= ts->_this->m_MOTSDK->GetSensorSonar3 (ts->_this->robot_dlg->x, ts->_this->robot_dlg->y, ts->_this->robot_dlg->t);

		// Update IR sensors
		ts->_this->m_IR1 = ts->_this->m_MOTSDK->GetSensorIRRange (ts->_this->robot_dlg->x, ts->_this->robot_dlg->y, ts->_this->robot_dlg->t);	
		ts->_this->m_IR2 = ts->_this->m_MOTSDK->GetCustomAD3 (ts->_this->robot_dlg->x, ts->_this->robot_dlg->y, ts->_this->robot_dlg->t);
		ts->_this->m_IR3 = ts->_this->m_MOTSDK->GetCustomAD4 (ts->_this->robot_dlg->x, ts->_this->robot_dlg->y, ts->_this->robot_dlg->t);
		ts->_this->m_IR4 = ts->_this->m_MOTSDK->GetCustomAD5 (ts->_this->robot_dlg->x, ts->_this->robot_dlg->y, ts->_this->robot_dlg->t);
		ts->_this->m_IR5 = ts->_this->m_MOTSDK->GetCustomAD6 (ts->_this->robot_dlg->x, ts->_this->robot_dlg->y, ts->_this->robot_dlg->t);
		ts->_this->m_IR6 = ts->_this->m_MOTSDK->GetCustomAD7 (ts->_this->robot_dlg->x, ts->_this->robot_dlg->y, ts->_this->robot_dlg->t);
		ts->_this->m_IR7 = ts->_this->m_MOTSDK->GetCustomAD8 (ts->_this->robot_dlg->x, ts->_this->robot_dlg->y, ts->_this->robot_dlg->t);

		//ts->_this->openGLControl->Invalidate();
		//ts->_this->openGLControl->UpdateWindow();

		// Send WM_PAINT Message
		RECT DialogRegion;
		CRgn Region; 
		Region.CreateRectRgnIndirect(&DialogRegion);
		//ts->_this->InvalidateRgn(&Region,TRUE);
		ts->_this->openGLControl->Invalidate(TRUE);
		//ts->_this->OnPaint();
		
		// Sleep to approximate 10 Hz update rate
		Sleep(100);
	}
	//AfxEndThread(0);
	
	return 1;
}
BOOL CDemoPlay::ProcessCam(SCamEffectorInfo& info)
{
	// skeep a few frames before counting
	if (Device.dwPrecacheFrame)	return	TRUE;

	if (stat_started)
	{
		//g_SASH.DisplayFrame(Device.fTimeGlobal);
	}
	else
	{
		//g_SASH.StartBenchmark();
		stat_Start();
	}

	// Per-frame statistics
	{
		stat_table.push_back		(stat_Timer_frame.GetElapsed_sec());
		stat_Timer_frame.Start		();
	}

	// Process motion
	if (m_pMotion)
	{
		Fvector R;
		Fmatrix mRotate;
		m_pMotion->_Evaluate	(m_MParam->Frame(),info.p,R);
		m_MParam->Update		(Device.fTimeDelta,1.f,true);
		fLifeTime				-= Device.fTimeDelta;
		if (m_MParam->bWrapped)	{ stat_Stop(); stat_Start(); }
		mRotate.setXYZi			(R.x,R.y,R.z);
		info.d.set				(mRotate.k);
		info.n.set				(mRotate.j);
	}
	else
	{
		if (seq.empty()) {
			g_pGameLevel->Cameras().RemoveCamEffector(cefDemo);
			return		TRUE;
		}

		fStartTime		+=	Device.fTimeDelta;
		
		float	ip;
		float	p		=	fStartTime/fSpeed;
		float	t		=	modff(p, &ip);
		int		frame	=	iFloor(ip);
		VERIFY	(t>=0);
		
		if (frame>=m_count)
		{
			dwCyclesLeft			--	;
			if (0==dwCyclesLeft)	return FALSE;
			fStartTime				= 0	;
			// just continue
			// stat_Stop			();
			// stat_Start			();
		}
		
		int f1=frame; FIX(f1);
		int f2=f1+1;  FIX(f2);
		int f3=f2+1;  FIX(f3);
		int f4=f3+1;  FIX(f4);
		
		Fmatrix *m1,*m2,*m3,*m4;
		Fvector v[4];
		m1 = (Fmatrix *) &seq[f1];
		m2 = (Fmatrix *) &seq[f2];
		m3 = (Fmatrix *) &seq[f3];
		m4 = (Fmatrix *) &seq[f4];
		
		for (int i=0; i<4; i++) {
			v[0].x = m1->m[i][0]; v[0].y = m1->m[i][1];  v[0].z = m1->m[i][2];
			v[1].x = m2->m[i][0]; v[1].y = m2->m[i][1];  v[1].z = m2->m[i][2];
			v[2].x = m3->m[i][0]; v[2].y = m3->m[i][1];  v[2].z = m3->m[i][2];
			v[3].x = m4->m[i][0]; v[3].y = m4->m[i][1];  v[3].z = m4->m[i][2];
			spline1	( t, &(v[0]), (Fvector *) &(Device.mView.m[i][0]) );
		}
		
		Fmatrix mInvCamera;
		mInvCamera.invert(Device.mView);
		info.n.set( mInvCamera._21, mInvCamera._22, mInvCamera._23 );
		info.d.set( mInvCamera._31, mInvCamera._32, mInvCamera._33 );
		info.p.set( mInvCamera._41, mInvCamera._42, mInvCamera._43 );
		
		fLifeTime-=Device.fTimeDelta;
	}
	return TRUE;
}
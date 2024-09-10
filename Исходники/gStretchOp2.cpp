// Update =============================================================================
CStatus gStretchOp2Multi_Update( CRef& in_ctxt )
{

	OperatorContext ctxt( in_ctxt );

		// User Datas ------------------------------------
		CValue::siPtrType pUserData = ctxt.GetUserData();
		OpUserData* pOpState = (OpUserData*)pUserData;

		if ( pOpState == NULL || pOpState->index >= 2)
		{
			// First time called
			pOpState = new OpUserData();
			ctxt.PutUserData( (CValue::siPtrType)pOpState );

			// Inputs ---------------------------------------
			KinematicState kRoot(ctxt.GetInputValue(0));
			KinematicState kCtrl(ctxt.GetInputValue(1));
			CTransformation tRoot(kRoot.GetTransform());
			CTransformation tCtrl(kCtrl.GetTransform());
			CVector3 vRoot = tRoot.GetTranslation();
			CVector3 vCtrl = tCtrl.GetTranslation();
			CMatrix4 mRoot = tRoot.GetMatrix4();
			CMatrix4 mRootNeg;
			mRootNeg.Invert(mRoot);

			double dRestLength = ctxt.GetParameterValue(L"restlength");
			double dScale      = ctxt.GetParameterValue(L"scale");
			double dSoftness   = ctxt.GetParameterValue(L"soft");
			double dMaxStretch = ctxt.GetParameterValue(L"maxstretch");

			// Distance with MaxStretch ---------------------
			dRestLength = dRestLength * dScale - .00001;
			CVector3 vDistance;
			vDistance.MulByMatrix4(vCtrl, mRootNeg);
			double dDistance = vDistance.GetLength();
			double dDistance2 = dDistance;
			if (dDistance > (dRestLength * dMaxStretch))
			{
				vDistance.NormalizeInPlace();
				vDistance.ScaleInPlace(dRestLength * dMaxStretch);
				dDistance = dRestLength * dMaxStretch;
			}

			Application app;
			app.LogMessage(L"dist : "+CString(dDistance));
			app.LogMessage(L"dist2 : "+CString(dDistance2));

			// Adapt Softness value to chain length --------
			dSoftness = dSoftness * dRestLength *.1;

			// Stretch and softness ------------------------
			/// We use the real distance from root to controler to calculate the softness
			/// This way we have softness working even when there is no stretch
			double dStretch = dDistance/dRestLength;
			if (dStretch < 1)
				dStretch = 1;
			double da = dRestLength - dSoftness;
			if (dSoftness > 0 && dDistance2 > da)
			{
				double newlen = dSoftness*(1.0 - exp(-(dDistance2 -da)/dSoftness)) + da;
				dStretch = dDistance / newlen;
			}

			double dScaleX = dStretch * dScale;
			app.LogMessage(L"scalex : "+CString(dScaleX));

			// Effector Position ----------------------------
			CTransformation t;
			vDistance.MulByMatrix4(vDistance, mRoot);
			t.SetTranslation(vDistance);

			pOpState->index = 0;
			pOpState->t = t;
			pOpState->dLength0 = dScaleX;
		}

	// Outputs -------------------------------------
	CRef outputPortRef=ctxt.GetOutputPort();
	OutputPort OutPort(outputPortRef);

	// Effector Transform
	if (OutPort.GetIndex() == 2)
	{
		KinematicState kOut = ctxt.GetOutputTarget();
		kOut.PutTransform(pOpState->t);
	}
	// Bone 0 Length
	else if (OutPort.GetIndex() == 3)
	{
		OutPort.PutValue(pOpState->dLength0);
	}

	pOpState->index += 1;

	return CStatus::OK;
}
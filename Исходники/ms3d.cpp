//-------------------------------------------------------------
//- Animate
//- Animates the model from start time to end time (in seconds)
//- at specified speed and can loop
//-------------------------------------------------------------
void CMs3d::Animate(float fSpeed, float fStartTime, float fEndTime, bool bLoop)
{
	static bool bFirstTime = true;
	//First time animate has been called
	if(bFirstTime)
	{
		Reset();
		bFirstTime = false;
	}

	static float fLastTime = fStartTime;

	float fTime = m_Timer.GetSeconds() * fSpeed;
	fTime += fLastTime;
	fLastTime = fTime;
	
	//looping
	if(fTime > fEndTime)
	{
		if(bLoop)
		{
			Reset();
			fLastTime = fStartTime;
			fTime = fStartTime;
		}
		else
			fTime = fEndTime;
	}	

	for(int x = 0; x < m_usNumJoints; x++)
	{
		//Transformation matrix
		CMatrix4X4 matTmp;
		//Current joint
		SMs3dJoint * pJoint = &m_pJoints[x];
		//Current frame
		unsigned int uiFrame = 0;

		//if there are no keyframes, don't do any transformations
		if(pJoint->m_usNumRotFrames == 0 && pJoint->m_TransKeyFrames == 0)
		{
			pJoint->m_matFinal = pJoint->m_matAbs;
			continue;
		}
		//Calculate the current frame
		//Translation
		while(uiFrame < pJoint->m_usNumTransFrames && pJoint->m_TransKeyFrames[uiFrame].m_fTime < fTime)
			uiFrame++;
		pJoint->m_usCurTransFrame = uiFrame;

		float fTranslation[3];
		float fDeltaT = 1;
		float fInterp = 0;

		//If its at the extremes
		if(uiFrame == 0)
			memcpy(fTranslation, pJoint->m_TransKeyFrames[0].m_fParam, sizeof(float[3]));
		else if(uiFrame == pJoint->m_usNumTransFrames)
			memcpy(fTranslation, pJoint->m_TransKeyFrames[uiFrame-1].m_fParam, sizeof(float[3]));
		//If its in the middle of two frames
		else
		{
			SMs3dKeyFrame * pkCur = &pJoint->m_TransKeyFrames[uiFrame];
			SMs3dKeyFrame * pkPrev = &pJoint->m_TransKeyFrames[uiFrame-1];
			
			fDeltaT = pkCur->m_fTime - pkPrev->m_fTime;
			fInterp = (fTime - pkPrev->m_fTime) / fDeltaT;
			
			//Interpolate between the translations
			fTranslation[0] = pkPrev->m_fParam[0] + (pkCur->m_fParam[0] - pkPrev->m_fParam[0]) * fInterp;
			fTranslation[1] = pkPrev->m_fParam[1] + (pkCur->m_fParam[1] - pkPrev->m_fParam[1]) * fInterp;
			fTranslation[2] = pkPrev->m_fParam[2] + (pkCur->m_fParam[2] - pkPrev->m_fParam[2]) * fInterp;
		}
		//Calculate the current rotation
		uiFrame = 0;
		while(uiFrame < pJoint->m_usNumRotFrames && pJoint->m_RotKeyFrames[uiFrame].m_fTime < fTime)
			uiFrame++;


		//If its at the extremes
		if(uiFrame == 0)
			matTmp.SetRotation(pJoint->m_RotKeyFrames[0].m_fParam);
		else if(uiFrame == pJoint->m_usNumTransFrames)
			matTmp.SetRotation(pJoint->m_RotKeyFrames[uiFrame-1].m_fParam);
		//If its in the middle of two frames, use a quaternion SLERP operation to calculate a new position
		else
		{
			SMs3dKeyFrame * pkCur = &pJoint->m_RotKeyFrames[uiFrame];
			SMs3dKeyFrame * pkPrev = &pJoint->m_RotKeyFrames[uiFrame-1];

			fDeltaT = pkCur->m_fTime - pkPrev->m_fTime;
			fInterp = (fTime - pkPrev->m_fTime) / fDeltaT;
			
			//Create a rotation quaternion for each frame
			CQuaternion qCur;
			CQuaternion qPrev;
			qCur.FromEulers(pkCur->m_fParam);
			qPrev.FromEulers(pkPrev->m_fParam);
			//SLERP between the two frames
			CQuaternion qFinal = SLERP(qPrev, qCur, fInterp);

			//Convert the quaternion to a rotation matrix
			matTmp = qFinal.ToMatrix4();
		}

		//Set the translation part of the matrix
		matTmp.SetTranslation(fTranslation);

		//Calculate the joints final transformation
		CMatrix4X4 matFinal = pJoint->m_matLocal * matTmp;

		//if there is no parent, just use the matrix you just made
		if(pJoint->m_sParent == -1)
			pJoint->m_matFinal = matFinal;
		//otherwise the final matrix is the parents final matrix * the new matrix
		else
			pJoint->m_matFinal = m_pJoints[pJoint->m_sParent].m_matFinal * matFinal;
	}


	//Transform and render the meshes
	if(m_bDrawMesh)
		RenderT();

	if(m_bDrawBones)
	{
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
		glLineWidth(5);
		//Draw the bones
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINES);	
		for(int x = 1; x < m_usNumJoints; x++)
		{
			float * fMat = m_pJoints[x].m_matFinal.Get();
			float * fMatParent = m_pJoints[m_pJoints[x].m_sParent].m_matFinal.Get();
			glVertex3f(fMat[12], fMat[13], fMat[14]);
			glVertex3f(fMatParent[12], fMatParent[13], fMatParent[14]);
		}
		glEnd();

		glEnable(GL_DEPTH_TEST);
	}
}
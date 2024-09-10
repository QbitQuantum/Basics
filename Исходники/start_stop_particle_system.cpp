//******************************************************************************************************
void CStartStopParticleSystem::goPreRender()
{	
	if (!_ActiveNode) return;
	NL3D::CParticleSystem *ps = _ActiveNode->getPSPointer();
	sint currNumParticles = (sint) ps->getCurrNumParticles();
	sint maxNumParticles = (sint) ps->getMaxNumParticles();
	// if linked with scene animation, restart if animation ends
	if (m_LinkPlayToScenePlay) // is scene animation subordinated to the fx animation
	{		
		// start animation for the scene too
		if (_AnimationDLG && isRunning())
		{
			if (_LastSceneAnimFrame > _AnimationDLG->CurrentFrame) // did animation restart ?
			{			
				restartAllFX();
			}
			_LastSceneAnimFrame = _AnimationDLG->CurrentFrame;
		}
	}
	else
	if (_AutoRepeat && !m_LinkPlayToScenePlay) // auto repeat feature
	{
		if (isRunning())
		{		
			bool allFXFinished = true;
			bool fxStarted = false;
			for(uint k = 0; k < _PlayingNodes.size(); ++k)
			{
				if (_PlayingNodes[k])
				{					
					if (isRunning(_PlayingNodes[k]))
					{					
						fxStarted = true;
						if (_PlayingNodes[k]->getPSPointer()->getSystemDate() <= _PlayingNodes[k]->getPSPointer()->evalDuration())
						{												
							allFXFinished = false;
							break;						
						}
						else
						{
							if (_PlayingNodes[k]->getPSPointer()->getCurrNumParticles() != 0)
							{						
								allFXFinished = false;
								break;
							}
						}
					}
				}
			}
			if (fxStarted && allFXFinished)
			{
				restartAllFX();
			}
		}
	}
	if (_State == RunningMultiple || _State == PausedMultiple)
	{
		std::set<std::string> currAnims;
		CObjectViewer *ov = _ParticleDlg->getObjectViewer();
		for(uint k = 0; k < ov->getNumInstance(); ++k)
		{
			CInstanceInfo *ci = ov->getInstance(k);
			uint animIndex = ci->Playlist.getAnimation(0);
			if (animIndex != NL3D::CAnimationSet::NotFound)
			{			
				std::string animName = ci->AnimationSet.getAnimationName(animIndex);
				if (!animName.empty())
				{
					currAnims.insert(animName);
				}
			}
		}				
		// check fx that have a trigger anim
		for(uint k = 0; k < _PlayingNodes.size(); ++k)
		{
			if (_PlayingNodes[k])
			{							
				if (!isRunning(_PlayingNodes[k]) || !_PlayingNodes[k]->getPSModel()->hasActiveEmitters())
				{
					// see if chosen anim is currently running
					if (_PlayingNodes[k]->getTriggerAnim().empty() || currAnims.count(_PlayingNodes[k]->getTriggerAnim()))
					{
						// if the fx was shutting down, stop then restart it
						if (!_PlayingNodes[k]->getPSModel()->hasActiveEmitters())
						{
							nlassert(isRunning(_PlayingNodes[k]));
							stop(*_PlayingNodes[k]);
						}
						// yes -> trigger the fx	
						play(*_PlayingNodes[k]);
					}
					else if (!_PlayingNodes[k]->getPSPointer()->hasParticles()) // fx is being shut down, stop it when necessary
					{					
						stop(*_PlayingNodes[k]); // no more particles so stop the system
					}					
				}
				else
				{					
					if (!_PlayingNodes[k]->getTriggerAnim().empty())
					{
						if (_PlayingNodes[k]->getPSModel()->hasActiveEmitters())
						{
							// see if anim if already playing. If this is not the case then shutdown the emitters
							if (!currAnims.count(_PlayingNodes[k]->getTriggerAnim()))
							{
								_PlayingNodes[k]->getPSModel()->activateEmitters(false);
							}
						}
					}					
				}
			}
		}
	}
	if (_ActiveNode)
	{	
		// display number of particles for the currently active node
		if (currNumParticles != _LastCurrNumParticles || maxNumParticles != _LastMaxNumParticles)
		{	
			CString numParts;	
			numParts.LoadString(IDS_NUM_PARTICLES);
			numParts += CString(NLMISC::toString("%d / %d",(int) currNumParticles, (int) maxNumParticles).c_str());
			GetDlgItem(IDC_NUM_PARTICLES)->SetWindowText((LPCTSTR) numParts);
			_LastCurrNumParticles = currNumParticles;
			_LastMaxNumParticles = maxNumParticles;
		}
		// display max number of wanted faces
		NLMISC::CMatrix camMat = ps->getScene()->getCam()->getMatrix();
		sint numWantedFaces = (uint) ps->getWantedNumTris((ps->getSysMat().getPos() - camMat.getPos()).norm());
		if (numWantedFaces != _LastNumWantedFaces)
		{	
			CString numWF;
			numWF.LoadString(IDS_NUM_WANTED_FACES);
			numWF += CString(NLMISC::toString("%d",(int) numWantedFaces).c_str());
			GetDlgItem(IDC_NUM_ASKED_FACES)->SetWindowText((LPCTSTR) numWF);
			_LastNumWantedFaces = numWantedFaces;		
		}
		// display system date
		if (ps->getSystemDate() != _LastSystemDate)
		{
			_LastSystemDate = ps->getSystemDate();
			CString sysDate;	
			sysDate.LoadString(IDS_SYSTEM_DATE);
			sysDate += CString(NLMISC::toString("%.2f s",_LastSystemDate).c_str());
			GetDlgItem(IDC_SYSTEM_DATE)->SetWindowText((LPCTSTR) sysDate);
		}	
	}
	if (_ParticleDlg)
	{
		CParticleWorkspace *pws = _ParticleDlg->getParticleWorkspace();
		if (pws)
		{
			for(uint k = 0; k < pws->getNumNode(); ++k)
			{
				if (pws->getNode(k)->isLoaded())
				{				
					if (pws->getNode(k) == _ActiveNode)
					{
						pws->getNode(k)->getPSModel()->enableDisplayTools(!isRunning(pws->getNode(k)) || m_DisplayHelpers);
					}
					else
					{
						pws->getNode(k)->getPSModel()->enableDisplayTools(false);
					}
					// hide / show the node
					if (_State == RunningMultiple || _State == PausedMultiple)
					{
						if (isRunning(pws->getNode(k)))
						{
							pws->getNode(k)->getPSModel()->show();
						}
						else
						{
							pws->getNode(k)->getPSModel()->hide();
						}
					}
					else
					{
						if (pws->getNode(k) == _ActiveNode)
						{
							pws->getNode(k)->getPSModel()->show();
						}
						else
						{
							pws->getNode(k)->getPSModel()->hide();
						}
					}
				}
			}
		}
	}
}
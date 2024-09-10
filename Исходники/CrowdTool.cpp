void CrowdToolState::handleRenderOverlay(double* proj, double* model, int* view)
{
	GLdouble x, y, z;
	
	// Draw start and end point labels
	if (m_targetRef && gluProject((GLdouble)m_targetPos[0], (GLdouble)m_targetPos[1], (GLdouble)m_targetPos[2],
								  model, proj, view, &x, &y, &z))
	{
		imguiDrawText((int)x, (int)(y+25), IMGUI_ALIGN_CENTER, "TARGET", imguiRGBA(0,0,0,220));
	}
	
	char label[32];
	
	if (m_toolParams.m_showLabels)
	{
		dtCrowd* crowd = m_sample->getCrowd();
		if (crowd)
		{
			for (int i = 0; i < crowd->getAgentCount(); ++i)
			{
				const dtCrowdAgent* ag = crowd->getAgent(i);
				if (!ag->active) continue;
				const float* pos = ag->npos;
				const float h = ag->params.height;
				if (gluProject((GLdouble)pos[0], (GLdouble)pos[1]+h, (GLdouble)pos[2],
							   model, proj, view, &x, &y, &z))
				{
					snprintf(label, 32, "%d", i);
					imguiDrawText((int)x, (int)y+15, IMGUI_ALIGN_CENTER, label, imguiRGBA(0,0,0,220));
				}
			}			
		}
	}
	if (m_agentDebug.idx != -1)
	{
		dtCrowd* crowd = m_sample->getCrowd();
		if (crowd) 
		{
			const dtCrowdAgent* ag = crowd->getAgent(m_agentDebug.idx);
			if (ag->active)
			{
				const float radius = ag->params.radius;
				
				if (m_toolParams.m_showNeis)
				{
					for (int j = 0; j < ag->nneis; ++j)
					{
						const dtCrowdAgent* nei = crowd->getAgent(ag->neis[j].idx);
						if (!nei->active) continue;
						
						if (gluProject((GLdouble)nei->npos[0], (GLdouble)nei->npos[1]+radius, (GLdouble)nei->npos[2],
									   model, proj, view, &x, &y, &z))
						{
							snprintf(label, 32, "%.3f", ag->neis[j].dist);
							imguiDrawText((int)x, (int)y+15, IMGUI_ALIGN_CENTER, label, imguiRGBA(255,255,255,220));
						}
					}
				}
			}
		}
	}
	
	
	if (m_toolParams.m_showPerfGraph)
	{
		GraphParams gp;
		gp.setRect(300, 10, 500, 200, 8);
		gp.setValueRange(0.0f, 2.0f, 4, "ms");
		
		drawGraphBackground(&gp);
		drawGraph(&gp, &m_crowdTotalTime, 1, "Total", duRGBA(255,128,0,255));
		
		gp.setRect(300, 10, 500, 50, 8);
		gp.setValueRange(0.0f, 2000.0f, 1, "");
		drawGraph(&gp, &m_crowdSampleCount, 0, "Sample Count", duRGBA(96,96,96,128));
	}
	
}
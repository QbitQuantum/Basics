void CMemoryCardView::CRender::DrawScene()
{
	RECT ClientRect;

	glClear(GL_COLOR_BUFFER_BIT);

	if(m_memoryCard == NULL) return;

	unsigned int nItemCount = static_cast<unsigned int>(m_memoryCard->GetSaveCount());
	CopyRect(&ClientRect, &m_viewState->m_ClientRect);

	int nY = 0;
	int nUpperClip = (int)(m_viewState->m_nScrollPosition - m_viewState->m_nItemHeight);
	int nLowerClip = nUpperClip + ClientRect.bottom + m_viewState->m_nItemHeight;

	for(unsigned int i = 0; i < nItemCount; i++)
	{
		if(nY >= nLowerClip) break;

		if(nY > nUpperClip)
		{
			glClear(GL_DEPTH_BUFFER_BIT);

			glViewport(0, 
				(ClientRect.bottom - nY - m_viewState->m_nItemHeight + m_viewState->m_nScrollPosition), 
				m_viewState->m_nItemWidth, 
				m_viewState->m_nItemHeight);

			if(nY == (m_viewState->m_nSelection * m_viewState->m_nItemHeight))
			{
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0, 1, 1, 0, 0, 1);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glDisable(GL_DEPTH_TEST);

				glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

				glBegin(GL_QUADS);
				{
					glVertex2f(0.0, 0.0);
					glVertex2f(1.0, 0.0);
					glVertex2f(1.0, 1.0);
					glVertex2f(0.0, 1.0);
				}
				glEnd();			
			}

			glEnable(GL_DEPTH_TEST);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();

			glTranslatef(0.0f, -2.0f, -7.0f);
			glScalef(1.0f, -1.0f, -1.0f);

			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f, (float)m_viewState->m_nItemWidth / (float)m_viewState->m_nItemHeight, 0.1f, 100.0f);

			IconMeshPtr iconMesh;
			IconList::iterator itIcon = m_icons.find(i);
			if(itIcon == m_icons.end())
			{
				const CSave* pSave = m_memoryCard->GetSaveByIndex(i);
				try
				{
					auto iconStream(Framework::CreateInputStdStream(pSave->GetNormalIconPath().native()));
					IconPtr iconData(new CIcon(iconStream));
					iconMesh = IconMeshPtr(new CIconMesh(iconData));
				}
				catch(...)
				{

				}
				m_icons[i] = iconMesh;
			}
			else
			{
				iconMesh = itIcon->second;
			}

			if(iconMesh)
			{
				iconMesh->Render();
			}
		}

		nY += m_viewState->m_nItemHeight;
	}

	SwapBuffers(m_deviceContext);
}
void CCDirector::popToSceneStackLevel(int level)
{
    CCAssert(m_pRunningScene != NULL, "A running Scene is needed");
    int c = (int)m_pobScenesStack->count();

    // level 0? -> end
    if (level == 0)
    {
        end();
        return;
    }

    // current level or lower -> nothing
    if (level >= c)
        return;

	// pop stack until reaching desired level
	while (c > level)
    {
		CCScene *current = (CCScene*)m_pobScenesStack->lastObject();

		if (current->isRunning())
        {
            current->onExitTransitionDidStart();
            current->onExit();
		}

        current->cleanup();
        m_pobScenesStack->removeLastObject();
		c--;
	}

	m_pNextScene = (CCScene*)m_pobScenesStack->lastObject();
	m_bSendCleanupToScene = false;
}
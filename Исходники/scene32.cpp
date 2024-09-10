void sceneHandler32_potLogic(ExCommand *cmd) {
	if (g_vars->scene32_cactusCounter < 0 || g_vars->scene32_cactusCounter > 20) {
		MessageQueue *mq = new MessageQueue(g_fp->_globalMessageQueueList->compact());

		ExCommand *ex = new ExCommand(ANI_MAN, 1, MV_MAN32_STANDUP, 0, 0, 0, 1, 0, 0, 0);

		ex->_excFlags |= 2;

		mq->addExCommandToEnd(ex);

		StaticANIObject *ani = g_fp->_currentScene->getStaticANIObjectAtPos(cmd->_sceneClickX, cmd->_sceneClickY);

		if (!ani || ani->_id != ANI_KADKA)
			mq->addExCommandToEnd(cmd->createClone());

		mq->setFlags(mq->getFlags() | 1);
		mq->chain(0);

		getCurrSceneSc2MotionController()->activate();
		getGameLoaderInteractionController()->enableFlag24();

		g_vars->scene32_dudeIsSitting = false;
	}
}
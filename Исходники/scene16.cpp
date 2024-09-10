void sceneHandler16_startLaugh() {
	StaticANIObject *girl = g_fp->_currentScene->getStaticANIObject1ById(ANI_GIRL, -1);

	girl->changeStatics2(ST_GRL_STAND);

	MessageQueue *mq = new MessageQueue(g_fp->_currentScene->getMessageQueueById(QU_SC16_GIRLLAUGH), 0, 1);

	mq->replaceKeyCode(-1, girl->_okeyCode);
	mq->setFlags(mq->getFlags() | 1);
	mq->chain(0);

	g_fp->getGameLoaderGameVar()->getSubVarByName("OBJSTATES")->setSubVarAsInt(sO_DudeSwinged, 0);

	g_vars->scene16_girlIsLaughing = true;
}
void sceneHandler08_badLuck() {
	g_fp->_currentScene->getPictureObjectById(PIC_SC8_LADDER, 0)->_flags &= 0xFFFB;

	g_fp->_aniMan->changeStatics2(ST_MAN8_HANDSUP);
	g_fp->_aniMan->setOXY(376, 280);
	g_fp->_aniMan->_priority = 10;

	MessageQueue *mq = new MessageQueue(g_fp->_globalMessageQueueList->compact());

	ExCommand *ex = new ExCommand(g_fp->_aniMan->_id, 1, MV_MAN8_BADLUCK, 0, 0, 0, 1, 0, 0, 0);
	ex->_excFlags |= 2;
	ex->_keyCode = g_fp->_aniMan->_okeyCode;
	mq->addExCommandToEnd(ex);

	mq->setFlags(mq->getFlags() | 1);
	mq->chain(0);

	g_fp->setObjectState(sO_StairsUp_8, g_fp->getObjectEnumState(sO_StairsUp_8, sO_NotBroken));

	g_vars->scene08_inAir = false;
}
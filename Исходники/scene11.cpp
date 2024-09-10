void sceneHandler11_jumpFromSwing() {
	g_vars->scene11_arcadeIsOn = false;
	g_vars->scene11_hint->_flags &= 0xFFFB;
	g_vars->scene11_scrollIsEnabled = false;

	getCurrSceneSc2MotionController()->activate();
	getGameLoaderInteractionController()->enableFlag24();

	g_vars->scene11_swingOldAngle = 0.0;
	g_vars->scene11_swingAngleDiff = 0.0;
	g_vars->scene11_swingSpeed = 0.0;
	g_vars->scene11_swingAngle = 0.0;

	g_vars->scene11_dudeOnSwing = g_fp->_currentScene->getStaticANIObject1ById(ANI_MAN11, -1);
	g_vars->scene11_dudeOnSwing->_flags &= 0xFFFB;
	g_vars->scene11_dudeOnSwing = g_fp->_currentScene->getStaticANIObject1ById(ANI_KACHELI, -1);
	g_vars->scene11_dudeOnSwing->changeStatics2(ST_KCH_STATIC);
	g_vars->scene11_dudeOnSwing->setOXY(691, 371);
	g_vars->scene11_dudeOnSwing->_priority = 20;
	g_vars->scene11_dudeOnSwing->_flags |= 4;

    MessageQueue *mq = new MessageQueue(g_fp->_globalMessageQueueList->compact());
    ExCommand *ex = new ExCommand(g_fp->_aniMan->_id, 34, 256, 0, 0, 0, 1, 0, 0, 0);
	ex->_field_14 = 256;
	ex->_messageNum = 0;
	ex->_excFlags |= 3;
	mq->addExCommandToEnd(ex);
	mq->setFlags(mq->getFlags() | 1);

	g_fp->_globalMessageQueueList->addMessageQueue(mq);

	g_fp->_aniMan->_flags |= 0x104;
	g_fp->_aniMan->changeStatics2(ST_MAN11_SWING);
	g_fp->_aniMan->setOXY(685, 373);
	g_fp->_aniMan->startAnim(MV_MAN11_JUMPFROMSWING, mq->_id, -1);

	g_fp->_aniMan2 = g_fp->_aniMan;
}
bool sceneHandler25_isOnLadder(ExCommand *cmd) {
	if ((g_fp->_aniMan->_movement && g_fp->_aniMan->_movement->_id == MV_MAN_GOLADDERDOWN)
		|| g_fp->_aniMan->_statics->_staticsId == ST_MAN_GOLADDERD) {
		Interaction *inter = getGameLoaderInteractionController()->getInteractionByObjectIds(PIC_SC25_LADDERDOWN, ANI_MAN, cmd->_keyCode);

		if (!inter)
			return 0;

		MessageQueue *mq = new MessageQueue(inter->_messageQueue, 0, 1);
		PictureObject *pic = g_fp->_currentScene->getPictureObjectById(PIC_SC25_LADDERDOWN, 0);
		Common::Point point;

		point.x = inter->_xOffs + pic->_ox;
		point.y = inter->_yOffs + pic->_oy;

		mq->setFlags(mq->getFlags() | 1);

		sceneHandler25_walkOnLadder(g_fp->_aniMan, &point, mq, 0);

		return true;
	} else {
		return false;
	}
}
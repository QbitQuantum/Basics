bool sceneHandler14_arcadeProcessClick(ExCommand *cmd) {
	if (!getCurrSceneSc2MotionController()->_isEnabled)
		return 0;

	if (!g_vars->scene14_grandmaIsHere) {
		if (!cmd->_keyCode) {
			if (g_vars->scene14_pink) {
				if (g_vars->scene14_pink->_flags & 4) {
					if (cmd->_sceneClickX < g_vars->scene14_pink->_ox + 40) {
						handleObjectInteraction(g_fp->_aniMan, g_vars->scene14_pink, 0);
						cmd->_messageKind = 0;
						return true;
					}
				}
			}
		}
		return false;
	}

	if (getCurrSceneSc2MotionController()->_objtype != kObjTypeMctlCompound)
		return false;

	if (!getCurrSceneSc2MotionController()->_motionControllers[0]->_movGraphReactObj->pointInRegion(cmd->_sceneClickX, cmd->_sceneClickY))
		return false;

	if (cmd->_sceneClickX > 1237)
		return false;

	MessageQueue *mq = getCurrSceneSc2MotionController()->startMove(g_fp->_aniMan, 1237, 451, 1, 0);

	if (!mq)
		return false;

	ExCommand *ex = new ExCommand(0, 17, MSG_SC14_STARTARCADE, 0, 0, 0, 1, 0, 0, 0);

	ex->_excFlags |= 3;
	mq->addExCommandToEnd(ex);
	mq->setFlags(mq->getFlags() | 1);

	postExCommand(g_fp->_aniMan->_id, 2, 1237, 451, 0, -1);

	cmd->_messageKind = 0;

	getCurrSceneSc2MotionController()->deactivate();
	getGameLoaderInteractionController()->disableFlag24();
	return true;
}
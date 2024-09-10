void sceneHandler06_mumsyBallTake() {
	int momAni = 0;

	switch (g_vars->scene06_mumsyNumBalls) {
    case 1:
		momAni = MV_MOM_TAKE1;
		break;
    case 2:
		momAni = MV_MOM_TAKE2;
		break;
    case 3:
		momAni = MV_MOM_TAKE3;
		break;
    case 4:
		momAni = MV_MOM_TAKE4;
		break;
    case 5:
		momAni = MV_MOM_TAKE5;
		break;
	}

	MessageQueue *mq = new MessageQueue(g_fp->_globalMessageQueueList->compact());

	ExCommand *ex = new ExCommand(ANI_MAMASHA, 2, 50, 0, 0, 0, 1, 0, 0, 0);

	ex->_excFlags = 2u;
	mq->addExCommandToEnd(ex);

	if (g_vars->scene06_mumsyNumBalls >= 5) {
		g_fp->setObjectState(sO_BigMumsy, g_fp->getObjectEnumState(sO_BigMumsy, sO_IsGone));

		if (g_fp->getObjectState(sO_ClockAxis) == g_fp->getObjectEnumState(sO_ClockAxis, sO_IsNotAvailable))
			g_fp->setObjectState(sO_ClockAxis, g_fp->getObjectEnumState(sO_ClockAxis, sO_WithoutHandle));

		ex = new ExCommand(ANI_MAMASHA, 1, momAni, 0, 0, 0, 1, 0, 0, 0);
		ex->_excFlags |= 2;
		mq->addExCommandToEnd(ex);

		if (g_vars->scene06_mumsyPos + 3 >= 0) {
			ex = new ExCommand(ANI_MAMASHA, 1, MV_MOM_STARTBK, 0, 0, 0, 1, 0, 0, 0);
			ex->_excFlags |= 2u;
			mq->addExCommandToEnd(ex);

			for (int i = 0; i < g_vars->scene06_mumsyPos + 3; i++) {
				ex = new ExCommand(ANI_MAMASHA, 1, MV_MOM_CYCLEBK, 0, 0, 0, 1, 0, 0, 0);
				ex->_excFlags |= 2;
				mq->addExCommandToEnd(ex);
			}

			ex = new ExCommand(ANI_MAMASHA, 1, MV_MOM_STOPBK, 0, 0, 0, 1, 0, 0, 0);
			ex->_excFlags |= 2;
			mq->addExCommandToEnd(ex);
		}

		ex = new ExCommand(0, 18, QU_MOM_TOLIFT, 0, 0, 0, 1, 0, 0, 0);
		ex->_excFlags |= 3;
		mq->addExCommandToEnd(ex);
	} else {
		if (momAni) {
			ex = new ExCommand(ANI_MAMASHA, 1, momAni, 0, 0, 0, 1, 0, 0, 0);
			ex->_excFlags |= 2;
			mq->addExCommandToEnd(ex);
		}

		if (g_vars->scene06_mumsyPos < 0) {
			for (int i = 0; i > g_vars->scene06_mumsyPos; i--) {
				ex = new ExCommand(ANI_MAMASHA, 1, MV_MOM_JUMPFW, 0, 0, 0, 1, 0, 0, 0);
				ex->_excFlags |= 2;
				mq->addExCommandToEnd(ex);
			}
		} else if (g_vars->scene06_mumsyPos > 0) {
			for (int i = 0; i < g_vars->scene06_mumsyPos; i++) {
				ex = new ExCommand(ANI_MAMASHA, 1, MV_MOM_JUMPBK, 0, 0, 0, 1, 0, 0, 0);
				ex->_excFlags |= 2;
				mq->addExCommandToEnd(ex);
			}
		}

		ex = new ExCommand(0, 18, QU_MOM_SITDOWN, 0, 0, 0, 1, 0, 0, 0);
		ex->_excFlags |= 3u;
		mq->addExCommandToEnd(ex);
	}

	mq->setFlags(mq->getFlags() | 1);
	mq->chain(0);

	g_vars->scene06_mumsyNumBalls = 0;
	g_vars->scene06_arcadeEnabled = false;

	g_fp->_aniMan2 = 0;
}
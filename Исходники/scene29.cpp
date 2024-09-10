void sceneHandler29_manHit() {
	MGMInfo mgminfo;

	g_vars->scene29_var15 = 1;

	g_fp->_aniMan->changeStatics2(ST_MAN29_RUNR);
	g_fp->_aniMan->setOXY(g_vars->scene29_var20, g_vars->scene29_var21);

	mgminfo.ani = g_fp->_aniMan;
	mgminfo.staticsId2 = ST_MAN29_SITR;
	mgminfo.y1 = 463;
	mgminfo.x1 = g_vars->scene29_var20 <= 638 ? 351 : 0;
	mgminfo.field_1C = 10;
	mgminfo.field_10 = 1;
	mgminfo.flags = (g_vars->scene29_var20 <= 638 ? 2 : 0) | 0x44;
	mgminfo.movementId = MV_MAN29_HIT;

	MessageQueue *mq = g_vars->scene29_mgm.genMovement(&mgminfo);
	ExCommand *ex;

	if (mq) {
		if (g_vars->scene29_var20 <= 638) {
			ex = new ExCommand(ANI_MAN, 1, MV_MAN29_STANDUP_NORM, 0, 0, 0, 1, 0, 0, 0);
			ex->_excFlags = 2;
			ex->_keyCode = g_fp->_aniMan->_okeyCode;
			mq->addExCommandToEnd(ex);

			ex = new ExCommand(0, 17, MSG_SC29_STOPRIDE, 0, 0, 0, 1, 0, 0, 0);
			ex->_excFlags = 2;
			mq->addExCommandToEnd(ex);

			g_vars->scene29_var09 = 0;
			g_vars->scene29_var10 = 0;
			g_vars->scene29_var11 = 0;
			g_vars->scene29_var12 = 0;
		} else {
			ex = new ExCommand(ANI_MAN, 1, MV_MAN29_STANDUP, 0, 0, 0, 1, 0, 0, 0);
			ex->_excFlags = 2;
			ex->_keyCode = g_fp->_aniMan->_okeyCode;
			mq->addExCommandToEnd(ex);
		}

		mq->setFlags(mq->getFlags() | 1);

		if (!mq->chain(g_fp->_aniMan))
			delete mq;
	}
}
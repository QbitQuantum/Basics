void sceneHandler27_batLogic() {
    if (g_vars->scene27_balls.size()) {
        g_vars->scene27_bat = g_vars->scene27_balls[0];

        g_vars->scene27_balls.remove_at(0);

        int mv;

        switch (g_vars->scene27_batHandler->_statics->_staticsId) {
        case ST_BTH_5:
            mv = MV_BTH_5_4;
            break;

        case ST_BTH_4:
            mv = MV_BTH_4_3;
            break;

        case ST_BTH_3:
            mv = MV_BTH_3_2;
            break;

        case ST_BTH_2:
            mv = MV_BTH_2_1;
            break;

        case ST_BTH_1:
            mv = MV_BTH_1_0;
            break;

        default:
            chainQueue(QU_SC27_RESTARTBETS, 1);

            getCurrSceneSc2MotionController()->activate();
            getGameLoaderInteractionController()->enableFlag24();

            g_fp->_behaviorManager->setFlagByStaticAniObject(g_fp->_aniMan, 1);

            return;
        }

        MessageQueue *mq = new MessageQueue(g_fp->_globalMessageQueueList->compact());

        mq->setFlags(mq->getFlags() | 1);

        ExCommand *ex = new ExCommand(g_vars->scene27_batHandler->_id, 1, mv, 0, 0, 0, 1, 0, 0, 0);
        ex->_excFlags |= 2;
        mq->addExCommandToEnd(ex);

        ex = new ExCommand(0, 17, MSG_SC27_CLICKBET, 0, 0, 0, 1, 0, 0, 0);
        ex->_excFlags |= 3;
        mq->addExCommandToEnd(ex);

        mq->chain(0);
    } else {
        g_vars->scene27_bat = 0;
    }
}
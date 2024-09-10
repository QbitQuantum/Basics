void sceneHandler35_startFlow() {
    if (g_fp->getObjectState(sO_Valve_35) == g_fp->getObjectEnumState(sO_Valve_35, sO_TurnedOn)) {
        if ((g_vars->scene35_hose->_flags & 4) && g_vars->scene35_hose->_statics->_staticsId == ST_HZE_NORM) {
            g_fp->_behaviorManager->setBehaviorEnabled(g_vars->scene35_bellyInflater, ST_PDV_SMALL, QU_PDV_SML_BLINK, 0);
            g_fp->_behaviorManager->setBehaviorEnabled(g_vars->scene35_bellyInflater, ST_PDV_SMALL, QU_PDV_SML_TRY, 0);

            g_vars->scene35_bellyInflater->changeStatics2(ST_PDV_SMALL);
            g_vars->scene35_bellyInflater->_flags &= 0xFEFF;

            MessageQueue *mq = new MessageQueue(g_fp->_currentScene->getMessageQueueById(QU_SC35_EATHOZE), 0, 0);

            mq->setFlags(mq->getFlags() | 1);

            ExCommand *cmd = new ExCommand(g_vars->scene35_bellyInflater->_id, 34, 256, 0, 0, 0, 1, 0, 0, 0);

            cmd->_excFlags |= 3;
            cmd->_field_14 = 256;
            cmd->_messageNum = 0;

            mq->addExCommandToEnd(cmd);

            if (!mq->chain(g_vars->scene35_bellyInflater))
                delete mq;

            g_vars->scene35_bellyInflater->_flags |= 1;

            getCurrSceneSc2MotionController()->enableLinks(sO_CloseThing, 1);

            g_fp->playSound(SND_35_012, 1);
        } else {
            if (!g_vars->scene35_flowCounter)
                g_vars->scene35_flowCounter = 98;

            g_fp->playSound(SND_35_011, 1);
        }
    }
}
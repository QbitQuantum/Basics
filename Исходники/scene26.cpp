void sceneHandler26_animateVents(StaticANIObject *ani) {
    int qId = 0;

    switch (ani->_okeyCode) {
    case 0:
        if (g_fp->getObjectState(sO_Valve1_26) == g_fp->getObjectEnumState(sO_Valve1_26, sO_Closed))
            qId = QU_SC26_OPEN1;
        else
            qId = QU_SC26_CLOSE1;

        break;

    case 1:
        if (g_fp->getObjectState(sO_Valve2_26) == g_fp->getObjectEnumState(sO_Valve2_26, sO_Closed))
            qId = QU_SC26_OPEN2;
        else
            qId = QU_SC26_CLOSE2;

        break;

    case 2:
        if (g_fp->getObjectState(sO_Valve3_26) == g_fp->getObjectEnumState(sO_Valve3_26, sO_Closed))
            qId = QU_SC26_OPEN3;
        else
            qId = QU_SC26_CLOSE3;

        break;

    case 3:
        if (g_fp->getObjectState(sO_Valve4_26) == g_fp->getObjectEnumState(sO_Valve4_26, sO_Closed))
            qId = QU_SC26_OPEN4;
        else
            qId = QU_SC26_CLOSE4;

        break;

    case 4:
        if (g_fp->getObjectState(sO_Valve5_26) == g_fp->getObjectEnumState(sO_Valve5_26, sO_Closed))
            qId = QU_SC26_OPEN5;
        else
            qId = QU_SC26_CLOSE5;

        break;

    default:
        return;
    }

    if (qId) {
        MessageQueue *mq = g_fp->_currentScene->getMessageQueueById(qId);

        mq->setFlags(mq->getFlags() | 1);
        mq->chain(0);
    }
}
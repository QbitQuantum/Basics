// the Main loop
PRIVATE void vProcessSnsObj_TSL2561(void *pvObj, teEvent eEvent) {
    tsSnsObj *pSnsObj = (tsSnsObj *)pvObj;
    tsObjData_TSL2561 *pObj = (tsObjData_TSL2561 *)pSnsObj->pvData;

    // general process (independent from each state)
    switch (eEvent) {
    case E_EVENT_TICK_TIMER:
        if (pObj->u8TickCount < 100) {
            pObj->u8TickCount += pSnsObj->u8TickDelta;
#ifdef SERIAL_DEBUG
            vfPrintf(&sDebugStream, "+");
#endif
        }
        break;
    case E_EVENT_START_UP:
        pObj->u8TickCount = 100; // expire immediately
#ifdef SERIAL_DEBUG
        vfPrintf(&sDebugStream, "\n\rTSL2561 WAKEUP");
#endif
        break;
    default:
        break;
    }

    // state machine
    switch(pSnsObj->u8State)
    {
    case E_SNSOBJ_STATE_INACTIVE:
        // do nothing until E_ORDER_INITIALIZE event
        break;

    case E_SNSOBJ_STATE_IDLE:
        switch (eEvent) {
        case E_EVENT_NEW_STATE:
            break;

        case E_ORDER_KICK:
            vSnsObj_NewState(pSnsObj, E_SNSOBJ_STATE_MEASURING);

#ifdef SERIAL_DEBUG
            vfPrintf(&sDebugStream, "\n\rTSL2561 KICKED");
#endif

            break;

        default:
            break;
        }
        break;

    case E_SNSOBJ_STATE_MEASURING:
        switch (eEvent) {
        case E_EVENT_NEW_STATE:
            pObj->u32Result = SENSOR_TAG_DATA_ERROR;
            pObj->u8TickWait = TSL2561_CONVTIME;

            pObj->bBusy = TRUE;
#ifdef TSL2561_ALWAYS_RESET
            u8reset_flag = TRUE;
            if (!bTSL2561reset(TURE)) {
                vSnsObj_NewState(pSnsObj, E_SNSOBJ_STATE_COMPLETE);
            }
#else
            if (!bTSL2561startRead()) { // kick I2C communication
                vSnsObj_NewState(pSnsObj, E_SNSOBJ_STATE_COMPLETE);
            }
#endif
            pObj->u8TickCount = 0;
            break;

        default:
            break;
        }

        // wait until completion
        if (pObj->u8TickCount > pObj->u8TickWait) {
#ifdef TSL2561_ALWAYS_RESET
            if (u8reset_flag) {
                u8reset_flag = 0;
                if (!bTSL2561startRead()) {
                    vTSL2561_new_state(pObj, E_SNSOBJ_STATE_COMPLETE);
                }

                pObj->u8TickCount = 0;
                pObj->u8TickWait = TSL2561_CONVTIME;
                break;
            }
#endif
            pObj->u32Result = u32TSL2561readResult();

            // data arrival
            pObj->bBusy = FALSE;
            vSnsObj_NewState(pSnsObj, E_SNSOBJ_STATE_COMPLETE);
        }
        break;

    case E_SNSOBJ_STATE_COMPLETE:
        switch (eEvent) {
        case E_EVENT_NEW_STATE:
#ifdef SERIAL_DEBUG
            vfPrintf(&sDebugStream, "\n\rTSL2561_CP: %d", pObj->i16Result);
#endif

            break;

        case E_ORDER_KICK:
            // back to IDLE state
            vSnsObj_NewState(pSnsObj, E_SNSOBJ_STATE_IDLE);
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}
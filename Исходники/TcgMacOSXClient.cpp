static TCGvoid EngineHandleCmd(struct android_app* app, TCGint cmd)
{
    struct Engine* engine = (struct Engine*)app->userData;
    switch (cmd)
    {
    case APP_CMD_SAVE_STATE:
        // The system has asked us to save our current state.  Do so.
        engine->app->savedState = TCG_MALLOC(sizeof(struct SavedState), eTCG_MAIN);
        *((struct SavedState*)engine->app->savedState) = engine->state;
        engine->app->savedStateSize = sizeof(struct SavedState);
        break;

    case APP_CMD_INIT_WINDOW:
        //窗口初始化
        _Lock.Lock();
        g_bWindowMax = TCG_TRUE;
        _Lock.UnLock();
        
        if (engine->app->window != NULL)
        {
            g_WindowType = engine->app->window;
        }
        break;

    case APP_CMD_TERM_WINDOW:
        //窗口销毁
        _Lock.Lock();
        g_bWindowMax = TCG_FALSE;
        _Lock.UnLock();
        break;

    case APP_CMD_GAINED_FOCUS:
        // When our app gains focus, we start monitoring the accelerometer.
        if (engine->accelerometerSensor != NULL)
        {
            ASensorEventQueue_enableSensor(engine->sensorEventQueue,
                    engine->accelerometerSensor);
            // We'd like to get 60 events per second (in us).
            ASensorEventQueue_setEventRate(engine->sensorEventQueue,
                    engine->accelerometerSensor, (1000L/60)*1000);
        }
        break;

    case APP_CMD_LOST_FOCUS:
        // When our app loses focus, we stop monitoring the accelerometer.
        // This is to avoid consuming battery while not being used.
        if (engine->accelerometerSensor != NULL)
        {
            ASensorEventQueue_disableSensor(engine->sensorEventQueue,
                    engine->accelerometerSensor);
        }
        // Also stop animating.
        engine->animating = 0;
        break;

    default:
        break;
    }
}
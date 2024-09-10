void Activity::handleCmd(int32_t cmd)
{
    switch (cmd)
    {
        case APP_CMD_SAVE_STATE:
            LOGGER.logf(LOG_DEBUG, "APP_CMD_SAVE_STATE");
            break;

        case APP_CMD_CONFIG_CHANGED:
            LOGGER.logf(LOG_DEBUG, "APP_CMD_CONFIG_CHANGED");
            break;

        case APP_CMD_INIT_WINDOW:
            LOGGER.logf(LOG_DEBUG, "APP_CMD_INIT_WINDOW");
            if (androidApp->window != nullptr)
            {
                window->init();
                app->init(window->getSize());
            }
            break;

        case APP_CMD_TERM_WINDOW:
            LOGGER.logf(LOG_DEBUG, "APP_CMD_TERM_WINDOW");
            window->destroy();
            app->destroy();
            break;

        case APP_CMD_START:
            LOGGER.logf(LOG_DEBUG, "APP_CMD_START");
            break;

        case APP_CMD_RESUME:
            LOGGER.logf(LOG_DEBUG, "APP_CMD_RESUME");
            resumed = true;
            app->resume();
            break;

        case APP_CMD_PAUSE:
            LOGGER.logf(LOG_DEBUG, "APP_CMD_PAUSE");
            resumed = false;
            app->pause();
            break;

        case APP_CMD_STOP:
            LOGGER.logf(LOG_DEBUG, "APP_CMD_STOP");
            break;

        case APP_CMD_DESTROY:
            LOGGER.logf(LOG_DEBUG, "APP_CMD_DESTROY");
            break;

        case APP_CMD_GAINED_FOCUS:
            LOGGER.logf(LOG_DEBUG, "APP_CMD_GAINED_FOCUS");
            hasFocus = true;
            break;

        case APP_CMD_LOST_FOCUS:
            LOGGER.logf(LOG_DEBUG, "APP_CMD_LOST_FOCUS");
            hasFocus = false;
            break;
    }
}
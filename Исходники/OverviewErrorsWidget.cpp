void OverviewErrorsWidget::SetVisible(bool pVisible)
{
	CONF.SetVisibilityErrorsWidget(pVisible);
    if (pVisible)
    {
        move(mWinPos);
        show();
        LOGGER.RegisterLogSink(this);
        mTimerId = startTimer(VIEW_ERROR_LOG_UPDATE_PERIOD);
    }else
    {
        if (mTimerId != -1)
            killTimer(mTimerId);
        mWinPos = pos();
        hide();
        LOGGER.UnregisterLogSink(this);
    }
}
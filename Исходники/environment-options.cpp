void EnvironmentOptions::ParseEnvironmentOptions()
{
    // get logging options
    mFpsFrequency = GetIntegerEnvironmentVariable( DALI_ENV_FPS_TRACKING, 0 );
    mUpdateStatusFrequency = GetIntegerEnvironmentVariable( DALI_ENV_UPDATE_STATUS_INTERVAL, 0 );
    mObjectProfilerInterval = GetIntegerEnvironmentVariable( DALI_ENV_OBJECT_PROFILER_INTERVAL, 0 );
    mPerformanceStatsLevel = GetIntegerEnvironmentVariable( DALI_ENV_LOG_PERFORMANCE_STATS, 0 );
    mPerformanceStatsFrequency = GetIntegerEnvironmentVariable( DALI_ENV_LOG_PERFORMANCE_STATS_FREQUENCY, 0 );
    mPerformanceTimeStampOutput = GetIntegerEnvironmentVariable( DALI_ENV_PERFORMANCE_TIMESTAMP_OUTPUT, 0 );
    mNetworkControl = GetIntegerEnvironmentVariable( DALI_ENV_NETWORK_CONTROL, 0 );
    mPanGestureLoggingLevel = GetIntegerEnvironmentVariable( DALI_ENV_LOG_PAN_GESTURE, 0 );

    int predictionMode;
    if( GetIntegerEnvironmentVariable(DALI_ENV_PAN_PREDICTION_MODE, predictionMode) )
    {
        mPanGesturePredictionMode = predictionMode;
    }
    int predictionAmount(-1);
    if( GetIntegerEnvironmentVariable(DALI_ENV_PAN_PREDICTION_AMOUNT, predictionAmount) )
    {
        if( predictionAmount < 0 )
        {
            // do not support times in the past
            predictionAmount = 0;
        }
        mPanGesturePredictionAmount = predictionAmount;
    }
    int minPredictionAmount(-1);
    if( GetIntegerEnvironmentVariable(DALI_ENV_PAN_MIN_PREDICTION_AMOUNT, minPredictionAmount) )
    {
        if( minPredictionAmount < 0 )
        {
            // do not support times in the past
            minPredictionAmount = 0;
        }
        mPanGestureMinPredictionAmount = minPredictionAmount;
    }
    int maxPredictionAmount(-1);
    if( GetIntegerEnvironmentVariable(DALI_ENV_PAN_MAX_PREDICTION_AMOUNT, maxPredictionAmount) )
    {
        if( minPredictionAmount > -1 && maxPredictionAmount < minPredictionAmount )
        {
            // maximum amount should not be smaller than minimum amount
            maxPredictionAmount = minPredictionAmount;
        }
        mPanGestureMaxPredictionAmount = maxPredictionAmount;
    }
    int predictionAmountAdjustment(-1);
    if( GetIntegerEnvironmentVariable(DALI_ENV_PAN_PREDICTION_AMOUNT_ADJUSTMENT, predictionAmountAdjustment) )
    {
        if( predictionAmountAdjustment < 0 )
        {
            // negative amount doesn't make sense
            predictionAmountAdjustment = 0;
        }
        mPanGesturePredictionAmountAdjustment = predictionAmountAdjustment;
    }
    int smoothingMode;
    if( GetIntegerEnvironmentVariable(DALI_ENV_PAN_SMOOTHING_MODE, smoothingMode) )
    {
        mPanGestureSmoothingMode = smoothingMode;
    }
    float smoothingAmount = 1.0f;
    if( GetFloatEnvironmentVariable(DALI_ENV_PAN_SMOOTHING_AMOUNT, smoothingAmount) )
    {
        smoothingAmount = Clamp(smoothingAmount, 0.0f, 1.0f);
        mPanGestureSmoothingAmount = smoothingAmount;
    }

    int minimumDistance(-1);
    if ( GetIntegerEnvironmentVariable(DALI_ENV_PAN_MINIMUM_DISTANCE, minimumDistance ))
    {
        mPanMinimumDistance = minimumDistance;
    }

    int minimumEvents(-1);
    if ( GetIntegerEnvironmentVariable(DALI_ENV_PAN_MINIMUM_EVENTS, minimumEvents ))
    {
        mPanMinimumEvents = minimumEvents;
    }

    int glesCallTime(0);
    if ( GetIntegerEnvironmentVariable(DALI_GLES_CALL_TIME, glesCallTime ))
    {
        mGlesCallTime = glesCallTime;
    }

    int windowWidth(0), windowHeight(0);
    if ( GetIntegerEnvironmentVariable( DALI_WINDOW_WIDTH, windowWidth ) && GetIntegerEnvironmentVariable( DALI_WINDOW_HEIGHT, windowHeight ) )
    {
        mWindowWidth = windowWidth;
        mWindowHeight = windowHeight;
    }

    const char * windowName = GetCharEnvironmentVariable( DALI_WINDOW_NAME );
    if ( windowName )
    {
        mWindowName = windowName;
    }

    const char * windowClassName = GetCharEnvironmentVariable( DALI_WINDOW_CLASS_NAME );
    if ( windowClassName )
    {
        mWindowClassName = windowClassName;
    }
}
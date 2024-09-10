void LatencyTest::BeginTest()
{
     if (State == State_WaitingForButton)
    {
        // Set color to black and wait a while.
        RenderColor = CALIBRATE_BLACK;

        State = State_WaitingForSettlePreCalibrationColorBlack;
        OVR_DEBUG_LOG(("State_WaitingForButton -> State_WaitingForSettlePreCalibrationColorBlack."));

        setTimer(TIME_TO_WAIT_FOR_SETTLE_PRE_CALIBRATION);
    }
}
/**
 * @private
 * Computes the next value of the pid.
 * @param instructionIndex the pid that we want to compute (0 = alpha, 1 = theta)
 * @param pidType the type of pid that we want to compute (between 0 and PID_TYPE_COUNT)
 * @param currentPosition the current position of the wheels (either alphaPosition, either thetaPosition)
 * @param time the time in pid sampling
 */
float computeNextPID(int instructionIndex, MotionInstruction* motionInstruction, Motion* motion, MotionError* motionError, float time) {
    unsigned char rollingTestMode = getRollingTestMode();
	unsigned char pidType = motionInstruction->pidType;
	float currentPosition = motion->position;

    // instructionIndex = Alpha / Theta
    // pidType = Forward / Rotation / Final Approach ...
    unsigned pidIndex = getIndexOfPid(instructionIndex, pidType);
    Pid* pid = getPID(pidIndex, rollingTestMode);

    if (!pid->enabled) {
        return 0.0f;
    }

    float normalPosition = computeNormalPosition(motionInstruction, time);
    float normalSpeed = computeNormalSpeed(motionInstruction, time);

	float positionError = normalPosition - currentPosition;
    float result = computePidCorrection(motionError, pid, normalSpeed, positionError);

    return result;
}
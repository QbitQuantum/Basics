void statusTask(void) {
    static time_t last = 100; // Don't begin immediately
    static uint32_t lastDuration = 0;
    if (((getSystemTime() - last) >= STATUSDELAY) && (!(state & STATE_OUTPUT))) {
        last = getSystemTime();
        printf("p%.2f %.2f %.2f\n", orientation.vPitch, orientation.vRoll, orientation.vYaw);
        printf("q%li %li\n", sumFlightTask / countFlightTask, lastDuration);
        printf("r%.2f %.2f\n", pidStates[0].intMin, pidStates[0].intMax);
        printf("s%.2f %.2f\n", pidStates[0].outMin, pidStates[0].outMax);
        printf("t%.3f %.3f %.3f\n", pidStates[0].kp, pidStates[0].ki, pidStates[0].kd);
        printf("u%.2f %.2f\n", pidOutput[PITCH], pidOutput[ROLL]);
        printf("v%i %i %i %i\n", motorSpeed[0], motorSpeed[1], motorSpeed[2], motorSpeed[3]);
        printf("w%.2f\n", orientation.pitch);
        printf("x%.2f\n", orientation.roll);
        printf("y%.2f\n", orientation.yaw);
        printf("z%.2f\n", getVoltage());
        lastDuration = getSystemTime() - last;
    }
}
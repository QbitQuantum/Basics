void ledTask(void) {
    /*
     * Basic example of executing a task with a given frequency.
     * last contains the last time this task was executed.
     */
    static time_t last = 0;
    if ((getSystemTime() - last) > 125) { // 125ms have passed
        xyLed(LED_ALL, LED_TOGGLE); // Do something...
        last = getSystemTime(); // Store new execution time
    }
}
/** Initializes all global variables and prepares global log file output.
 * @see TestLogger_t#runnerStarted()}
 */
static void runnerStarted() {
    globalFile = fopen(GLOBAL_FILE_NAME, "w");
    fprintf(globalFile, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
    fprintf(globalFile, "<testsuites>\n");
    fflush(globalFile);
    globalInfo.hostname = getHostname();
    globalInfo.suiteId = 0;
}
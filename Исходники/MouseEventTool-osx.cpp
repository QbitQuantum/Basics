void MouseEventTool::getMainWindowNumber() {
    pid_t pid = getPid();

    if (windowNumber_ == NULL) {
        // Get the windowNumber of the main window
        CFArrayRef windows = CGWindowListCopyWindowInfo(kCGWindowListOptionOnScreenOnly | kCGWindowListExcludeDesktopElements, kCGNullWindowID);
        for (int i = 0; i < CFArrayGetCount(windows); ++i) {
            CFDictionaryRef windInfo = (CFDictionaryRef) CFArrayGetValueAtIndex(windows, i);

            // We'll know if it's this process because it has the same PID as us, and it's got a name.
            int windowPid;
            CFNumberRef windowPidRef = (CFNumberRef) CFDictionaryGetValue(windInfo, kCGWindowOwnerPID);
            CFNumberGetValue(windowPidRef, kCFNumberIntType, &windowPid);
            if (windowPid == pid) {                CFStringRef windName;
                bool val = CFDictionaryGetValueIfPresent(windInfo, kCGWindowName, (const void**) &windName);
                if (val) {
                    // Store the window number so it's easier to do searches in the future.
                    CFNumberRef windNum = (CFNumberRef) CFDictionaryGetValue(windInfo, kCGWindowNumber);
                    windowNumber_ = windNum;
                    break;
                }
            }
        }
    }
}
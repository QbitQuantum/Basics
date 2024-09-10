void KeyPresser::sendKeys(int numKeys, int keys[MAX_KEYS]) {
    int i;
    for (i=0; i<numKeys; i++) {
        input.ki.wVk = keys[i];
        input.ki.dwFlags = KEYPRESS;
        SendInput(1, &input, sizeof(INPUT));
    }
    for (i=numKeys-1; i>=0; i--) {
        input.ki.wVk = keys[i];
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));
    }
}
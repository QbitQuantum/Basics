int main() {
    int i, slot, mtoggle = 0;
    MSG msg = {0};
    HWND window_handles[10];
    RECT window_rect;

    // Register hotkeys 0-9
    for (i = 0; i < 10; i++) {
        if (RegisterHotKey(NULL, i, MOD_ALT, 0x30 + i) == TRUE) {
            printf("Registering Alt+%d as hotkey\n", i);
        } else {
            printf("Failed to register Alt+%d as hotkey\n", i);
            return 1;
        }
        if (RegisterHotKey(NULL, 10 + i, MOD_SHIFT | MOD_ALT, 0x30 + i) == TRUE) {
            printf("Registering Alt+Shift+%d as hotkey\n", i);
        } else {
            printf("Failed to register Alt+Shift+%d as hotkey\n", i);
            return 1;
        }
        window_handles[i] = 0;
    }

    if (RegisterHotKey(NULL, 20, MOD_SHIFT | MOD_ALT, 0x30 + 0x1D) == TRUE) {
        printf("Registered Alt+Shift+M as mouse toggle hotkey\n");
    }

    while (GetMessage(&msg, NULL, 0, 0) != 0) {
        if (msg.message == WM_HOTKEY) {
            slot = (msg.lParam >> 16) - 0x30;
            if (slot == 0x1D) { // Mouse toggle hotkey
                printf("Mouse centering %sabled.\n", mtoggle ? "dis" : "en");
                mtoggle = !mtoggle;
                continue;
            }
            if (msg.lParam & MOD_SHIFT) { /* Shift is pressed, register this window */
                window_handles[slot] = GetForegroundWindow();
                printf("Slot %d: Registering window %d\n", slot, window_handles[slot]);
            } else { /* Shift is not pressed, show this window */
                if (window_handles[slot] == 0) {
                    printf("Slot %d: Cannot show - no window registered\n", slot);
                } else {
                    SetForegroundWindow(window_handles[slot]);
                    if (mtoggle) {
                        ZeroMemory(&window_rect, sizeof(RECT));
                        if (GetWindowRect(window_handles[slot], &window_rect) == FALSE) {
                            printf("Could not get window dimensions.\n");
                            continue;
                        }
                        if (SetCursorPos((window_rect.left + window_rect.right)/2,
                                         (window_rect.top + window_rect.bottom)/2) == FALSE) {
                            printf("Could not set cursor position.\n");
                            continue;
                        }
                    }
                    printf("Slot %d: Showing window %d\n", slot, window_handles[slot]);
                }
            }
        }
    }
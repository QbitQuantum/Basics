int get_connected_state() {
    DWORD flags;
    return IsNetworkAlive(&flags)?CONNECTED_STATE_CONNECTED:CONNECTED_STATE_NOT_CONNECTED;
}
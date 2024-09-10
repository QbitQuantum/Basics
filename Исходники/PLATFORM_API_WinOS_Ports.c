INT32 PORT_GetPortMixerCount() {
    return (INT32) mixerGetNumDevs();
}
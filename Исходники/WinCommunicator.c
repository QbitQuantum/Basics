JNIEXPORT void JNICALL Java_imageembedder_WinSettings_broadcastChange(JNIEnv * env, jobject obj){
    char filepath[225];
    //SystemParametersInfo(SPI_GETDESKWALLPAPER, sizeof (filepath) - 1, filepath, SPIF_SENDCHANGE);
    SendNotifyMessageA()
    SendNotifyMessage(HWND_BROADCAST);
}
JNIEXPORT void JNICALL
Java_sun_print_Win32PrintServiceLookup_notifyClosePrinterChange(JNIEnv *env,
                                                                jobject peer,
                                                                jlong chgObject) {
    FindClosePrinterChangeNotification((HANDLE)chgObject);
}
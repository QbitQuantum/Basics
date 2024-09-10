/*
 * Create an add-image process that can later be run with specific inputs
 * @return the pointer to the process
 * @param env pointer to java environment this was called from
 * @partam caseHandle pointer to case to add image to
 * @param timezone timezone for the image
 */
JNIEXPORT jlong JNICALL
    Java_org_sleuthkit_datamodel_SleuthkitJNI_initAddImgNat(JNIEnv * env,
    jclass obj, jlong caseHandle, jstring timezone) {
    jboolean isCopy;

    TskCaseDb *tskCase = castCaseDb(env, caseHandle);

    char envstr[32];
    snprintf(envstr, 32, "TZ=%s", env->GetStringUTFChars(timezone,
            &isCopy));
    if (0 != putenv(envstr)) {
        throwTskError(env, "Error setting timezone environment");
        return 1;
    }

    /* we should be checking this somehow */
    TZSET();
    TskAutoDb *tskAuto = tskCase->initAddImage();
    return (jlong) tskAuto;
}
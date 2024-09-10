JNIEXPORT void JNICALL Java_org_opencv_video_BackgroundSubtractor_apply_11
  (JNIEnv* env, jclass , jlong self, jlong image_nativeObj, jlong fgmask_nativeObj)
{
    try {
        LOGD("video::apply_11()");
        BackgroundSubtractor* me = (BackgroundSubtractor*) self; //TODO: check for NULL
        Mat& image = *((Mat*)image_nativeObj);
        Mat& fgmask = *((Mat*)fgmask_nativeObj);
        me->operator ()( image, fgmask );
        return;
    } catch(cv::Exception e) {
        LOGD("video::apply_11() catched cv::Exception: %s", e.what());
        jclass je = env->FindClass("org/opencv/core/CvException");
        if(!je) je = env->FindClass("java/lang/Exception");
        env->ThrowNew(je, e.what());
        return;
    } catch (...) {
        LOGD("video::apply_11() catched unknown exception (...)");
        jclass je = env->FindClass("java/lang/Exception");
        env->ThrowNew(je, "Unknown exception in JNI code {video::apply_11()}");
        return;
    }
}
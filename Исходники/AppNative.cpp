void hide_ads (void)
{
    // Get the android application's activity.
    ANativeActivity* activity = gEngine.app->activity;
    JavaVM* jvm = activity->vm;

    JNIEnv* env = NULL;
    DTboolean needs_detach = false;
    int env_stat = jvm->GetEnv( (void**) &env, JNI_VERSION_1_6);
    if (env_stat == JNI_EDETACHED) {
        jvm->AttachCurrentThread(&env, 0);
        needs_detach = true;
    }
    ASSERT(env);

    jclass c_activity = env->GetObjectClass(activity->clazz);
    ASSERT(c_activity);
    jmethodID m_hide_ad_popup = env->GetMethodID(c_activity, "hideAdPopup", "()V");
    ASSERT(m_hide_ad_popup);

    env->CallVoidMethod(activity->clazz, m_hide_ad_popup);

    if (needs_detach)
        jvm->DetachCurrentThread();
}
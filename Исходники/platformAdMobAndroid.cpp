void platform_adMobShow(loom_adMobHandle handle)
{
    gShowMethodInfo.getEnv()->CallStaticVoidMethod(gShowMethodInfo.classID, gShowMethodInfo.methodID, (jint)handle);
}
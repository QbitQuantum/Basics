void MI_CALL L_LifecycleC1_Unload(
    L_LifecycleC1_Self* self,
    MI_Context* context)
{
    CHKMIRESULTPOST(lifecycle_StopThread(&cfgL_LifecycleC1), "L_LifecycleC1_Unload");
    CHKMIRESULTPOST(lifecycle_Unload(&cfgL_LifecycleC1), "lifecycle_Unload(L_LifecycleC1)");
    CHKMIRESULTPOST(class_Unload((void*)self, &cfgL_LifecycleC1), "L_LifecycleC1_Unload");
    if (cfgL_LifecycleC1.lifecycleInstance)
    {
        MI_Instance_Delete( cfgL_LifecycleC1.lifecycleInstance );
        cfgL_LifecycleC1.lifecycleInstance = NULL;
    }
    MI_PostResult(context, MI_RESULT_OK);
}
JNIEXPORT jobject JNICALL Java_com_mousebird_maply_Matrix3d_inverse
(JNIEnv *env, jobject obj)
{
    try
    {
        Matrix3dClassInfo *classInfo = Matrix3dClassInfo::getClassInfo();
        Matrix3d *inst = classInfo->getObject(env,obj);
        if (!inst)
            return NULL;
        
        Matrix3d matInv = inst->inverse();
        return MakeMatrix3d(env,matInv);
    }
    catch (...)
    {
        __android_log_print(ANDROID_LOG_VERBOSE, "Maply", "Crash in Matrix3d::inverse()");
    }
    
    return NULL;
}
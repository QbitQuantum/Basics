static void android_view_RenderNode_getInverseTransformMatrix(JNIEnv* env,
        jobject clazz, jlong renderNodePtr, jlong outMatrixPtr) {
    // load transform matrix
    android_view_RenderNode_getTransformMatrix(env, clazz, renderNodePtr, outMatrixPtr);
    SkMatrix* outMatrix = reinterpret_cast<SkMatrix*>(outMatrixPtr);

    // return it inverted
    if (!outMatrix->invert(outMatrix)) {
        // failed to load inverse, pass back identity
        outMatrix->setIdentity();
    }
}
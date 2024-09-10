IFACEMETHODIMP AccessibleSelectionProvider::GetSelection(SAFEARRAY **pRetVal) {
    LOG("In AccessibleSelectionProvider::GetSelection\n");
    LOG("  this: %p\n", this);
    if (pRetVal == NULL)
        return E_INVALIDARG;
    JNIEnv* env = GetEnv();
    jlongArray selectedElements = static_cast<jlongArray>(env->CallObjectMethod(m_self, midGetSelection));
    if( selectedElements == NULL )
        return S_OK;
    jint size = env->GetArrayLength(selectedElements);
    if (size != 0) {
        //LOG("  size: %d\n", size);
        jlong* selectedElementsPatterns = env->GetLongArrayElements(selectedElements, JNI_FALSE);
        SAFEARRAY *psaElements = SafeArrayCreateVector(VT_I4, 0, size);
        if (psaElements == NULL) {
            return E_OUTOFMEMORY;
        }
        for (LONG idx = 0; idx < size; idx++) {
            LOG("  idx: %d\n", idx);
            LOG("  selectedElements: %p\n", reinterpret_cast<void*>(jlong_to_ptr(selectedElementsPatterns[idx])) );
            SafeArrayPutElement(psaElements, &idx, (void*)(jlong_to_ptr(selectedElementsPatterns[idx])));
        }
        env->ReleaseLongArrayElements(selectedElements, selectedElementsPatterns, JNI_FALSE);
        *pRetVal = psaElements;
    } else 
        LOG("AccessibleSelectionProvider size=%d\n" , size);
    return S_OK;
}
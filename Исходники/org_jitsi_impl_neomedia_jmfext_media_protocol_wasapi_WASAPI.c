JNIEXPORT jlong JNICALL
Java_org_jitsi_impl_neomedia_jmfext_media_protocol_wasapi_WASAPI_PSPropertyKeyFromString
    (JNIEnv *env, jclass clazz, jstring pszString)
{
    const jchar *pszString_ = (*env)->GetStringChars(env, pszString, NULL);
    PROPERTYKEY *pkey;

    if (pszString_)
    {
        HRESULT hr;

        pkey = CoTaskMemAlloc(sizeof(PROPERTYKEY));
        if (pkey)
        {
            hr = PSPropertyKeyFromString((LPCWSTR) pszString_, pkey);
            if (FAILED(hr))
            {
                CoTaskMemFree(pkey);
                pkey = NULL;
            }
        }
        else
            hr = E_OUTOFMEMORY;
        (*env)->ReleaseStringChars(env, pszString, pszString_);
        if (FAILED(hr))
            WASAPI_throwNewHResultException(env, hr, __func__, __LINE__);
    }
    else
        pkey = NULL;
    return (jlong) (intptr_t) pkey;
}
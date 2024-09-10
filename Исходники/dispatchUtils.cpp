HRESULT JNICALL GetRunningActiveObject
  (JNIEnv * env, jclass clazz, jstring clsid, IDispatch ** ppDisp)
{
   // jstring to char
   const char * utfChars = env->GetStringUTFChars( clsid, NULL );
   UBSTR lpsz(utfChars);
   env->ReleaseStringUTFChars(clsid, utfChars);

   // wchar_t to CLSID
   GUID guid;
   HRESULT hr = CLSIDFromString( lpsz, &guid );
   if ( FAILED( hr ) ) {
      //ThrowComException( env, hr, "CLSIDFromString(...) FAILED!" );
      //return hr;

      //WINOLEAPI CLSIDFromProgID (IN LPCOLESTR lpszProgID, OUT LPCLSID lpclsid);
      hr = CLSIDFromProgID( lpsz, &guid );
      if ( FAILED( hr ) ) {
         ThrowComException( env, hr, "CLSIDFromString/CLSIDFromProgID(...) FAILED!" );
         return hr;
      }

   }

   IUnknown * pItf = 0;
   hr = GetActiveObject( guid, 0, &pItf );
   if ( FAILED( hr ) ) {
      return hr;
   }

   //*ppDisp = 0;
   hr = pItf->QueryInterface(IID_IDispatch, (void**)ppDisp);
   pItf->Release();

   return hr;

}
OsStatus sipXmediaFactoryImpl::buildCodecFactory(SdpCodecList* pFactory, 
                                                 const UtlString& sAudioPreferences,
                                                 const UtlString& sVideoPreferences,
                                                 int videoFormat,
                                                 int* iRejected)
{
   OsStatus rc = OS_FAILED;

   *iRejected = 0;

   if (pFactory)
   {
      pFactory->clearCodecs();

      // If preferred codecs supplied - add them, else add all supported
      // codecs.
      if (sAudioPreferences.length() > 0)
      {
         *iRejected = pFactory->addCodecs(sAudioPreferences);
         OsSysLog::add(FAC_MP, PRI_DEBUG, 
                       "sipXmediaFactoryImpl::buildCodecFactory: "
                       "supported codecs = %s with NumReject %d",
                       sAudioPreferences.data(), *iRejected);
         rc = OS_SUCCESS;
      }
      else
      {
         // Build up the supported codecs
         MpCodecFactory *pCodecFactory = MpCodecFactory::getMpCodecFactory();
         pCodecFactory->addCodecsToList(*pFactory);

         *iRejected = 0;
         rc = OS_SUCCESS;
      }

#ifdef VIDEO // [
      // If preferred codecs supplied - add them, else add all supported
      // codecs.
      if (sVideoPreferences.length() > 0)
      {
         *iRejected = pFactory->addCodecs(sVideoPreferences);
         OsSysLog::add(FAC_MP, PRI_DEBUG, 
                       "sipXmediaFactoryImpl::buildCodecFactory: "
                       "supported codecs = %s with NumReject %d",
                       sVideoPreferences.data(), *iRejected);
         rc = OS_SUCCESS;
      }
      else
      {
         // Build up the supported codecs
         SdpCodec::SdpCodecTypes videoCodecs[] = {};
         const int numVideoCodecs = sizeof(videoCodecs)/sizeof(SdpCodec::SdpCodecTypes);

         *iRejected = pFactory->addCodecs(numVideoCodecs, videoCodecs);
         rc = OS_SUCCESS;
      }
#endif // VIDEO ]
   }
   return rc;
}
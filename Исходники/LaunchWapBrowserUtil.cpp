TBool
LaunchWapBrowserUtil::LaunchWapBrowser(const TDesC& aUrl)
{
#if defined NAV2_CLIENT_SERIES60_V2 || defined NAV2_CLIENT_SERIES60_V3
   TInt urlLen = aUrl.Length();
   HBufC* fixedUrl;

   if (KFourHttpString().Compare(aUrl.Left(KFourHttpString().Length()))) {
      /* Not 4 http:// at the beginning. */

      if (KHttpString().Compare(aUrl.Left(KHttpString().Length()))) {
         /* Not http:// at the beginning. */
         urlLen += KFourHttpString().Length() + 1;
         fixedUrl = HBufC::NewLC(urlLen);
         fixedUrl->Des().Copy(KFourHttpString);
      } else {
         urlLen += KFourString().Length() + 1;
         fixedUrl = HBufC::NewLC(urlLen);
         fixedUrl->Des().Copy(KFourString);
      }
      fixedUrl->Des().Append(aUrl);
   } else {
      fixedUrl = aUrl.AllocLC();
   }

   RApaLsSession aApaLsSession;

   TUid id( KPhoneUidWmlBrowser );
   TApaTaskList taskList( CEikonEnv::Static()->WsSession() );
   TApaTask task = taskList.FindApp( id );

   if ( task.Exists() ) {
      HBufC8* param8 = HBufC8::NewLC( fixedUrl->Length() );
      param8->Des().Append( *fixedUrl );
      task.SendMessage( TUid::Uid( 0 ), *param8 ); // UID is not used
      CleanupStack::PopAndDestroy( param8 );
   } else {
      if ( !aApaLsSession.Handle() )
      {
         User::LeaveIfError( aApaLsSession.Connect() );
      }
      TThreadId thread;
      User::LeaveIfError( aApaLsSession.StartDocument( *fixedUrl,
               KPhoneUidWmlBrowser, thread ) );
   }
   CleanupStack::PopAndDestroy(fixedUrl);

   aApaLsSession.Close();

#elif defined NAV2_CLIENT_SERIES60_V1
   return EFalse;
#else
# error This code not implemented!
#endif
   return ETrue;
}
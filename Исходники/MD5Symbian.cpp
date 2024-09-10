TInt TMD5Checker::ReadAndHashFileL(class RFs& aFs, const TDesC& aFile)
{
   TInt ret = KErrNone;

   class RFile file;
   // CAP: dependent
   User::LeaveIfError(file.Open(aFs, aFile, EFileRead));
   CleanupClosePushL(file);

   HBufC8* readBuf = HBufC8::NewLC(6*1024);
   TPtr8 buf = readBuf->Des();

   Reset();

   User::LeaveIfError(file.Read(buf));
   while(buf.Length() > 0){
      Append(buf);
      User::LeaveIfError(file.Read(buf));
   }

   Finish();
      
   CleanupStack::PopAndDestroy(readBuf);
   CleanupStack::PopAndDestroy(/*file*/);
   return ret;
}
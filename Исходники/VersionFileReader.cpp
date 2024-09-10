TInt CVersionFileReader::ReadNewVersionFileL(const TDesC& versionFile)
{
   iNewVersionArray->Reset();
   class RFs& fs = CCoeEnv::Static()->FsSession();
   class RFile file;
   TInt ret = file.Open(fs, versionFile, 
                        EFileStreamText | EFileRead);
   if(ret != KErrNone) {
      /* Could not open file, return the error code */
      return ret;
   }
   
   HBufC8* line = HBufC8::NewLC(40);
   TInt pos = -1;
   file.Seek(ESeekStart, pos);
   TPtr8 pLine = line->Des();
   ret = file.Read(pLine);
   if(line->Length() == 0) {
      // Empty file
      file.Close();
      return KErrEof;
   }
   file.Close();

   // The file contains a string that should match this regex:
   // [0-9]+\.[0-9]+\.[0-9]\+:[0-9]+\.[0-9]+\.[0-9]\+:[0-9]\+
   // The string is separated into three parts by ':'. 
   // The first part is the application version
   // The second part is the resource version
   // The third part is the mlfw version.
   const TChar colon = ':';
   const TChar dot = '.';
   while(line->Length() > 0) {
      if(line->Locate(colon) != KErrNotFound) {
         TPtrC8 part = line->Left(line->Locate(colon));
         TPtrC8 version = part.Left(part.LocateReverse(dot));
         TPtrC8 misc = part.Right(part.Length() - part.LocateReverse(dot) - 1);
         iNewVersionArray->AppendL(part);
         iNewVersionArray->AppendL(version);
         iNewVersionArray->AppendL(misc);
         line->Des().CopyF(line->Right(line->Length() - line->Locate(colon) - 1));
      } else {
         iNewVersionArray->AppendL(*line);
         break;
      }
   }
   CleanupStack::PopAndDestroy(line);
   return 0;
}
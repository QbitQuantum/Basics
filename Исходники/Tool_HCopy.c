/* IsWave: check config parms to see if target is a waveform */
Boolean IsWave(char *srcFile)
{
   FILE *f;
   long nSamp,sampP, hdrS;
   short sampS,kind;
   Boolean isPipe,bSwap,isWave;
   
   isWave = tgtPK == WAVEFORM;
   if (tgtPK == ANON){
      if ((srcFF == HTK || srcFF == ESIG) && srcFile != NULL){
         if ((f=FOpen(srcFile,WaveFilter,&isPipe)) == NULL)
            HError(1011,"IsWave: cannot open File %s",srcFile);
         switch (srcFF) {
         case HTK:
            if (!ReadHTKHeader(f,&nSamp,&sampP,&sampS,&kind,&bSwap))
               HError(1013, "IsWave: cannot read HTK Header in File %s",
                      srcFile);
            break;
         case ESIG:
            if (!ReadEsignalHeader(f, &nSamp, &sampP, &sampS,
                                   &kind, &bSwap, &hdrS, isPipe))
               HError(1013, "IsWave: cannot read Esignal Header in File %s",
                      srcFile);             
            break;
         }
         isWave = kind == WAVEFORM;
         FClose(f,isPipe);
      } else
         isWave = TRUE;
   }
   return isWave;
}
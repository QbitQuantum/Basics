void cChatEngine::set_sentence(char csender[30], char csentence[128]) {
   if (sender[0] == ' ' || sender[0] == '\0') {
      //      SERVER_PRINT("Sender & sentence set.\nSender=");
      //      SERVER_PRINT(csender);
      //      SERVER_PRINT("\nSentence=");
      //      SERVER_PRINT(csentence);
      //      SERVER_PRINT("--\n");

      strcpy(sender, csender);
#ifdef _WIN32

      _strupr(csentence);
      // #elseif did not compile in MSVC - stefan (26/04/04)
#else
      //for linux by ok:
      //further changed back by evyncke as these are normal string not CString
      //Hence, hardcoding the strupr inline...
      char *pString;
      pString = csentence;
      while (*pString) {
         *pString = toupper(*pString);
         pString++;
      }
      //              transform (csentence.begin(), csentence.end(), csentence.begin(), toupper);
#endif

      strcpy(sentence, csentence);
   }
}
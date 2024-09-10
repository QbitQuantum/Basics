nsresult nsTestUConv::DisplayCharsets()
{
  char * trace = "DisplayCharsets";
  mLog.AddTrace(trace);
  nsresult res = NS_OK;

  nsCOMPtr<nsICharsetConverterManager> ccMan = 
           do_GetService(kCharsetConverterManagerCID, &res);
  if (NS_FAILED(res)) {
    mLog.PrintError("NS_WITH_SERVICE", res);
    return res;
  }

  nsCOMPtr<nsIUTF8StringEnumerator> decoders;
  nsCOMPtr<nsIUTF8StringEnumerator> encoders;

  res = ccMan->GetDecoderList(getter_AddRefs(decoders));
  if (NS_FAILED(res)) {
    mLog.PrintError("GetDecoderList()", res);
    return res;
  }

  res = ccMan->GetEncoderList(getter_AddRefs(encoders));
  if (NS_FAILED(res)) {
    mLog.PrintError("GetEncoderList()", res);
    return res;
  }


  printf("***** Character Sets *****\n");

  PRUint32 encCount = 0, decCount = 0;
  PRUint32 basicEncCount = 0, basicDecCount = 0;

  nsCStringArray allCharsets;
  
  nsCAutoString charset;
  PRBool hasMore;
  encoders->HasMore(&hasMore);
  while (hasMore) {
    res = encoders->GetNext(charset);
    if (NS_SUCCEEDED(res))
      allCharsets.AppendCString(charset);

    encoders->HasMore(&hasMore);
  }

  nsAutoString prop, str;
  PRUint32 count = allCharsets.Count();
  for (PRUint32 i = 0; i < count; i++) {

    const nsCString* charset = allCharsets[i];
    printf("%s", charset->get());
    PrintSpaces(24 - charset->Length());  // align to hard coded column number


    nsCOMPtr<nsIUnicodeDecoder> dec = NULL;
    res = ccMan->GetUnicodeDecoder(charset->get(), getter_AddRefs(dec));
    if (NS_FAILED(res)) printf (" "); 
    else {
      printf("D");
      decCount++;
    }
#ifdef NS_DEBUG
    // show the "basic" decoder classes
    if (dec) {
      nsCOMPtr<nsIBasicDecoder> isBasic = do_QueryInterface(dec);
      if (isBasic) {
        basicDecCount++;
        printf("b");
      }
      else printf(" ");
    }
    else printf(" ");
#endif

    nsCOMPtr<nsIUnicodeEncoder> enc = NULL;
    res = ccMan->GetUnicodeEncoder(charset->get(), getter_AddRefs(enc));
    if (NS_FAILED(res)) printf (" "); 
    else {
      printf("E");
      encCount++;
    }

#ifdef NS_DEBUG
    if (enc) {
      nsCOMPtr<nsIBasicEncoder> isBasic = do_QueryInterface(enc);
      if (isBasic) {
        basicEncCount++;
        printf("b");
      }
      else printf(" ");
    }
    else printf(" ");
#endif
    
    printf(" ");

    prop.AssignLiteral(".notForBrowser");
    res = ccMan->GetCharsetData(charset->get(), prop.get(), str);
    if ((dec != NULL) && (NS_FAILED(res))) printf ("B"); 
    else printf("X");

    prop.AssignLiteral(".notForComposer");
    res = ccMan->GetCharsetData(charset->get(), prop.get(), str);
    if ((enc != NULL) && (NS_FAILED(res))) printf ("C"); 
    else printf("X");

    prop.AssignLiteral(".notForMailView");
    res = ccMan->GetCharsetData(charset->get(), prop.get(), str);
    if ((dec != NULL) && (NS_FAILED(res))) printf ("V"); 
    else printf("X");

    prop.AssignLiteral(".notForMailEdit");
    res = ccMan->GetCharsetData(charset->get(), prop.get(), str);
    if ((enc != NULL) && (NS_FAILED(res))) printf ("E"); 
    else printf("X");

    printf("(%3d, %3d) ", encCount, decCount);
    res = ccMan->GetCharsetTitle(charset->get(), str);
    if (NS_FAILED(res)) str.SetLength(0);
    NS_LossyConvertUCS2toASCII buff2(str);
    printf(" \"%s\"\n", buff2.get());
  }

  printf("%u of %u decoders are basic (%d%%)\n",
         basicDecCount, decCount, (basicDecCount * 100) / decCount);

  printf("%u of %u encoders are basic (%d%%)\n",
         basicEncCount, encCount, (basicEncCount * 100) / encCount);
  mLog.DelTrace(trace);
  return NS_OK;
}
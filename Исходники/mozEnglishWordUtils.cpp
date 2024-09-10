mozEnglishWordUtils::myspCapitalization 
mozEnglishWordUtils::captype(const nsString &word)
{
  if(!mCaseConv) return HuhCap; //punt
  PRUnichar* lword=ToNewUnicode(word);  
  mCaseConv->ToUpper(lword,lword,word.Length());
  if(word.Equals(lword)){
    nsMemory::Free(lword);
    return AllCap;
  }

  mCaseConv->ToLower(lword,lword,word.Length());
  if(word.Equals(lword)){
    nsMemory::Free(lword);
    return NoCap;
  }
  PRInt32 length=word.Length();
  if(Substring(word,1,length-1).Equals(lword+1)){
    nsMemory::Free(lword);
    return InitCap;
  }
  nsMemory::Free(lword);
  return HuhCap;
}
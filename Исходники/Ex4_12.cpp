int main()
{ 
  char* str("Smith, where Jones had had \"had had\" had had \"had\"."
                         "\n\"Had had\" had had the examiners' approval.");
  char* word("had");
  cout << "The string to be searched is: "
       << endl << str << endl;

  int count(0);                   // Number of occurrences of word in str
  char* pstr(str);                // Pointer to search start position
  char* found(nullptr);           // Pointer to occurrence of word in str            
  while(true)
  {
    found = strstr(pstr, word);
    if(!found)
      break;
    ++count;
    pstr = found+strlen(word);    // Set next search start as 1 past the word found
  }
  cout << "\"" << word << "\" was found " 
       << count << " times in the string." << endl;
  return 0;
}
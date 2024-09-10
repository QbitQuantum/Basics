void addWords(Password* fh)
{
   Keyboard* kb = Keyboard::getKeyboard();
   String* file_str = kb->readString("Enter the file name containing the possible passwords: ");
   ReadFile* rf = new ReadFile(file_str->getText());
   delete file_str;

   String* num_words_str = rf->readLine();
   int num_words = num_words_str->a_to_i();
   delete num_words_str;

   for (int i = 0; i < num_words; i++)
   {
      String* word = rf->readLine();
      fh->addWord(word);
   }

   delete rf;
   fh->displayViableWords();
}
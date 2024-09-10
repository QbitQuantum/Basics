      /// <summary>Convert string into a list of phrases with contiguous formatting</summary>
      /// <param name="str">string.</param>
      /// <returns>List of phrases</returns>
      PhraseList  RichTextRenderer::GetPhrases(const RichString& str)
      {
         // space char as a RichCharacter
         static RichCharacter space(' ', Colour::Default, NULL);

         // lambda for assembling phrases
         static function<void (PhraseList& list, const RichCharacter*)> buildPhrases = [](PhraseList& list, const RichCharacter* ch) 
         {
            // Init: Start first phrase
            if (list.empty())
               list += RichPhrase(iswcntrl(ch->Char) ? space : *ch);
            else
            {
               RichPhrase& current = list.back();

               // CRLF: Replace with space
               if (iswcntrl(ch->Char))
                  current += ' ';

               // Create new phrase if colour/formatting changes
               else if (ch->Colour != current.Colour
                     || ch->Format != current.Format)
                     list += RichPhrase(*ch);
               else
                  // Otherwise append to last phrase
                  current += ch->Char;
            }
         };

         
         PhraseList phrases;

         // Author: Manual insert
         if (str.Author.length())
         {
            // Parse colours + formatting
            for (auto& ch : RichStringParser(str.Author).Output.Characters)
               buildPhrases(phrases, ch);

            // Spacing phrase
            phrases += RichPhrase(L" ", NULL, Colour::Default);
         }

         // Title: Manual insert
         if (str.Title.length())
         {
            // Parse colours + formatting
            for (auto& ch : RichStringParser(str.Title).Output.Characters)
               buildPhrases(phrases, ch);

            // Spacing phrase
            phrases += RichPhrase(L" ", NULL, Colour::Default);
         }

         // Embolden author/title, if any
         for (auto& p : phrases)
         {
            p.Format |= CFE_BOLD;
            p.CustomFont = L"Times New Roman";
         }
         
         // Assemble phrases
         for (const RichCharacter* ch : str.Characters)
            buildPhrases(phrases, ch);

         return phrases;
      }
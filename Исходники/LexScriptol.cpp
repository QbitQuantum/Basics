static void ColouriseSolDoc(unsigned int startPos, int length, int initStyle,
                            WordList *keywordlists[], Accessor &styler)
 {

	int lengthDoc = startPos + length;
        char stringType = '\"';

	if (startPos > 0)
        {
            int lineCurrent = styler.GetLine(startPos);
            if (lineCurrent > 0)
            {
              startPos = styler.LineStart(lineCurrent-1);
              if (startPos == 0) initStyle = SCE_SCRIPTOL_DEFAULT;
              else               initStyle = styler.StyleAt(startPos-1);
            }
	}

	styler.StartAt(startPos, 127);

	WordList &keywords = *keywordlists[0];

	int whingeLevel = styler.GetPropertyInt("tab.timmy.whinge.level");
	char prevWord[200];
	prevWord[0] = '\0';
        if (length == 0)  return;

	int state = initStyle & 31;

	int nextIndex = 0;
        char chPrev  = ' ';
        char chPrev2 = ' ';
        char chNext  = styler[startPos];
	styler.StartSegment(startPos);
	bool atStartLine = true;
	int spaceFlags = 0;
	for (int i = startPos; i < lengthDoc; i++)
        {

         if (atStartLine)
         {
         char chBad = static_cast<char>(64);
         char chGood = static_cast<char>(0);
         char chFlags = chGood;

         if (whingeLevel == 1)
         {
             chFlags = (spaceFlags & wsInconsistent) ? chBad : chGood;
         }
         else if (whingeLevel == 2)
         {
             chFlags = (spaceFlags & wsSpaceTab) ? chBad : chGood;
         }
         else if (whingeLevel == 3)
         {
             chFlags = (spaceFlags & wsSpace) ? chBad : chGood;
         }
         else if (whingeLevel == 4)
         {
              chFlags = (spaceFlags & wsTab) ? chBad : chGood;
         }
         styler.SetFlags(chFlags, static_cast<char>(state));
         atStartLine = false;
       }

       char ch = chNext;
       chNext = styler.SafeGetCharAt(i + 1);

       if ((ch == '\r' && chNext != '\n') || (ch == '\n') || (i == lengthDoc))
       {
          if ((state == SCE_SCRIPTOL_DEFAULT) ||
              (state == SCE_SCRIPTOL_TRIPLE) ||
              (state == SCE_SCRIPTOL_COMMENTBLOCK))
          {
              styler.ColourTo(i, state);
          }
          atStartLine = true;
        }

        if (styler.IsLeadByte(ch))
         {
             chNext = styler.SafeGetCharAt(i + 2);
             chPrev  = ' ';
             chPrev2 = ' ';
             i += 1;
             continue;
         }

        if (state == SCE_SCRIPTOL_STRINGEOL)
         {
             if (ch != '\r' && ch != '\n')
             {
                    styler.ColourTo(i - 1, state);
                    state = SCE_SCRIPTOL_DEFAULT;
             }
         }

        if (state == SCE_SCRIPTOL_DEFAULT)
         {
            if (IsSolWordStart(ch))
            {
                 styler.ColourTo(i - 1, state);
                 state = SCE_SCRIPTOL_KEYWORD;
            }
            else if (ch == '`')
            {
                styler.ColourTo(i - 1, state);
                state = SCE_SCRIPTOL_COMMENTLINE;
            }
            else if (ch == '/')
            {
                styler.ColourTo(i - 1, state);
                if(chNext == '/') state = SCE_SCRIPTOL_CSTYLE;
                if(chNext == '*') state = SCE_SCRIPTOL_COMMENTBLOCK;
            }

            else if (IsSolStringStart(ch))
            {
               styler.ColourTo(i - 1, state);
               state = GetSolStringState(styler, i, &nextIndex);
               if(state == SCE_SCRIPTOL_STRING)
               {
                 stringType = ch;
               }
               if (nextIndex != i + 1)
               {
                   i = nextIndex - 1;
                   ch = ' ';
                   chPrev = ' ';
                   chNext = styler.SafeGetCharAt(i + 1);
               }
           }
            else if (isoperator(ch))
            {
                 styler.ColourTo(i - 1, state);
                 styler.ColourTo(i, SCE_SCRIPTOL_OPERATOR);
            }
          }
          else if (state == SCE_SCRIPTOL_KEYWORD)
          {
              if (!iswordchar(ch))
              {
                 ClassifyWordSol(styler.GetStartSegment(), i - 1, keywords, styler, prevWord);
                 state = SCE_SCRIPTOL_DEFAULT;
                 if (ch == '`')
                 {
                     state = chNext == '`' ? SCE_SCRIPTOL_PERSISTENT : SCE_SCRIPTOL_COMMENTLINE;
                 }
                 else if (IsSolStringStart(ch))
                 {
                    styler.ColourTo(i - 1, state);
                    state = GetSolStringState(styler, i, &nextIndex);
                    if (nextIndex != i + 1)
                    {
                       i = nextIndex - 1;
                       ch = ' ';
                       chPrev = ' ';
                       chNext = styler.SafeGetCharAt(i + 1);
                     }
                 }
                 else if (isoperator(ch))
                 {
                     styler.ColourTo(i, SCE_SCRIPTOL_OPERATOR);
                 }
             }
          }
          else
          {
            if (state == SCE_SCRIPTOL_COMMENTLINE ||
                state == SCE_SCRIPTOL_PERSISTENT ||
                state == SCE_SCRIPTOL_CSTYLE)
            {
                 if (ch == '\r' || ch == '\n')
                 {
                     styler.ColourTo(i - 1, state);
                     state = SCE_SCRIPTOL_DEFAULT;
                 }
            }
            else if(state == SCE_SCRIPTOL_COMMENTBLOCK)
            {
              if(chPrev == '*' && ch == '/')
              {
                styler.ColourTo(i, state);
                state = SCE_SCRIPTOL_DEFAULT;
              }
            }
            else if ((state == SCE_SCRIPTOL_STRING) ||
                     (state == SCE_SCRIPTOL_CHARACTER))
            {
               if ((ch == '\r' || ch == '\n') && (chPrev != '\\'))
                {
                    styler.ColourTo(i - 1, state);
                    state = SCE_SCRIPTOL_STRINGEOL;
                }
                else if (ch == '\\')
                {
                   if (chNext == '\"' || chNext == '\'' || chNext == '\\')
                   {
                        i++;
                        ch = chNext;
                        chNext = styler.SafeGetCharAt(i + 1);
                   }
                 }
                else if ((ch == '\"') || (ch == '\''))
                {
                    // must match the entered quote type
                    if(ch == stringType)
                    {
                      styler.ColourTo(i, state);
                      state = SCE_SCRIPTOL_DEFAULT;
                    }
                 }
             }
             else if (state == SCE_SCRIPTOL_TRIPLE)
             {
                if ((ch == '\'' && chPrev == '\'' && chPrev2 == '\'') ||
                    (ch == '\"' && chPrev == '\"' && chPrev2 == '\"'))
                 {
                    styler.ColourTo(i, state);
                    state = SCE_SCRIPTOL_DEFAULT;
                 }
             }

           }
          chPrev2 = chPrev;
          chPrev = ch;
	}
        if (state == SCE_SCRIPTOL_KEYWORD)
        {
            ClassifyWordSol(styler.GetStartSegment(),
                 lengthDoc-1, keywords, styler, prevWord);
	}
        else
        {
            styler.ColourTo(lengthDoc-1, state);
	}
}
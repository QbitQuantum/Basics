/// Translate a file pattern into a regular expression
bool DirectoryResource::pattern2RegEx(const UtlString& pattern, UtlString& patternExpression)
{
   patternExpression.remove(0);

   RegEx regularExpressionSpecial(RegularExpressionSpecial);
   
   ssize_t patternPosition = 0;
   ssize_t nextSpecialPosition;

   while ( regularExpressionSpecial.SearchAt(pattern, patternPosition) )
   {
      nextSpecialPosition = regularExpressionSpecial.MatchStart(0);
      char nextSpecial = pattern(nextSpecialPosition);
      
      if ( nextSpecialPosition == patternPosition )
      {
         if ( nextSpecial == '*' )
         {
            patternExpression.append( (patternPosition == 0)
                                     ? InitialWildcardRegexp
                                     : InsideWildcardRegexp );
            patternPosition++;
         }
         else
         {
            // all other characters that are significant in a regexp are escaped
            patternExpression.append("\\");
            patternExpression.append(nextSpecial);
            patternPosition++;
         }
      }
      else
      {
         ssize_t fixedPartLength = nextSpecialPosition - patternPosition;
         patternExpression.append(pattern, patternPosition, fixedPartLength);
         patternPosition += fixedPartLength;
         /*
          * We have not incremented past the special, so we will match it again on
          * the next iteration; this avoids having to duplicate the checks for
          * whether it is '*' or some other regular expression character here
          */
      }
   }

   // append any fixed part that follows the last wildcard
   if ((size_t)patternPosition < pattern.length())
   {
      patternExpression.append( pattern, patternPosition, UTLSTRING_TO_END );
   }

   Os::Logger::instance().log(FAC_SUPERVISOR, PRI_DEBUG,
                 "DirectoryResource::patternRegEx( '%s' ) -> '%s'",
                 pattern.data(), patternExpression.data()
                 );
   
   return ! patternExpression.isNull();
}
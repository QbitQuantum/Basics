char* replace(char* str, char replacing, char* with)
{
      int strL = strLen(str);
      char* result = addSpaces(str);
      int newLen = strLen(result);
      int withLen = strLen(with);
      int i = 0;
      
      while ((strL - 1)!= 0)
      {
            if (str[strL - 1] != replacing)
            {
                result[newLen - 1] = str[strL - 1];
                newLen--;
                strL--;
            }
            else
            {
                for (i = withLen - 1; i >= 0 ; i--)
                    result[--newLen] = with[i];
                strL--;  
            }  
      }
      return result;
}
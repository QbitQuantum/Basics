/**
 * Takes a given unicode string 'dest' and
 * replaces any lowercase letter by the set made of itself and
 * its uppercase equivalent, surrounded with square brackets if
 * the letter was not already between square brackets.
 * Examples:
 *
 * "For" => "F[oO][rR]"
 * "F[ao]r" => "F[aAoO][rR]"
 *
 * The output is stored in 'src'. The function assumes that 'src' is
 * wide enough.
 *
 * This function is used for morphological filter regular expressions.
 */
void replace_letter_by_letter_set(const Alphabet* a,unichar* dest,const unichar* src) {
int i=0,j=0;
char inside_a_set=0;
while (src[i]!='\0') {
   switch (src[i]) {
      case '\\':
         if (src[i+1]=='\0') {
             // there is nothing after a backslash, then we stop,
             // and the RE compiler may indicate an error
             dest[j++] = src[i++];
             dest[j] = src[i];
             return;
         }
         if (is_lower(src[i+1],a)) {
             // this is a lowercase letter in Unitex alphabet :
             // we don't need "\" and we make expansion "[eE]"
             ++i;
             if (!inside_a_set) dest[j++]='[';
             dest[j++]=src[i];
             if (a==NULL) {
                /* If there is no alphabet file, we just consider the unique
                 * uppercase variant of the letter */
                dest[j++]=u_toupper(src[i]);
             } else {
			 unichar* tbrowse = NULL;
			 int i_pos_in_array_of_string = a->pos_in_represent_list[src[i]];
			 if (i_pos_in_array_of_string != 0)
				 tbrowse = a->t_array_collection[i_pos_in_array_of_string];
			 if (tbrowse != NULL)
				 while ((*tbrowse) != '\0') {
					 dest[j++]=*(tbrowse++);
				 }
             }
             if (!inside_a_set) dest[j++]=']';
             i++;
          } else {
             // others cases :
             // we keep the "\" and the letter
             dest[j++] = src[i++];
             dest[j++] = src[i++];
          }
          break;
       case '[':
          dest[j++]=src[i++];
          inside_a_set=1;
          break;
       case ']':
          dest[j++]=src[i++];
          inside_a_set=0;
          break;
       case '.': case '*': case '+': case '?': case '|': case '^': case '$':
       case ':': case '(': case ')': case '{': case '}': case '1': case '2':
       case '3': case '4': case '5': case '6': case '7': case '8': case '9':
          dest[j++]=src[i++];
          break;
       default:
          if (is_lower(src[i],a)) {
             if (!inside_a_set) dest[j++]='[';
             dest[j++]=src[i];
             if (inside_a_set && src[i+1]=='-') {
            	 /* Special case:
            	  * if we had [a-d], we don't want to turn it into
            	  * [aA-dD], but rather into [a-dA-D]. In such a case,
            	  * we just use u_toupper
            	  */
            	 i=i+2;
            	 dest[j++]='-';
            	 dest[j++]=src[i++];
            	 dest[j++]=u_toupper(dest[i-3]);
            	 dest[j++]='-';
            	 dest[j++]=u_toupper(src[i-1]);
            	 continue;
             }

             if (a==NULL) {
                /* If there is no alphabet file, we just consider the unique
                 * uppercase variant of the letter */
                dest[j++]=u_toupper(src[i]);
             } else {
                /* If there is an alphabet file, we use it */
                unichar* tbrowse = NULL;
                int i_pos_in_array_of_string = a->pos_in_represent_list[src[i]];
                if (i_pos_in_array_of_string != 0) {
                   tbrowse = a->t_array_collection[i_pos_in_array_of_string];
                }
                if (tbrowse != NULL) {
                   while ((*tbrowse) != '\0') {
                      dest[j++]=*(tbrowse++);
                   }
                }
             }
             if (!inside_a_set) dest[j++]=']';
             i++;
         }
          else {
             /* Not a lower case letter */
             dest[j++]=src[i++];
          }
   }
}
dest[j]='\0';
}
/**
 * This function allocates and returns a token_t structure corresponding to the given
 * string.
 */
token_t* new_token_t(unichar* str) {
token_t* tok=(token_t*)malloc(sizeof(token_t));
if (tok==NULL) {
   fatal_alloc_error("new_token_t");
}
for (const keyword_t* key=keywords;key->str!=NULL;key++) {
   if (!u_strcmp(str, key->str)) {
      /* If the token is a keyword */
      tok->type=key->val;
      tok->str= NULL;
      tok->next=NULL;
      return tok;
   }
}
if (*str=='<') {
   /* If we have a '<', we look for the ending '>' */
   unichar* p=u_strchr(str,'>');
   if (p==NULL || *(p+1)!='\0') {
      fatal_error("Invalid token: '%S'\n",str);
   }
   *p='\0';
   tok->type=TOK_ANGLE;
   /* We copy the content between the angle brackets */
   tok->str=u_strdup(str+1);
   tok->next=NULL;
   return tok;
}
/* Otherwise, we create a default token with the string */
tok->type=TOK_STR;
tok->str=u_strdup(str);
tok->next=NULL;
return tok;
}
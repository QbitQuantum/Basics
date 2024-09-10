static void tokens_expand( struct ureg_tokens *tokens,
                           unsigned count )
{
   unsigned old_size = tokens->size * sizeof(unsigned);

   if (tokens->tokens == error_tokens) {
      return;
   }

   while (tokens->count + count > tokens->size) {
      tokens->size = (1 << ++tokens->order);
   }

   tokens->tokens = REALLOC(tokens->tokens, 
                            old_size,
                            tokens->size * sizeof(unsigned));
   if (tokens->tokens == NULL) {
      tokens_error(tokens);
   }
}
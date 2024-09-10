int tokenizer_next( tokenizer_t *t, char *word, size_t size ) {
  UChar   savedEndChar;
  int k;

  // start iterator
  if( t->end == 0 ) {
    t->start = ubrk_first(t->boundary);
  }

  // Find next word
again:
  t->end = ubrk_next(t->boundary);
  if( t->end == UBRK_DONE ) {
    return -1;
  }

	// Null terminate
  savedEndChar = t->str[t->end];
  t->str[t->end] = 0;

	// Skip unct
	if( t->end - t->start == 1 && u_ispunct( t->str[t->start] ) ) {
    t->str[t->end] = savedEndChar;
    t->start = t->end;
    goto again;
	}

	// Skip whitespace
	for( k=t->start; k<t->end; k++ ) {
	  if( u_isspace( t->str[k] ) == 1 ) {
      t->str[t->end] = savedEndChar;
      t->start = t->end;
			goto again;
		}
  }

	// Copy to C bffer
  u_austrncpy(word, t->str+t->start, size-1);
  word[size-1] = 0;

  printf("string[%2d..%2d] \"%s\" %d\n", t->start, t->end-1, word, u_isspace( t->str[t->start])); 
  t->str[t->end] = savedEndChar;
  t->start = t->end;
  return 0;
}
int
compare_contexts(const context_t *x, const context_t *y)
{
  int *result = NULL;
  int ret_val = 0;

  // check if each entry in the 'x' context is in the 'y' context
  //
  for (uint i = 0; i < x->num_values; i++) {
    result = (int *) lfind (&(x->values[i]),
                            y->values, &(y->num_values), sizeof(int),
                            (int(*) (const void *, const void *))compare);

    if (result) {
      // if we got a non-null value then the value was found
      //
      ret_val = 1;
    } else {
      // if at any time we did not find a value we can give up
      //
      ret_val = 0;
      break;
    }
  }

  return ret_val;
}
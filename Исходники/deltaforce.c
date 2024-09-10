int compare_keys(char *buffer_left, char *buffer_right) {
  int keycmp = 0;
  int i;
  char field_left[MAX_FIELD_LEN + 1];
  char field_right[MAX_FIELD_LEN + 1];

  // printf("inside compare_keys([%s], [%s])\n", buffer_left, buffer_right);
  if (buffer_left == NULL && buffer_right == NULL) {
    return LEFT_RIGHT_EQUAL;
  }

  /* these special cases may seem counter-intuitive, but saying that
     a NULL line is greater than a non-NULL line results in
     the non-NULL line getting printed and a new line read in.
   */
  if (buffer_left == NULL)
    return LEFT_GREATER;

  if (buffer_right == NULL)
    return RIGHT_GREATER;

  for (i = 0; i < nkeys; i++) {
    get_line_field(field_left, buffer_left, MAX_FIELD_LEN, keyfields[i], delim);
    get_line_field(field_right, buffer_right, MAX_FIELD_LEN, keyfields[i],
                   delim);
    /* printf("Comparing (%s) to (%s) inside compare_keys\n", field_left, field_right); */
    if ((keycmp = strcoll(field_left, field_right)) != 0)
      break;
  }

  /* ensure predictable return values */
  if (keycmp == 0)
    return 0;
  if (keycmp < 0)
    return -1;
  if (keycmp > 0)
    return 1;
}
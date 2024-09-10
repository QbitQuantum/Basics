const char *
parse_thing (Thing thing, char **line, const char *type)
{
  const char *value;

  while (*line && ! **line)
    *line = read_line ();

  if (! *line) {
    print_error ("%s expected", type);
    return NULL;
  }

  value = *line;

  if (thing != STRING && thing != STRING_OR_NULL
      && (thing != STRING_OR_IDENTIFIER || **line != '"')) {
    do {
      int expected_character;

      switch (thing) {
      case IDENTIFIER:
      case STRING_OR_IDENTIFIER:
	expected_character = (isalpha (**line) || **line == '_'
			      || (*line != value && isdigit (**line)));
	break;

      case PROPERTY_IDENTIFIER:
	expected_character = isupper (**line);
	break;

      case FIELD_NAME:
	expected_character = (isalpha (**line)
			      || **line == '_' || ** line == '['
			      || (*line != value && (isdigit (**line)
						     || **line == '.'
						     || **line == ']')));
	break;

      case INTEGER_NUMBER:
	expected_character = isdigit (**line);
	break;

      case FLOATING_POINT_NUMBER:
	expected_character = isdigit (**line) || **line == '.';
	break;

      case TIME_VALUE:
	expected_character = (isdigit (**line)
			      || **line == ':' || **line == '.');
	break;

      default:
	assert (0);
      }

      if (!expected_character) {
	print_error ("unexpected character '%c' in %s", **line, type);
	return NULL;
      }

      (*line)++;
    } while (**line && !isspace (**line));
  }
  else {
    if (thing == STRING_OR_NULL) {
      char *possible_null = *line;

      if (looking_at ("NULL", line)) {
	*(possible_null + 4) = 0;
	return possible_null;
      }
    }

    if (**line != '"') {
      print_error ("string%s expected",
		   (thing == STRING ? "" : (thing == STRING_OR_NULL
					    ? " or NULL" : "or identifier")));
      return NULL;
    }

    while (1) {
      (*line)++;

      if (! **line || (**line == '\\' && ! *(*line + 1))) {
	print_error ("unterminated string");
	return NULL;
      }

      if (**line == '"') {
	(*line)++;
	break;
      }

      if (**line == '\\')
	(*line)++;
    }
  }

  if (**line) {
    **line = 0;
    do
      (*line)++;
    while (isspace (**line));
  }

  return value;
}
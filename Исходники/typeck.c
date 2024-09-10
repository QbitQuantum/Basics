static tree
parse_signature_type (const unsigned char **ptr, const unsigned char *limit)
{
  tree type;
  gcc_assert (*ptr < limit);

  switch (**ptr)
    {
    case 'B':  (*ptr)++;  return byte_type_node;
    case 'C':  (*ptr)++;  return char_type_node;
    case 'D':  (*ptr)++;  return double_type_node;
    case 'F':  (*ptr)++;  return float_type_node;
    case 'S':  (*ptr)++;  return short_type_node;
    case 'I':  (*ptr)++;  return int_type_node;
    case 'J':  (*ptr)++;  return long_type_node;
    case 'Z':  (*ptr)++;  return boolean_type_node;
    case 'V':  (*ptr)++;  return void_type_node;
    case '[':
      for ((*ptr)++; (*ptr) < limit && ISDIGIT (**ptr); ) (*ptr)++;
      type = parse_signature_type (ptr, limit);
      type = build_java_array_type (type, -1); 
      break;
    case 'L':
      {
	const unsigned char *start = ++(*ptr);
	const unsigned char *str = start;
	for ( ; ; str++)
	  {
	    gcc_assert (str < limit);
	    if (*str == ';')
	      break;
	  }
	*ptr = str+1;
	type = lookup_class (unmangle_classname ((const char *) start, str - start));
	break;
      }
    default:
      gcc_unreachable ();
    }
  return promote_type (type);
}
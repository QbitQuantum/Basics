static void
output_i386_opcode (FILE *table, const char *name, char *str,
		    char *last, int lineno)
{
  unsigned int i;
  char *operands, *base_opcode, *extension_opcode, *opcode_length;
  char *cpu_flags, *opcode_modifier, *operand_types [MAX_OPERANDS];

  /* Find number of operands.  */
  operands = next_field (str, ',', &str, last);

  /* Find base_opcode.  */
  base_opcode = next_field (str, ',', &str, last);

  /* Find extension_opcode.  */
  extension_opcode = next_field (str, ',', &str, last);

  /* Find opcode_length.  */
  opcode_length = next_field (str, ',', &str, last);

  /* Find cpu_flags.  */
  cpu_flags = next_field (str, ',', &str, last);

  /* Find opcode_modifier.  */
  opcode_modifier = next_field (str, ',', &str, last);

  /* Remove the first {.  */
  str = remove_leading_whitespaces (str);
  if (*str != '{')
    abort ();
  str = remove_leading_whitespaces (str + 1);

  i = strlen (str);

  /* There are at least "X}".  */
  if (i < 2)
    abort ();

  /* Remove trailing white spaces and }. */
  do
    {
      i--;
      if (ISSPACE (str[i]) || str[i] == '}')
	str[i] = '\0';
      else
	break;
    }
  while (i != 0);

  last = str + i;

  /* Find operand_types.  */
  for (i = 0; i < ARRAY_SIZE (operand_types); i++)
    {
      if (str >= last)
	{
	  operand_types [i] = NULL;
	  break;
	}

      operand_types [i] = next_field (str, ',', &str, last);
      if (*operand_types[i] == '0')
	{
	  if (i != 0)
	    operand_types[i] = NULL;
	  break;
	}
    }

  fprintf (table, "  { \"%s\", %s, %s, %s, %s,\n",
	   name, operands, base_opcode, extension_opcode,
	   opcode_length);

  process_i386_cpu_flag (table, cpu_flags, 0, ",", "    ", lineno);

  process_i386_opcode_modifier (table, opcode_modifier, lineno);

  fprintf (table, "    { ");

  for (i = 0; i < ARRAY_SIZE (operand_types); i++)
    {
      if (operand_types[i] == NULL || *operand_types[i] == '0')
	{
	  if (i == 0)
	    process_i386_operand_type (table, "0", 0, "\t  ", lineno);
	  break;
	}

      if (i != 0)
	fprintf (table, ",\n      ");

      process_i386_operand_type (table, operand_types[i], 0,
				 "\t  ", lineno);
    }
  fprintf (table, " } },\n");
}
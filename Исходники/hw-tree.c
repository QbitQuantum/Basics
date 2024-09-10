struct hw *
hw_tree_vparse (struct hw *current,
		const char *fmt,
		va_list ap)
{
  char device_specifier[1024];
  name_specifier spec;

  /* format the path */
  vsprintf (device_specifier, fmt, ap);
  if (strlen (device_specifier) >= sizeof (device_specifier))
    hw_abort (NULL, "device_tree_add_deviced: buffer overflow\n");

  /* construct the tree down to the final struct hw */
  current = split_fill_path (current, device_specifier, &spec);

  /* is there an interrupt spec */
  if (spec.property == NULL
      && spec.value != NULL)
    {
      char *op = split_value (&spec);
      switch (op[0])
	{
	case '>':
	  {
	    char *my_port_name = split_value (&spec);
	    int my_port;
	    char *dest_port_name = split_value (&spec);
	    int dest_port;
	    name_specifier dest_spec;
	    char *dest_hw_name = split_value (&spec);
	    struct hw *dest;
	    /* find my name */
	    if (!hw_finished_p (current))
	      hw_finish (current);
	    my_port = hw_port_decode (current, my_port_name, output_port);
	    /* find the dest device and port */
	    dest = split_fill_path (current, dest_hw_name, &dest_spec);
	    if (!hw_finished_p (dest))
	      hw_finish (dest);
	    dest_port = hw_port_decode (dest, dest_port_name,
					input_port);
	    /* connect the two */
	    hw_port_attach (current,
			    my_port,
			    dest,
			    dest_port,
			    permenant_object);
	    break;
	  }
	default:
	  hw_abort (current, "unreconised interrupt spec %s\n", spec.value);
	  break;
	}
    }

  /* is there a property */
  if (spec.property != NULL)
    {
      if (strcmp (spec.value, "true") == 0)
	hw_add_boolean_property (current, spec.property, 1);
      else if (strcmp (spec.value, "false") == 0)
	hw_add_boolean_property (current, spec.property, 0);
      else
	{
	  const struct hw_property *property;
	  switch (spec.value[0])
	    {
#if NOT_YET
	    case '*':
	      {
		parse_ihandle_property (current, spec.property, spec.value + 1);
		break;
	      }
#endif
	    case '[':
	      {
		unsigned8 words[1024];
		char *curr = spec.value + 1;
		int nr_words = 0;
		while (1)
		  {
		    char *next;
		    words[nr_words] = H2BE_1 (strtoul (curr, &next, 0));
		    if (curr == next)
		      break;
		    curr = next;
		    nr_words += 1;
		  }
		hw_add_array_property (current, spec.property,
				       words, sizeof (words[0]) * nr_words);
		break;
	      }
	    case '"':
	      {
		parse_string_property (current, spec.property, spec.value);
		break;
	      }
	    case '!':
	      {
		spec.value++;
		property = hw_tree_find_property (current, spec.value);
		if (property == NULL)
		  hw_abort (current, "property %s not found\n", spec.value);
		hw_add_duplicate_property (current,
					   spec.property,
					   property);
		break;
	      }
	    default:
	      {
		if (strcmp (spec.property, "reg") == 0
		    || strcmp (spec.property, "assigned-addresses") == 0
		    || strcmp (spec.property, "alternate-reg") == 0)
		  {
		    parse_reg_property (current, spec.property, spec.value);
		  }
		else if (strcmp (spec.property, "ranges") == 0)
		  {
		    parse_ranges_property (current, spec.property, spec.value);
		  }
		else if (isdigit (spec.value[0])
			 || (spec.value[0] == '-' && isdigit (spec.value[1]))
			 || (spec.value[0] == '+' && isdigit (spec.value[1])))
		  {
		    parse_integer_property (current, spec.property, spec.value);
		  }
		else
		  parse_string_property (current, spec.property, spec.value);
		break;
	      }
	    }
	}
    }
  return current;
}
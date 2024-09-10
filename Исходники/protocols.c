static int read_file (const char *path)
{
  FILE *fh;
  char key_buffer[4096];
  char value_buffer[4096];
  char *key_ptr;
  char *value_ptr;
  char *key_fields[256];
  char *value_fields[256];
  int key_fields_num;
  int value_fields_num;
  int status;
  int i;

  fh = fopen (path, "r");
  if (fh == NULL)
  {
    ERROR ("protocols plugin: fopen (%s) failed: %s.",
        path, sstrerror (errno, key_buffer, sizeof (key_buffer)));
    return (-1);
  }

  status = -1;
  while (42)
  {
    clearerr (fh);
    key_ptr = fgets (key_buffer, sizeof (key_buffer), fh);
    if (key_ptr == NULL)
    {
      if (feof (fh) != 0)
      {
        status = 0;
        break;
      }
      else if (ferror (fh) != 0)
      {
        ERROR ("protocols plugin: Reading from %s failed.", path);
        break;
      }
      else
      {
        ERROR ("protocols plugin: fgets failed for an unknown reason.");
        break;
      }
    } /* if (key_ptr == NULL) */

    value_ptr = fgets (value_buffer, sizeof (value_buffer), fh);
    if (value_ptr == NULL)
    {
      ERROR ("protocols plugin: read_file (%s): Could not read values line.",
          path);
      break;
    }

    key_ptr = strchr (key_buffer, ':');
    if (key_ptr == NULL)
    {
      ERROR ("protocols plugin: Could not find protocol name in keys line.");
      break;
    }
    *key_ptr = 0;
    key_ptr++;

    value_ptr = strchr (value_buffer, ':');
    if (value_ptr == NULL)
    {
      ERROR ("protocols plugin: Could not find protocol name "
          "in values line.");
      break;
    }
    *value_ptr = 0;
    value_ptr++;

    if (strcmp (key_buffer, value_buffer) != 0)
    {
      ERROR ("protocols plugin: Protocol names in keys and values lines "
          "don't match: `%s' vs. `%s'.",
          key_buffer, value_buffer);
      break;
    }


    key_fields_num = strsplit (key_ptr,
        key_fields, STATIC_ARRAY_SIZE (key_fields));
    value_fields_num = strsplit (value_ptr,
        value_fields, STATIC_ARRAY_SIZE (value_fields));

    if (key_fields_num != value_fields_num)
    {
      ERROR ("protocols plugin: Number of fields in keys and values lines "
          "don't match: %i vs %i.",
          key_fields_num, value_fields_num);
      break;
    }

    for (i = 0; i < key_fields_num; i++)
    {
      if (values_list != NULL)
      {
        char match_name[2 * DATA_MAX_NAME_LEN];

        ssnprintf (match_name, sizeof (match_name), "%s:%s",
            key_buffer, key_fields[i]);

        if (ignorelist_match (values_list, match_name))
          continue;
      } /* if (values_list != NULL) */

      submit (key_buffer, key_fields[i], value_fields[i]);
    } /* for (i = 0; i < key_fields_num; i++) */
  } /* while (42) */

  fclose (fh);

  return (status);
} /* int read_file */